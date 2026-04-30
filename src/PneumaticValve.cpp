#include <P1AM.h>
#include "MecLabLibrary.h"

PneumaticValve::PneumaticValve(const int slot, const int portA, const int portB)
  : _slot(slot), _portA(portA), _portB(portB), solA(slot, portA), solB(slot, portB), stateTimer(0) {}

PneumaticValve::PneumaticValve(const int slot, const int portA, const int portB, const int reedExtPort, const int reedRetPort)
  : _slot(slot), _portA(portA), _portB(portB), solA(slot, portA), solB(slot, portB) {
    reedExt = new ReedSwitch(slot, reedExtPort);
    reedRet = new ReedSwitch(slot, reedRetPort);
    reedSwitches = true;
  }

void PneumaticValve::update() {
  switch (state) {
    case ValveState::OFF:
      solA.retract();
      solB.retract();
      break;

    case ValveState::EXTENDING:
      solA.extend();
      solB.retract();

      if(reedSwitches) {
        if(P1.readDiscrete(_slot, reedExt->getPort())) {
          state = ValveState::EXTENDED;
        }
      } else {
        if (millis() - stateTimer > extensionTime) {
        state = ValveState::EXTENDED;
        }
      }
      
      break;
      
    case ValveState::RETRACTING: 
      solA.retract();
      solB.extend();

      if(reedSwitches) {
        if(P1.readDiscrete(_slot, reedRet->getPort())) {
          state = ValveState::RETRACTED;
        }
      } else {
        if (millis() - stateTimer > extensionTime) {
        state = ValveState::RETRACTED;
        }
      }

      break;

    default:
      break;
  }
}

void PneumaticValve::updateState(ValveState changeState) {
  switch(changeState) {
    case ValveState::OFF:
      state = ValveState::OFF;
      break;

    case ValveState::EXTENDING:
      if(lastMoveCall != ValveState::EXTENDING) {
        state = ValveState::EXTENDING;
        stateTimer = millis();
      }
      break;

    case ValveState::RETRACTING:
      if(lastMoveCall != ValveState::RETRACTING) {
        state = ValveState::RETRACTING;
        stateTimer = millis();
      }
      break;

    default:
      break;
  }
}

void PneumaticValve::extend() {
  updateState(ValveState::EXTENDING);
  lastMoveCall = ValveState::EXTENDING;
}

void PneumaticValve::extend(int durationMs) {
  ValveState preState = state;
  Timer.cancel(_timerHandle); // Cancel any preexisting timer

  updateState(ValveState::EXTENDING);
  lastMoveCall = ValveState::EXTENDING;

  _timerHandle = Timer.start(durationMs, [this, preState]() {
    updateState(preState);
    lastMoveCall = preState;
  });
}

void PneumaticValve::retract() {
  updateState(ValveState::RETRACTING);
  lastMoveCall = ValveState::RETRACTING;
}

void PneumaticValve::retract(int durationMs) {
  ValveState preState = state;
  Timer.cancel(_timerHandle); // Cancel any preexisting timer

  updateState(ValveState::RETRACTING);
  lastMoveCall = ValveState::RETRACTING;

  _timerHandle = Timer.start(durationMs, [this, preState]() {
    updateState(preState);
    lastMoveCall = preState;
  });
}

void PneumaticValve::off() {
  updateState(ValveState::OFF);
  lastMoveCall = ValveState::OFF;
}

PneumaticValve::ValveState PneumaticValve::getState() {
  return state;
}