#include "Node.hpp"

#include <glm/gtx/transform.hpp>
#include <algorithm>
#include <string>
#include "logger.hpp"
#include "AppManager.hpp"
#include "ActionManager.hpp"

NS_SPECTRUM_BEGIN

Node::Node()
    : m_pos({0.f, 0.f}), m_boundingBox({0, 0}), m_anchorPoint({.5f, .5f}), m_scale({1.f, 1.f}), m_rotation(0.f), m_objectLimit(UINT_MAX), m_zOrder(0),
      m_tag(""), m_children({}), m_parent(nullptr), m_visible(true), m_matrix(glm::mat4(1.0f)), m_shouldCalcMtx(false), m_isMouseOver(false) {}

void Node::setPos(const Vec2f& pos) {
    m_pos = pos;
    m_shouldCalcMtx = true;
}

void Node::setScaleX(float scale) {
    m_scale.x = scale;
    m_shouldCalcMtx = true;
}

void Node::setScaleY(float scale) {
    m_scale.y = scale;
    m_shouldCalcMtx = true;
}

void Node::setScale(float scale) {
    m_scale = {scale, scale};
    m_shouldCalcMtx = true;
}

void Node::setScale(const Vec2f& scale) {
    m_scale = scale;
    m_shouldCalcMtx = true;
}

void Node::setRotation(float degrees) {
    m_rotation = degrees;
    m_shouldCalcMtx = true;
}

void Node::setZOrder(int zOrder) {
    m_zOrder = zOrder;
    if (m_parent)
        m_parent->sortChildren();
}

void Node::setBoundingBox(const Vec2f& size) {
    m_boundingBox = size;
    m_shouldCalcMtx = true;
}

Vec2f Node::getScaledBoundingBox() {
    return m_boundingBox * m_scale;
}

Rectf Node::getRect() {
    // if (fmodf(m_rotation, 90.f) == 0) { // if the rect is in its place
    //     auto box = getScaledBoundingBox();
    //     return {m_pos.x - box.w * m_anchorPoint.x, m_pos.y - box.h * m_anchorPoint.y, box.w, box.h};
    // } else { // if the rect is rotated
    //     auto& box = m_boundingBox;

    //     auto topleft = m_matrix * glm::vec4(-box.w * m_anchorPoint.x, -box.h * m_anchorPoint.y, 0.f, 0.f);
    //     auto bottomright = m_matrix * glm::vec4(box.w * (1.f - m_anchorPoint.x), box.h * (1.f - m_anchorPoint.y), 0.f, 0.f);
    //     auto bottomleft = m_matrix * glm::vec4(-box.w * m_anchorPoint.x, box.h * (1.f - m_anchorPoint.y), 0.f, 0.f);
    //     auto topright = m_matrix * glm::vec4(box.w * (1.f - m_anchorPoint.x), -box.h * m_anchorPoint.y, 0.f, 0.f);

    //     auto rx = bottomleft.r;
    //     auto ry = topleft.g;
    //     auto rw = topright.r - rx;
    //     auto rh = bottomright.g - ry;

    //     return {m_pos.x + rx, m_pos.y + ry, rw, rh};
    // }

    auto box = getScaledBoundingBox();
    return {m_pos.x - box.w * m_anchorPoint.x, m_pos.y - box.h * m_anchorPoint.y, box.w, box.h};
}

void Node::setAnchorPoint(const Vec2f& anchor) {
    m_anchorPoint = anchor;
    m_shouldCalcMtx = true;
}

void Node::runAction(std::shared_ptr<Action> action) {
    action->setNode(this);
    ActionManager::get()->addAction(action);
}

void Node::removeAllActions() {
    ActionManager::get()->removeActionsForNode(this);
}

void Node::update(float dt) {
    if (m_shouldCalcMtx) {
        updateMtx();
    }
}

void Node::addChild(std::shared_ptr<Node> child) {
    child->setParent(this);

    if (m_children.size() == 0) {
        m_children.push_back(child);
    } else {
        auto childZ = child->getZOrder();

        for (auto i = m_children.size() - 1; i >= 0; i--) {
            if (m_children[i]->getZOrder() <= childZ) {
                m_children.insert(m_children.begin() + i + 1, child);
                break;
            }
        }
    }
}

void Node::addChild(std::shared_ptr<Node> child, int zOrder) {
    child->setZOrder(zOrder);
    addChild(child);
}

void Node::removeChild(int index) {
    if (index >= 0 && index < m_children.size())
        m_children.erase(m_children.begin() + index);
}

void Node::removeAllChildren() {
    m_children.clear();
}

void Node::removeFromParent() {
    if (m_parent) {
        auto& children = m_parent->getChildren();
        for (auto i = 0u; i < children.size(); i++) {
            if ((uintptr_t)children[i].get() == (uintptr_t)this) {
                m_parent->removeChild(i);
                break;
            }
        }
        m_parent = nullptr;
    }
}

void Node::setParent(Node* node) {
    removeFromParent();
    m_parent = node;
}

std::shared_ptr<Node> Node::getChildByTag(const char* tag) const {
    for (const auto child : m_children) {
        if (std::string(child->getTag()) == tag) {
            return child;
        }
    }

    return nullptr;
}

std::shared_ptr<Node> Node::getChildByIndex(int index) const {
    return index >= 0 && index < m_children.size() ? m_children[index] : nullptr;
}

void Node::sortChildren() {
    // TODO: a more optimized solution?
    std::sort(m_children.begin(), m_children.end(), [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) { return a->getZOrder() < b->getZOrder(); });
}

void Node::updateMtx() {
    m_shouldCalcMtx = false;

    auto bb = m_boundingBox * m_scale;
    m_matrix = glm::translate(glm::mat4(1.f), glm::vec3(m_pos.x, m_pos.y, 0.f));
    m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
    m_matrix = glm::translate(m_matrix, glm::vec3(-bb.w * m_anchorPoint.x, -bb.h * m_anchorPoint.y, 0.f));
    m_matrix = glm::scale(m_matrix, glm::vec3(m_scale.x, m_scale.y, 1.f));

    if (m_parent)
        m_matrix = m_parent->getMatrix() * m_matrix;

    // update matrix for children too
    for (auto c : m_children)
        c->updateMtx();
}

NS_SPECTRUM_END
