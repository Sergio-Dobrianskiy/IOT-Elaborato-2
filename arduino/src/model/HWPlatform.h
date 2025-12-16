/* Contiene tutti gli oggetti device e usa i pin di config.h. */
#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include"config.h"

#include "devices/button/Button.h"
#include "devices/led/Led.h"
#include "devices/pir/Pir.h"
#include "devices/proxymitySensor/sonar.h"
#include "devices/thermometer/thermometerDHT11.h"
#include "devices/servoMotor/servoMotorImpl.h"

// #include <Wire.h>                 // both needed for the
#include <LiquidCrystal_I2C.h>    // LCD screen

class HWPlatform {

public:
    HWPlatform();

    virtual void init();   // inizializza tutto l'hardware (lcd, pins, ecc.)
    virtual void test();   // inizializza i test

    // --- accesso ai device ---
    virtual Sonar* getDDD();
    virtual Pir* getDPD();
    virtual ServoMotor* getHangarDoorMotor();
    virtual ThermometerDHT11* getTempSensor();
    virtual LiquidCrystal_I2C* getOperatorLcd();
    virtual Led* getL1();    // verde
    virtual Led* getL2();    // verde blink durante takeoff/landing
    virtual Led* getL3();    // rosso allarme
    virtual Button* getResetButton();

private:
    // istanze concrete dei device
    Sonar* pDdd;
    Pir* pDpd;
    ServoMotor* pDoorMotor;
    ThermometerDHT11* pTempSensor;
    LiquidCrystal_I2C* pLcd;
    Led* pL1;
    Led* pL2;
    Led* pL3;
    Button* pResetButton;
};

#endif