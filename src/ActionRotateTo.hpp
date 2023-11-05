#pragma once
#include "Action.hpp"

NS_SPECTRUM_BEGIN

class ActionRotateTo : public Action {
  public:
    ActionRotateTo(EasingType easing, float duration, int repeat, float startRot, float endRot);

    virtual void update(float dt) override;
    virtual void setNode(Node* node) override;

  private:
    float m_startRot;
    float m_endRot;
};

NS_SPECTRUM_END