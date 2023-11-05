#include "ActionManager.hpp"

NS_SPECTRUM_BEGIN

ActionManager* ActionManager::instance() {
    static auto instance = std::make_shared<ActionManager>();
    return instance.get();
}

ActionManager::ActionManager() : m_actions({}) {}

void ActionManager::update(float dt) {
    for (auto action : m_actions) {
        action->update(dt);
    }
}

void ActionManager::addAction(std::shared_ptr<Action> action, Node* node) {
    action->setNode(node);
    m_actions.push_back(action);
}

void ActionManager::removeAction(std::shared_ptr<Action> action) {
    std::erase(m_actions, action);
}

NS_SPECTRUM_END
