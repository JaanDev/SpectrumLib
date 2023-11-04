#include "Action.hpp"

NS_SPECTRUM_BEGIN

Action::Action(EasingType easing, float duration)
    : m_duration(duration), m_runTime(0.f), m_progress(0.f), m_node(nullptr), m_easingType(easing), m_isFinished(false) {}

void Action::update(float dt) {
    if (m_isFinished)
        return;

    m_runTime += dt;
    if (m_runTime >= m_duration) {
        m_isFinished = true;
        m_progress = 1.0f;
        return;
    }

    m_progress = utils::calcEasing(m_easingType, m_runTime / m_duration);
}

NS_SPECTRUM_END