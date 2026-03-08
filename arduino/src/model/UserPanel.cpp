#include "UserPanel.h"
#include <Arduino.h>
#include "config.h"

UserPanel::UserPanel(HWPlatform* pHW)
    : pHW(pHW), pResetButton(nullptr), resetPressed(false), prevResetPressed(false) {
    // Prendiamo il bottone di reset dalla piattaforma hardware
    if (pHW) {
        pResetButton = pHW->getResetButton();
        pLcd = pHW->getLcd();
    }
}

void UserPanel::init() {
    resetPressed = false;
    prevResetPressed = false;
    pLcd->init();
    pLcd->backlight();
    pLcd->noDisplay();
    turnOnDisplay();
}

void UserPanel::turnOnDisplay() {
    pLcd->display();
    pLcd->clear();
}

void UserPanel::turnOffDisplay() {
    pLcd->noDisplay();
}

void UserPanel::displayDroneInside() {
    pLcd->clear();
    pLcd->setCursor(0, 0);
    pLcd->print("DRONE INSIDE");
}

void UserPanel::displayTakeOff() {
    pLcd->clear();
    pLcd->setCursor(0, 0);
    pLcd->print("TAKE OFF");
}

void UserPanel::displayWaitingDoor() {
    pLcd->clear();
    pLcd->setCursor(0, 0);
    pLcd->print("WAITING DOOR");
}

void UserPanel::displayDroneOut() {
    pLcd->clear();
    pLcd->setCursor(0, 0);
    pLcd->print("DRONE OUT");
}

void UserPanel::displayLanding() {
    pLcd->clear();
    pLcd->setCursor(0, 0);
    pLcd->print("LANDING");
}

void UserPanel::displayAlarm() {
    pLcd->clear();
    pLcd->setCursor(0, 0);
    pLcd->print("ALARM");
}

void UserPanel::prepareToSleep() {
    pLcd->noDisplay();
}

void UserPanel::resumeFromSleeping() {
    pLcd->display();
}

void UserPanel::sync() {
    if (!pResetButton) {
        return;
    }

    prevResetPressed = resetPressed;
    resetPressed = pResetButton->isPressed();
}

bool UserPanel::isResetPressed() const {
    return resetPressed;
}

bool UserPanel::isResetPressedEdge() {
    // fronte di salita: ora premuto, prima no
    return (resetPressed && !prevResetPressed);
}
