#include "ActionSequence.hpp"

NS_SPECTRUM_BEGIN

ActionSequence::ActionSequence(std::vector<std::shared_ptr<Action>> actions, int repeat) : m_actions(actions), m_currentAction(0) {
    m_timesLeft = repeat;
    m_isFinished = false;
}

ActionSequence::ActionSequence(std::initializer_list<std::shared_ptr<Action>> actions, int repeat) : m_actions {actions}, m_currentAction(0) {
    m_timesLeft = repeat;
    m_isFinished = false;
}

void ActionSequence::update(float dt) {
    if (m_isFinished)
        return;

    auto curAction = m_actions[m_currentAction];
    curAction->update(dt);
    if (curAction->isFinished()) {
        m_currentAction++;
        if (m_currentAction == m_actions.size()) {
            m_timesLeft--;
            if (m_timesLeft == 0) {
                m_isFinished = true;
            } else {
                m_currentAction = 0;
                for (auto action : m_actions) {
                    action->reset();
                }
            }
        }
    }
}

void ActionSequence::setNode(Node* node) {
    for (auto action : m_actions) {
        action->setNode(node);
    }
}

NS_SPECTRUM_END
