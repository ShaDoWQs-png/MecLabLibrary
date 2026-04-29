#include <P1AM.h>
#include "MecLabLibrary.h"

ReedSwitch::ReedSwitch(const int slot, const int port)
  : _slot(slot), _port(port) {}

bool ReedSwitch::read() {
  return P1.readDiscrete(_slot, _port);
}

int ReedSwitch::getPort() {
  return _port;
}