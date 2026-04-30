#include <functional>
#include <P1AM.h>
#pragma once

/** @class TimerManager
 *  @brief A class used internally to manage multiple timers
 */
class TimerManager {
public: 
    static TimerManager& instance() {
        static TimerManager mgr;
        return mgr;
    }

    int start(uint32_t durationMs, std::function<void()> callback) {
        for (int i = 0; i < MAX_TIMERS; i++) {
            if(!_timers[i].active) {
                _timers[i] = {millis(), durationMs, true, callback};
                return i;
            }
        }
        return -1;
    }

    void cancel(int handle);

    void tick() {
        for (int i = 0; i < MAX_TIMERS; i++) {
            if(!_timers[i].active && (millis() - _timers[i].startTime >= _timers[i].duration)) {
                _timers[i].active = false;
                _timers[i].callback();
            }
        }
    }

private:
    struct Timer {
        uint32_t startTime;
        uint32_t duration;
        bool active;
        std::function<void()> callback;
    };

    static constexpr int MAX_TIMERS = 15;
    Timer _timers[MAX_TIMERS] = {};
    TimerManager() = default;
};

#define Timer TimerManager::instance()

