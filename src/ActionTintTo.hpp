#pragma once
#include "Action.hpp"

NS_SPECTRUM_BEGIN

class ActionTintTo : public Action {
  public:
    ActionTintTo(EasingType easing, float duration, const Col3u& startCol, const Col3u& endCol);

    virtual void update(float dt) override;
    virtual void setNode(Node* node) override;

  private:
    Col3u m_startCol;
    Col3u m_endCol;
};

NS_SPECTRUM_END