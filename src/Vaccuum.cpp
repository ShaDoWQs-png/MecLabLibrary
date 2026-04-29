#include <P1AM.h>
#include "MecLabLibrary.h"

#define SUCK true
#define NOTSUCK false

Vaccuum::Vaccuum(const int slot, const int port) 
  : _slot(slot), _port(port) {}

void Vaccuum::suck() {
    P1.writeDiscrete(HIGH, _slot, _port);
    TheSucker = SUCK;
}

void Vaccuum::notsuck() {
    P1.writeDiscrete(LOW, _slot, _port);
    TheSucker = NOTSUCK;
}

bool Vaccuum::getState() {
    return TheSucker;
}