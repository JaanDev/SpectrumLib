#include "ActionScaleTo.hpp"

NS_SPECTRUM_BEGIN

ActionScaleTo::ActionScaleTo(EasingType easing, float duration, int repeat, float startScale, float endScale) : Action(easing, duration, repeat), m_startScale(startScale), m_endScale(endScale) {}

void ActionScaleTo::update(float dt) {
    Action::update(dt);

    m_node->setScale(utils::lerpValue(m_startScale, m_endScale, m_progress));
}

void ActionScaleTo::setNode(Node* node) {
    Action::setNode(node);
    m_node->setScale(utils::lerpValue(m_startScale, m_endScale, m_progress));
}

NS_SPECTRUM_END