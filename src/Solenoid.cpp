#include <P1AM.h>
#include "MecLabLibrary.h"

Solenoid::Solenoid(const int slot, const int port)
  : _slot(slot), _port(port), _isExtended(false) {}

void Solenoid::extend() {
  P1.writeDiscrete(HIGH, _slot, _port);
  _isExtended = true;
}

void Solenoid::extend(int durationMs) {
  Timer.cancel(_timerHandle); // Cancel any preexisting timer

  P1.writeDiscrete(HIGH, _slot, _port);
  _isExtended = true;

  _timerHandle = Timer.start(durationMs, [this]() {
    this->retract();
  });
}

void Solenoid::retract() {
  P1.writeDiscrete(LOW, _slot, _port);
  _isExtended = false;
}

void Solenoid::retract(int durationMs) {
  Timer.cancel(_timerHandle); // Cancel any preexisting timer

  P1.writeDiscrete(LOW, _slot, _port);
  _isExtended = false;

  _timerHandle = Timer.start(durationMs, [this]() {
    this->extend();
  });
}

bool Solenoid::isExtended() {
  return _isExtended;
}

int Solenoid::getPort() {
  return _port;
}