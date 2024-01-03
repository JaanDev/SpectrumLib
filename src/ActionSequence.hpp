#pragma once
#include "Action.hpp"

NS_SPECTRUM_BEGIN

class SPL_API ActionSequence : public Action {
  public:
    ActionSequence(std::vector<std::shared_ptr<Action>> actions, int repeat);

    virtual void update(float dt) override;
    virtual void setNode(Node* node) override;

  private:
    std::vector<std::shared_ptr<Action>> m_actions;
    int m_currentAction;
};

NS_SPECTRUM_END