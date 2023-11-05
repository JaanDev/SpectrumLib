#pragma once
#include "utils.hpp"
#include "types.hpp"
#include "Node.hpp"

NS_SPECTRUM_BEGIN

class Action {

  public:
    Action() {};
    Action(EasingType easing, float duration, int repeat);

    virtual void update(float dt);

    inline bool isFinished() const { return m_isFinished; }
    inline EasingType getEasingType() const { return m_easingType; }
    inline Node* getNode() const { return m_node; }
    virtual void setNode(Node* node) { m_node = node; }
    inline float getProgress() const { return m_runTime / m_duration; }
    inline float getEasedProgress() const { return m_progress; }
    inline int getTimesLeft() const { return m_timesLeft; }

    void reset();

  protected:
    float m_duration; // total action time
    float m_runTime;  // the time the action has been running
    float m_progress; // 0 to 1
    Node* m_node;
    EasingType m_easingType;
    int m_totalTimes; // repeat
    int m_timesLeft; // repeat
    bool m_isFinished;
};

NS_SPECTRUM_END