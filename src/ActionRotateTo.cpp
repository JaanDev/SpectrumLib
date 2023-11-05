#include "ActionRotateTo.hpp"

NS_SPECTRUM_BEGIN

ActionRotateTo::ActionRotateTo(EasingType easing, float duration, float startRot, float endRot)
    : Action(easing, duration), m_startRot(startRot), m_endRot(endRot) {}

void ActionRotateTo::update(float dt) {
    Action::update(dt);

    m_node->setRotation(utils::lerpValue(m_startRot, m_endRot, m_progress));
}

void ActionRotateTo::setNode(Node* node) {
    Action::setNode(node);
    m_node->setRotation(utils::lerpValue(m_startRot, m_endRot, m_progress));
}

NS_SPECTRUM_END