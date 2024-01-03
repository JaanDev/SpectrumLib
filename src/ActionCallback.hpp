#pragma once
#include "Action.hpp"
#include <functional>

NS_SPECTRUM_BEGIN

class ActionCallback : public Action {
  public:
    ActionCallback(MiniFunction<void(Node*)> callback);

    virtual void update(float dt) override;

  private:
    MiniFunction<void(Node*)> m_callback;
};

NS_SPECTRUM_END