#include "ActionMoveTo.hpp"

NS_SPECTRUM_BEGIN

ActionMoveTo::ActionMoveTo(EasingType easing, float duration, int repeat, const Vec2f& startPos, const Vec2f& endPos) : Action(easing, duration, repeat), m_startPos(startPos), m_endPos(endPos) {}

void ActionMoveTo::update(float dt) {
    Action::update(dt);

    m_node->setPos(utils::lerpValue(m_startPos, m_endPos, m_progress));
}

void ActionMoveTo::setNode(Node* node) {
    Action::setNode(node);

    m_node->setPos(utils::lerpValue(m_startPos, m_endPos, m_progress));
}

NS_SPECTRUM_END