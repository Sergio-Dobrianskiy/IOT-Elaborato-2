#include "HangarDoor.h"

HangarDoor::HangarDoor(ServoMotor* doorMotor)
    :   motor(doorMotor),
        openAngle(DOOR_OPEN_ANGLE),
        closedAngle(DOOR_CLOSED_ANGLE),
        openFlag(false) {

    // opzionale: se vuoi assicurarti che all'inizio sia chiusa:
    if (motor) {
        motor->on();                      // attacca il servo, se non già fatto altrove
        motor->setPosition(closedAngle);  // chiudi la porta
    }
}

void HangarDoor::setOpenAngle(int angle) {
    if (angle < 0)   angle = 0;
    if (angle > 180) angle = 180;
    openAngle = angle;
}

void HangarDoor::setClosedAngle(int angle) {
    if (angle < 0)   angle = 0;
    if (angle > 180) angle = 180;
    closedAngle = angle;
}

void HangarDoor::open() {
    if (!motor) return;

    motor->setPosition(openAngle);
    openFlag = true;
}

void HangarDoor::close() {
    if (!motor) return;

    motor->setPosition(closedAngle);
    openFlag = false;
}

bool HangarDoor::isOpen() const {
    return openFlag;
}

bool HangarDoor::isClosed() const {
    return !openFlag;
}