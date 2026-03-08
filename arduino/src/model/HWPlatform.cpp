#include "HWPlatform.h"
#include <Arduino.h>
#include "devices/button/ButtonImpl.h"
#include "devices/led/Led.h"
#include "devices/pir/Pir.h"
#include "devices/proximity_sensor/Sonar.h"
#include "devices/servo_motor/servo_motor_impl.h"
#include "devices/temperature_sensor/TemperatureSensorDHT11.h"

void wakeUp() {}

HWPlatform::HWPlatform() {
    pDdd = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, MAX_TIME_US);
    pDpd = new Pir(PIR_PIN);
    pDoorMotor = new ServoMotorImpl(SERVO_PIN);
    pTempSensor = new TempSensorDHT11(TEMP_PIN);
    pLcd = new LiquidCrystal_I2C(LCD_ADDR, 16, 2);
    pL1 = new Led(L1_PIN);
    pL2 = new Led(L2_PIN);
    pL3 = new Led(L3_PIN);
    pResetButton = new ButtonImpl(BUTTON_PIN);
    Serial.println("HWPlatform istanziata");
}

void HWPlatform::init() {
    pLcd->init();
    pLcd->backlight();
    Serial.println("HWPlatform inizializzata");
}

ButtonImpl* HWPlatform::getResetButton() {
    return this->pResetButton;
}

Led* HWPlatform::getL1() {
    return this->pL1;
}

Led* HWPlatform::getL2() {
    return this->pL2;
}

Led* HWPlatform::getL3() {
    return this->pL3;
}

LiquidCrystal_I2C* HWPlatform::getLcd() {
    return this->pLcd;
}

TempSensor* HWPlatform::getTempSensor() {
    return this->pTempSensor;
}

ServoMotor* HWPlatform::getHangarDoorMotor() {
    return this->pDoorMotor;
}

Sonar* HWPlatform::getDDD() {
    return this->pDdd;
}

Pir* HWPlatform::getDPD() {
    return this->pDpd;
}

void HWPlatform::test() {
    // --- static state (persists between calls) ---
    static bool doorOpen = false;

    static unsigned long lastBlink = 0;
    static bool l2State = false;

    static unsigned long lastPrint = 0;
    static bool prevPressed = false;

    unsigned long now = millis();

    /* --------- 1) Blink L2 every 500 ms --------- */
    if (now - lastBlink >= 500) {
        lastBlink = now;
        l2State = !l2State;

        if (pL2) {
            if (l2State) {
                pL2->switchOn();
            } else {
                pL2->switchOff();
            }
        }
    }

    /* --------- 2) Read sensors every 1 s --------- */
    if (now - lastPrint >= 1000) {
        lastPrint = now;

        // Sonar (DDD)
        float d = 0.0f;
        if (pDdd) {
            d = pDdd->getDistance();  // in meters
        }

        // PIR (DPD)
        bool above = false;
        if (pDpd) {
            above = pDpd->isDetected();
        }

        // Temperature (DHT11)
        float t = 0.0f;
        if (pTempSensor) {
            t = pTempSensor->getTemperature();
        }

        Serial.print("Distance: ");
        Serial.print(d);
        Serial.print(" m  |  Drone above (PIR): ");
        Serial.print(above ? "YES" : "NO");
        Serial.print("  |  Temp: ");
        Serial.print(t);
        Serial.println(" C");

        // Show something on LCD (second row)
        if (pLcd) {
            pLcd->setCursor(0, 1);
            pLcd->print("D:");
            pLcd->print(d, 2);
            pLcd->print("m T:");
            pLcd->print(t, 1);
            pLcd->print("C ");
        }
    }

    /* --------- 3) RESET button → toggle door --------- */
    bool pressed = false;
    if (pResetButton) {
        // adapt to your real button method if different
        pressed = pResetButton->isPressed();
    }

    // rising edge: not pressed -> pressed
    if (pressed && !prevPressed) {
        doorOpen = !doorOpen;

        if (doorOpen) {
            Serial.println(">> Opening door");
            if (pDoorMotor) {
                pDoorMotor->setPosition(90);  // open (adjust angle if needed)
            }
            if (pL3) {
                pL3->switchOn();  // e.g. red LED ON when door open
            }
        } else {
            Serial.println(">> Closing door");
            if (pDoorMotor) {
                pDoorMotor->setPosition(0);  // close
            }
            if (pL3) {
                pL3->switchOff();
            }
        }
    }
    prevPressed = pressed;

    // small delay so we don't hammer the CPU too hard
    delay(5);
}