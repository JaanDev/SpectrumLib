#pragma once
#include "Action.hpp"

NS_SPECTRUM_BEGIN

class ActionScaleTo : public Action {
  public:
    ActionScaleTo(EasingType easing, float duration, float startScale, float endScale);

    virtual void update(float dt) override;

  private:
    float m_startScale;
    float m_endScale;
};

NS_SPECTRUM_END