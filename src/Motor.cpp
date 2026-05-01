#include <P1AM.h>
#include "MecLabLibrary.h"

Motor::Motor(const int slot, const int port, const int revPort)
  : _slot(slot), _port(port), _revPort(revPort), state(MotorState::OFF) {}

void Motor::forward() {
  P1.writeDiscrete(LOW, _slot, _revPort);
  P1.writeDiscrete(HIGH, _slot, _port);
  state = MotorState::FORWARD;
}

void Motor::forward(int durationMs) {
  MotorState preState = state;
  Timer.cancel(_timerHandle); // Cancel any preexisting timer
  
  P1.writeDiscrete(LOW, _slot, _revPort);
  P1.writeDiscrete(HIGH, _slot, _port);
  state = MotorState::FORWARD;

  _timerHandle = Timer.start(durationMs, [this, preState]() {
    preState == MotorState::REVERSE ? this->reverse() : this->stop();
  });
}

void Motor::reverse() {
  P1.writeDiscrete(HIGH, _slot, _revPort);
  P1.writeDiscrete(HIGH, _slot, _port);
  state = MotorState::REVERSE;
}

void Motor::reverse(int durationMs) {
  MotorState preState = state;
  Timer.cancel(_timerHandle); // Cancel any preexisting timer

  P1.writeDiscrete(HIGH, _slot, _revPort);
  P1.writeDiscrete(HIGH, _slot, _port);
  state = MotorState::REVERSE;

  _timerHandle = Timer.start(durationMs, [this, preState]() {
    preState == MotorState::FORWARD ? this->forward() : this->stop();
  });
}

void Motor::stop() {
  P1.writeDiscrete(LOW, _slot, _revPort);
  P1.writeDiscrete(LOW, _slot, _port);
  state = MotorState::OFF;
}

void Motor::stop(int durationMs) {
  MotorState preState = state;
  Timer.cancel(_timerHandle); // Cancel any preexisting timer

  P1.writeDiscrete(LOW, _slot, _revPort);
  P1.writeDiscrete(LOW, _slot, _port);
  state = MotorState::OFF;

  _timerHandle = Timer.start(durationMs, [this, preState]() {
    preState == MotorState::FORWARD ? this->forward() : this->reverse();
  });
}

Motor::MotorState Motor::direction() {
  return state;
}