#pragma once
#include "Action.hpp"

NS_SPECTRUM_BEGIN

class ActionScaleTo : public Action {
  public:
    ActionScaleTo(EasingType easing, float duration, int repeat, float startScale, float endScale);

    virtual void update(float dt) override;
    virtual void setNode(Node* node) override;

  private:
    float m_startScale;
    float m_endScale;
};

NS_SPECTRUM_END