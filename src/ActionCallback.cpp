#include "ActionCallback.hpp"

NS_SPECTRUM_BEGIN

ActionCallback::ActionCallback(MiniFunction<void(Node*)> callback) : Action(EasingType::Linear, 0.f, 1), m_callback(callback) {}

void ActionCallback::update(float dt) {
    if (m_isFinished)
        return;

    // lol
    m_isFinished = true;
    m_callback(m_node);
}

NS_SPECTRUM_END
