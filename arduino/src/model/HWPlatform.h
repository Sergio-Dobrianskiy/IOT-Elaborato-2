/* Contiene tutti gli oggetti device e usa i pin di config.h. */
#ifndef __HW_PLATFORM__
#define __HW_PLATFORM__

#include "config.h"  // pins

#include "devices/button/ButtonImpl.h"              // button
#include "devices/led/Led.h"                        // led
#include "devices/pir/Pir.h"                        // pir
#include "devices/proximity_sensor/Sonar.h"         // proximity sensor
#include "devices/servo_motor/servo_motor.h"        // servo motor
#include "devices/temperature_sensor/TempSensor.h"  // temperature sensor

#include <LiquidCrystal_I2C.h>  // LCD screen
#include <Wire.h>               // both needed for the

class HWPlatform {
public:
    HWPlatform();

    void init();  // inizializza tutto l'hardware (lcd, pins, ecc.)
    void test();  // inizializza i test

    /* ---------------------------------- ACCESSO AI DEVICE ---------------------------------- */

    // Drone Distance Detector (sonar dentro l’hangar)
    Sonar* getDDD();

    // Drone Presence Detector (PIR sopra l’hangar)
    Pir* getDPD();

    // Motore porta hangar
    ServoMotor* getHangarDoorMotor();

    // Sensore temperatura (DHT11 tramite TempSensorDHT11)
    TempSensor* getTempSensor();

    // LCD dell’operatore
    LiquidCrystal_I2C* getLcd();

    // LED
    Led* getL1();  // verde sempre acceso
    Led* getL2();  // verde blink durante takeoff/landing
    Led* getL3();  // rosso allarme

    // Bottone di reset allarme
    ButtonImpl* getResetButton();

private:
    // istanze concrete dei device
    Sonar* pDdd;
    Pir* pDpd;
    ServoMotor* pDoorMotor;
    TempSensor* pTempSensor;
    LiquidCrystal_I2C* pLcd;
    Led* pL1;
    Led* pL2;
    Led* pL3;
    ButtonImpl* pResetButton;
};

#endif
