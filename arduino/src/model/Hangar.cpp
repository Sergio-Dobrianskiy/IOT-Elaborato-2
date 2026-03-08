#include "Arduino.h"

#include "Hangar.h"
#include "config.h"
#include "kernel/Logger.h"

bool SVILUPPO = true;

Hangar::Hangar(HWPlatform* hw)
    : pHW(hw),
      droneState(DroneState::REST),
      hangarState(HangarState::NORMAL),
      pResetButton(pHW->getResetButton()) {}

void Hangar::init() {
    L1isOn = false;
    L2isBlinking = false;
    L3isOn = false;

    alarmRaised = false;

    pHW->getHangarDoorMotor()->motorOn();
    doorOpen = true;  // serve per far funzionare la prima volta closeDoor();
    closeDoor();
    if (SVILUPPO) {
        Serial.println("Door and Led TEST");

        pHW->getL1()->switchOn();
        pHW->getL2()->switchOn();
        pHW->getL3()->switchOn();

        delay(1000);

        openDoor();

        delay(1000);

        closeDoor();
        pHW->getL1()->switchOff();
        pHW->getL2()->switchOff();
        pHW->getL3()->switchOff();
    }
    Serial.println("Door is READY");
    L1isOn = true;
    droneState = DroneState::REST;
    hangarState = HangarState::NORMAL;
}

/* --------- Stato drone --------- */

void Hangar::setDroneState(DroneState state) {
    this->droneState = state;
}

DroneState Hangar::getDroneState() {
    return this->droneState;
}

/* --------- Porta hangar --------- */

void Hangar::openDoor() {
    auto motor = pHW->getHangarDoorMotor();
    if (motor && !doorOpen) {
        motor->setPosition(DOOR_OPEN_ANGLE);
        doorOpen = true;
    } else {
        Serial.println("NO MOTOR");
    }
}

void Hangar::closeDoor() {
    auto motor = pHW->getHangarDoorMotor();
    if (motor && doorOpen) {
        motor->setPosition(DOOR_CLOSED_ANGLE);
        doorOpen = false;
    } else {
        Serial.println("NO MOTOR");
    }
}

bool Hangar::isDoorOpen() {
    return doorOpen;
}

/* --------- Letture sensori --------- */

float Hangar::getDistance() {
    auto sonar = pHW->getDDD();
    if (!sonar) {
        return SONAR_NO_OBJ_DETECTED;
    }
    return sonar->getDistance();
}

bool Hangar::isDroneAbove() {
    auto pir = pHW->getDPD();
    if (!pir) {
        return false;
    }
    pir->sync();
    return pir->isDetected();
}

float Hangar::getTemperature() {
    auto temperatureSensor = pHW->getTempSensor();
    if (!temperatureSensor) {
        return NAN;
    }
    return temperatureSensor->getTemperature();
}

/* --------- Stato hangar / allarmi --------- */

void Hangar::setHangarState(HangarState state) {
    this->hangarState = state;
}

HangarState Hangar::getHangarState() {
    return this->hangarState;
}

void Hangar::setL1On() {
    this->L1isOn = true;
}
void Hangar::setL2Blinking() {
    this->L2isBlinking = true;
}
void Hangar::setL3On() {
    this->L3isOn = true;
}

void Hangar::setL1Off() {
    this->L1isOn = false;
}
void Hangar::setL2Off() {
    this->L2isBlinking = false;
}
void Hangar::setL3Off() {
    this->L3isOn = false;
}

void Hangar::raiseAlarm() {
    this->alarmRaised = true;
}

void Hangar::resetAlarm() {
    this->alarmRaised = false;
}

void Hangar::manageAlarm() {
    if (alarmRaised && droneState != DroneState::TAKING_OFF && droneState != DroneState::LANDING &&
        droneState != DroneState::WAITING) {
        hangarState = HangarState::ALARM;
    } else {
        hangarState = HangarState::NORMAL;
    }
}

void Hangar::manageLeds() {
    // Led1 Verde
    if (L1isOn) {
        pHW->getL1()->switchOn();
    } else {
        pHW->getL1()->switchOff();
    }

    // Led2 Verde
    if (droneState == DroneState::TAKING_OFF || droneState == DroneState::LANDING) {
        pHW->getL2()->blink(L2_BLINK_PERIOD);
    } else {
        pHW->getL2()->stopBlinking();
    }

    // Led3 Rosso
    if (hangarState == HangarState::ALARM) {
        pHW->getL3()->switchOn();
    } else {
        pHW->getL3()->switchOff();
    }
}

void Hangar::manageDoor() {
    switch (doorState) {
        case DoorState::OPEN:
            Logger.log(F("[DO] Door is Open"));
            break;
        case DoorState::OPENING:
            this->openDoor();
            Logger.log(F("[DO] opening door"));
            break;
        case DoorState::CLOSED:
            Logger.log(F("[DO] Door is Closed"));
            break;
        case DoorState::CLOSING:
            this->closeDoor();
            Logger.log(F("[DO] closing door"));
            break;

        default:
            break;
    }
}

ButtonImpl* Hangar::getResetButton() {
    //  return this->pHW->getResetButton();
    return this->pResetButton;
}

void Hangar::setDoorState(DoorState state) {
    this->doorState = state;
    this->manageDoor();
}

DoorState Hangar::getDoorState() {
    return this->doorState;
}

void Hangar::sync() {
    manageAlarm();
    manageLeds();
}
