#pragma once
#include "Action.hpp"

NS_SPECTRUM_BEGIN

class ActionMoveTo : public Action {
  public:
    ActionMoveTo(EasingType easing, float duration, const Vec2f& startPos, const Vec2f& endPos);

    virtual void update(float dt) override;

  private:
    Vec2f m_startPos;
    Vec2f m_endPos;
};

NS_SPECTRUM_END