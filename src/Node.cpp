#include "Node.hpp"

#include <glm/gtx/transform.hpp>
#include <algorithm>
#include <string>
#include "logger.hpp"

NS_SPECTRUM_BEGIN

Node::Node()
    : m_pos({0.f, 0.f}), m_boundingBox({0, 0}), m_anchorPoint({.5f, .5f}), m_scale({1.f, 1.f}), m_rotation(0.f), m_opacity(1.f),
      m_objectLimit(UINT_MAX), m_zOrder(0), m_tag(""), m_children({}), m_parent(nullptr), m_visible(true),
      m_matrix(glm::mat4(1.0f)), m_shouldSortChildren(false), m_shouldCalcMtx(true) {}

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

void Node::setOpacity(float opacity) {
    m_opacity = opacity;
}

void Node::setZOrder(int zOrder) {
    m_zOrder = zOrder;
    if (m_parent)
        m_parent->setShouldSortChildren(true);
}

void Node::setBoundingBox(const Sizef& size) {
    m_boundingBox = size;
    m_shouldCalcMtx = true;
}

Sizef Node::getScaledBoundingBox() {
    return m_boundingBox * m_scale;
}

void Node::setAnchorPoint(const Vec2f& anchor) {
    m_anchorPoint = anchor;
    m_shouldCalcMtx = true;
}

void Node::runAction(std::shared_ptr<Action> action) {}

void Node::update(float dt) {
    if (m_shouldSortChildren)
        sortChildren();

    if (m_shouldCalcMtx) {
        m_shouldCalcMtx = false;
        auto bb = m_boundingBox * m_scale;

        m_matrix = glm::translate(glm::mat4(1.f), glm::vec3(m_pos.x, m_pos.y, 0.f));
        m_matrix = glm::rotate(m_matrix, m_rotation, glm::vec3(0.f, 0.f, 1.f));
        m_matrix = glm::translate(m_matrix, glm::vec3(-bb.w * m_anchorPoint.x, -bb.h * m_anchorPoint.y, 0.f));
        m_matrix = glm::scale(m_matrix, glm::vec3(m_scale.x, m_scale.y, 1.f));
    }
}

void Node::addChild(std::shared_ptr<Node> child) {
    m_shouldSortChildren = true;
    child->setParent(this);
    m_children.push_back(child);
}

void Node::addChild(std::shared_ptr<Node> child, int zOrder) {
    m_shouldSortChildren = true;
    child->setZOrder(zOrder);
    child->setParent(this);
    m_children.push_back(child);
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
    m_shouldSortChildren = false;
    // TODO: a more optimized solution?
    std::sort(m_children.begin(), m_children.end(),
              [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) { return a->getZOrder() < b->getZOrder(); });
}

NS_SPECTRUM_END
