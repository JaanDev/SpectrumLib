#pragma once
#include "Action.hpp"
#include <functional>

NS_SPECTRUM_BEGIN

class ActionCallback : public Action {
  public:
    ActionCallback(std::function<void(Node*)> callback);

    virtual void update(float dt) override;

  private:
    std::function<void(Node*)> m_callback;
};

NS_SPECTRUM_END