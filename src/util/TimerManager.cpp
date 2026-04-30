#include "Managers.hpp"

void TimerManager::cancel(int handle) {
    if(handle >= 0 && handle < MAX_TIMERS) {
        _timers[handle].active = false;
    }
}