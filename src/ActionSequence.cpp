#include "ActionSequence.hpp"

NS_SPECTRUM_BEGIN

ActionSequence::ActionSequence(std::vector<std::shared_ptr<Action>> actions) : m_actions(actions), m_currentAction(0) {}

void ActionSequence::update(float dt) {
    if (m_currentAction >= m_actions.size())
        return;

    auto curAction = m_actions[m_currentAction];
    curAction->update(dt);
    if (curAction->isFinished())
        m_currentAction++;
}

void ActionSequence::setNode(Node* node) {
    for (auto action : m_actions) {
        action->setNode(node);
    }
}

NS_SPECTRUM_END
