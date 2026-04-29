#include <P1AM.h>
#include "MecLabLibrary.h"

OpticalSensor::OpticalSensor(const int slot, const int port)
  : _slot(slot), _port(port) {}

bool OpticalSensor::read() {
  return P1.readDiscrete(_slot, _port);
}

int OpticalSensor::getPort() {
  return _port;
}