#include "Scheduler.hpp"

#include <memory>

NS_SPECTRUM_BEGIN

Scheduler* Scheduler::instance() {
    static auto instance = std::make_unique<Scheduler>();
    return instance.get();
}

Scheduler::Scheduler()
    : m_nextTimerID(0), m_timers({}), m_AFKInterval(0.f), m_AFKCallback(nullptr), m_AFKTime(0.f), m_isAFK(false) {}

unsigned int Scheduler::schedule(float interval, int timesRepeat, std::function<void()> callback) {
    m_timers.push_back({interval, timesRepeat, callback, m_nextTimerID, interval});
    // TODO: return m_nextTimerID++?
    m_nextTimerID++;
    return m_nextTimerID - 1;
}

void Scheduler::unschedule(unsigned int id) {
    auto it = std::find_if(m_timers.begin(), m_timers.end(), [id](const Timer& timer) { return timer.id == id; });
    if (it != m_timers.end())
        m_timers.erase(it);
}

void Scheduler::unscheduleAll() {
    m_timers.clear();
}

void Scheduler::update(float dt) {
    // TODO: somehow get if the user was afk this moment (probs with InputDispatcher, like if no events were processed)
    auto isUserAfkRn = false;

    if (isUserAfkRn) {
        m_AFKTime += dt;
    } else {
        m_isAFK = false;
        m_AFKTime = 0.f;
    }

    if (!m_isAFK && m_AFKTime >= m_AFKInterval) {
        m_AFKCallback();
        m_isAFK = true;
    }

    for (auto it = m_timers.begin(); it != m_timers.end();) {
        bool go = true;

        Timer& timer = *it;

        timer.timeLeft -= dt;
        if (timer.timeLeft <= 0.f) {
            timer.callback();

            timer.repeatLeft--;
            if (timer.repeatLeft == 0) {
                m_timers.erase(it);
                go = false;
            } else {
                timer.timeLeft = timer.interval;
            }
        }

        if (go)
            it++;
    }
}

void Scheduler::setAFKCallback(std::function<void()> callback) {
    m_AFKCallback = callback;
}

void Scheduler::setAFKInterval(float interval) {
    m_AFKInterval = interval;
}

NS_SPECTRUM_END
