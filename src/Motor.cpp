#include <P1AM.h>
#include "MecLabLibrary.h"

Motor::Motor(const int slot, const int port, const int revPort)
  : _slot(slot), _port(port), _revPort(revPort), state(MotorState::OFF) {}

void Motor::forward() {
  P1.writeDiscrete(LOW, _slot, _revPort);
  P1.writeDiscrete(HIGH, _slot, _port);
  state = MotorState::FORWARD;
}

void Motor::reverse() {
  P1.writeDiscrete(HIGH, _slot, _revPort);
  P1.writeDiscrete(HIGH, _slot, _port);
  state = MotorState::REVERSE;
}

void Motor::stop() {
  P1.writeDiscrete(LOW, _slot, _revPort);
  P1.writeDiscrete(LOW, _slot, _port);
  state = MotorState::OFF;
}

Motor::MotorState Motor::direction() {
  return state;
}