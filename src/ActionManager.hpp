#pragma once
#include <memory>
#include <vector>
#include "utils.hpp"
#include "Action.hpp"

NS_SPECTRUM_BEGIN

class ActionManager {
  public:
    static ActionManager* instance();
    ActionManager();

    void update(float dt);

    void addAction(std::shared_ptr<Action> action);
    void removeAction(std::shared_ptr<Action> action);
    void removeActionsForNode(Node* node);

  private:
    std::vector<std::shared_ptr<Action>> m_actions;
};

NS_SPECTRUM_END