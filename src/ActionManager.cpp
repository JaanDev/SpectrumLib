#include "ActionManager.hpp"

#include <algorithm>

NS_SPECTRUM_BEGIN

ActionManager* ActionManager::instance() {
    static auto instance = std::make_unique<ActionManager>();
    return instance.get();
}

ActionManager::ActionManager() : m_actions({}) {}

void ActionManager::update(float dt) {
    for (auto it = m_actions.begin();;) {
        if (it == m_actions.end())
            break;

        bool go = true;

        auto action = *it;
        action->update(dt);
        if (action->isFinished()) {
            m_actions.erase(it);
            go = false;
        }

        if (go)
            it++;
    }
}

void ActionManager::addAction(std::shared_ptr<Action> action) {
    m_actions.push_back(action);
}

void ActionManager::removeAction(std::shared_ptr<Action> action) {
    if (auto it = std::find(m_actions.begin(), m_actions.end(), action); it != m_actions.end())
        m_actions.erase(it);
}

NS_SPECTRUM_END
