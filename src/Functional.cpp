#include "MecLabLibrary.h"

void Function::wait(int durationMs, std::function<void()> callback) {
    static int _timerHandle;
    
    _timerHandle= Timer.start(durationMs, [callback]() {
        callback();
    });
}