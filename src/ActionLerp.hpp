#pragma once
#include "Action.hpp"
#include <functional>

NS_SPECTRUM_BEGIN

template <typename T>
class SPL_API ActionLerp : public Action {
  public:
    ActionLerp(EasingType easing, float duration, int repeat, const T& startVal, const T& endVal, MiniFunction<void(T)> callback)
        : Action(easing, duration, repeat), m_startVal(startVal), m_endVal(endVal), m_callback(callback) {}

    virtual void update(float dt) override {
        Action::update(dt);

        m_callback(utils::lerpValue(m_startVal, m_endVal, m_progress));
    }

  private:
    T m_startVal;
    T m_endVal;
    MiniFunction<void(T)> m_callback;
};

NS_SPECTRUM_END