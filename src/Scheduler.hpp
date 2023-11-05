#pragma once
#include <functional>
#include "utils.hpp"
#include "types.hpp"

NS_SPECTRUM_BEGIN

struct Timer {
    float interval;
    int timesLeft;
    std::function<void()> callback;
    unsigned int id;
    float timeLeft;
};

class Scheduler {
  public:
    static Scheduler* instance();

    // returns the timer id which can be used to unschedule it
    // timesLeft = -1 => infinite repeat
    unsigned int schedule(float interval, int timesLeft, std::function<void()> callback);
    void unschedule(unsigned int id);
    void unscheduleAll();

    // internal
    void update(float dt);

    void setAFKCallback(std::function<void()> callback);
    inline float getAFKInterval() const;
    void setAFKInterval(float interval);

  private:
    unsigned int m_nextTimerID; // 0 by default, += 1 after each created timer
    std::vector<Timer> m_timers;
    float m_AFKInterval;
    std::function<void()> m_AFKCallback;
};

NS_SPECTRUM_END