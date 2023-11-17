#include "ActionDelay.hpp"

NS_SPECTRUM_BEGIN

ActionDelay::ActionDelay(float time) : Action(EasingType::Linear, time, 1) {}

void ActionDelay::update(float dt) {
    if (m_isFinished)
        return;

    m_runTime += dt;

    if (m_runTime >= m_duration) {
        m_isFinished = true;
    }
}

NS_SPECTRUM_END
