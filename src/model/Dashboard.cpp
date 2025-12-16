#include "Dashboard.h"

Dashboard::Dashboard(HWPlatform* hw)
    :   hw(hw),
        lcd(nullptr),
        l1(nullptr),
        l2(nullptr),
        l3(nullptr),
        l2State(false) {

    // prendo subito i puntatori dai getter dell'HWPlatform
    if (hw) {
        lcd = hw->getOperatorLcd();
        l1  = hw->getL1();
        l2  = hw->getL2();
        l3  = hw->getL3();
    }
}

void Dashboard::init() {
    // stato iniziale: DRONE INSIDE, sistema normale
    if (lcd) {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("DRONE INSIDE");
        lcd->setCursor(0, 1);
        lcd->print("STATE: NORMAL   ");
    }

    if (l1) l1->switchOn();   // sistema acceso
    if (l2) l2->switchOff();
    if (l3) l3->switchOff();
}

/* --------- Messaggi principali --------- */

void Dashboard::showDroneInside() {
    if (lcd) {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("DRONE INSIDE");
        lcd->setCursor(0, 1);
        lcd->print("STATE: NORMAL   ");
    }
    if (l2) l2->switchOff();
}

void Dashboard::showDroneOut() {
    if (lcd) {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("DRONE OUT");
        lcd->setCursor(0, 1);
        lcd->print("STATE: NORMAL   ");
    }
    if (l2) l2->switchOff();
}

void Dashboard::showTakeOff() {
    if (lcd) {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("TAKE OFF");
        lcd->setCursor(0, 1);
        lcd->print("PLEASE WAIT     ");
    }
  // durante take-off L2 deve blinkare: sarà il task a chiamare blinkL2()
}

void Dashboard::showLanding() {
    if (lcd) {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("LANDING");
        lcd->setCursor(0, 1);
        lcd->print("PLEASE WAIT     ");
    }
  // anche qui L2 blink, gestito dal task
}

void Dashboard::showPreAlarm() {
    if (lcd) {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("TEMP HIGH");
        lcd->setCursor(0, 1);
        lcd->print("PRE-ALARM       ");
    }
    if (l3) l3->switchOff();   // rosso solo in ALLARM pieno
}

void Dashboard::showAlarm() {
    if (lcd) {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("ALLARM");
        lcd->setCursor(0, 1);
        lcd->print("CHECK HANGAR    ");
    }
    if (l3) l3->switchOn();    // rosso acceso in ALLARM
}

/* --------- LED L2 / L3 --------- */

void Dashboard::blinkL2() {
    if (!l2) return;

    l2State = !l2State;
    if (l2State) {
        l2->switchOn();
    } else {
        l2->switchOff();
    }
}

void Dashboard::setL2(bool on) {
    if (!l2) return;
    l2State = on;
    if (on) {
        l2->switchOn();
    } else {
        l2->switchOff();
    }
}

void Dashboard::setL3(bool on) {
    if (!l3) return;
    if (on) {
        l3->switchOn();
    } else {
        l3->switchOff();
    }
}