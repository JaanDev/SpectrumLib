#pragma once
#include "Action.hpp"

NS_SPECTRUM_BEGIN

class SPL_API ActionDelay : public Action {
  public:
    ActionDelay(float time);

    virtual void update(float dt) override;
};

NS_SPECTRUM_END