#include <P1AM.h>
#include "MecLabLibrary.h"

SuctionArm::SuctionArm(PneumaticValve& valveX, PneumaticValve& valveY, Vaccuum& vac) {
        _valveX = &valveX;
        _valveY = &valveY;
        _vac = &vac;
    }

void SuctionArm::pick() {
    _valveY->extend();

    while(_valveY->getState() != PneumaticValve::ValveState::EXTENDED) {
        _valveY->update();
    }

    _vac->suck();
    delay(500);
    _valveY->retract();
}

void SuctionArm::place() {
    _valveY->extend();
    
    while(_valveY->getState() != PneumaticValve::ValveState::EXTENDED) {
        _valveY->update();
    }

    _vac->notsuck();
    delay(500);
    _valveY->retract();
}

void SuctionArm::transferObject() {
    if(_valveX->getState() == PneumaticValve::ValveState::EXTENDED) {
        _valveY->extend();

        while(_valveY->getState() != PneumaticValve::ValveState::EXTENDED) {
            _valveY->update();
            _valveX->update();
        }

        _vac->suck();
        delay(500);

        _valveY->retract();
        _valveX->retract();

        while(_valveX->getState() != PneumaticValve::ValveState::RETRACTED) {
            _valveY->update();
            _valveX->update();
        }

        _valveY->extend();

        while(_valveY->getState() != PneumaticValve::ValveState::EXTENDED) {
            _valveY->update();
            _valveX->update();
        }

        _vac->notsuck();
        delay(500);
        _valveY->retract();
    }
}