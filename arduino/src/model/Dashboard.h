#ifndef __DASHBOARD__
#define __DASHBOARD__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "HWPlatform.h"
#include "scheduler/states.h"

class Dashboard {
public:
    Dashboard(HWPlatform* hw);

    virtual void init();   // opzionale, per impostare lo schermo iniziale

    // --- messaggi principali su LCD/LED ---

    virtual void showDroneInside();
    virtual void showDroneOut();
    virtual void showTakeOff();
    virtual void showLanding();
    virtual void showPreAlarm();
    virtual void showAlarm();

    // --- gestione LED L2 / L3 ---

    // L2 lampeggia: ogni chiamata inverte lo stato
    virtual void blinkL2();

    // Imposta L2 / L3 esplicitamente
    virtual void setL2(bool on);
    virtual void setL3(bool on);

private:
    HWPlatform* hw;

    LiquidCrystal_I2C* lcd;
    Led* l1;
    Led* l2;
    Led* l3;

    bool l2State;
};

#endif