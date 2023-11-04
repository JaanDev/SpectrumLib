#include "Node.hpp"

NS_SPECTRUM_BEGIN

Node::Node()
    : m_pos({0.f, 0.f}), m_boundingBox({0, 0}), m_anchorPoint({.5f, .5f}), m_scale({1.f, 1.f}), m_rotation(0.f), m_opacity(1.f),
      m_objectLimit(UINT_MAX), m_zOrder(0), m_tag(""), m_children({}), m_parent(nullptr), m_visible(true) {}

void Node::setPos(const Vec2f& pos) {}

void Node::setScaleX(float scale) {}

void Node::setScaleY(float scale) {}

void Node::setScale(float scale) {}

void Node::setScale(const Vec2f& scale) {}

void Node::setRotation(float degrees) {}

void Node::setVisible(bool visible) {}

void Node::setOpacity(float opacity) {}

void Node::setZOrder(int zOrder) {}

void Node::setObjectLimit(unsigned int objectlimit) {}

void Node::setBoundingBox(const Sizef& size) {}

Sizef Node::getScaledBoundingBox() {
    return Sizef();
}

void Node::setAnchorPoint(const Vec2f& anchor) {}

void Node::setTag(const char* tag) {}

void Node::runAction(std::shared_ptr<Action> action) {}

void Node::addChild(std::shared_ptr<Node> child) {}

void Node::addChild(std::shared_ptr<Node> child, int zOrder) {}

void Node::removeChild(int index) {}

void Node::removeAllChildren() {}

void Node::removeFromParent() {}

NS_SPECTRUM_END
