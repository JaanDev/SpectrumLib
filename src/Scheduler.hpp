#pragma once
#include <functional>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

struct Timer {
    float interval;
    int repeatLeft;
    MiniFunction<void()> callback;
    unsigned int id;
    float timeLeft;
};

class SPL_API Scheduler {
  public:
    static Scheduler* get();
    Scheduler();

    // returns the timer id which can be used to unschedule it
    // timesRepeat = -1 => infinite repeat
    unsigned int schedule(float interval, int timesRepeat, MiniFunction<void()> callback);
    void unschedule(unsigned int id);
    void unscheduleAll();

    // internal
    void update(float dt);

    void setAFKCallback(MiniFunction<void()> callback);
    inline float getAFKInterval() const { return m_AFKInterval; }
    void setAFKInterval(float interval);

  private:
    unsigned int m_nextTimerID; // 0 by default, += 1 after each created timer
    std::vector<Timer> m_timers;
    float m_AFKInterval;
    float m_AFKTime; // current time user is afk
    MiniFunction<void()> m_AFKCallback;
    bool m_isAFK;
};

NS_SPECTRUM_END