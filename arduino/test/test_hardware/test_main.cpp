#include <Arduino.h>
#include "model/HWPlatform.h"

HWPlatform hw;

// per test porta
bool doorOpen = false;

// per blink di L2
unsigned long lastBlink = 0;
bool l2State = false;

// per stampare sui serial ogni tanto
unsigned long lastPrint = 0;

void setup() {
    Serial.begin(9600);
    delay(2000);  // tempo per aprire Serial Monitor

    hw.init();  // inizializza TUTTO l'hardware

    Serial.println("=== DRONE HANGAR HW TEST ===");
    Serial.println("Sonar, PIR, DHT11, LCD, LED, Servo, Button");
    Serial.println("Premi il bottone RESET per aprire/chiudere la porta.");
}

void loop() {
    unsigned long now = millis();

    /* --------- 1) Blink L2 ogni 500 ms --------- */
    if (now - lastBlink >= 500) {
        lastBlink = now;
        l2State = !l2State;
        if (l2State) {
            hw.getL2()->switchOn();
        } else {
            hw.getL2()->switchOff();
        }
    }

    /* --------- 2) Letture sensori ogni 1 s --------- */
    if (now - lastPrint >= 1000) {
        lastPrint = now;

        // Sonar (DDD)
        float d = hw.getDDD()->getDistance();  // in metri
        // PIR (DPD)
        bool above = false;
        if (hw.getDPD()) {
            // ADATTA QUESTO AL TUO METODO REALE
            above = hw.getDPD()->isDetected();
        }
        // Temperatura (DHT11)
        float t = hw.getTempSensor()->getTemperature();

        Serial.print("Distance: ");
        Serial.print(d);
        Serial.print(" m  |  Drone above (PIR): ");
        Serial.print(above ? "YES" : "NO");
        Serial.print("  |  Temp: ");
        Serial.print(t);
        Serial.println(" C");

        // Mostriamo qualcosa anche sull'LCD (riga 2)
        auto lcd = hw.getOperatorLcd();
        if (lcd) {
            lcd->setCursor(0, 1);  // seconda riga
            lcd->print("D:");
            lcd->print(d, 2);
            lcd->print("m T:");
            lcd->print(t, 1);
            lcd->print("C ");
        }
    }

    /* --------- 3) Bottone RESET → toggla la porta --------- */
    static bool prevPressed = false;

    bool pressed = false;
    if (hw.getResetButton()) {
        // ADATTA QUESTO AL TUO METODO REALE
        pressed = hw.getResetButton()->isPressed();
    }

    // rileva fronte di discesa / salita (qui: cambio stato da non premuto → premuto)
    if (pressed && !prevPressed) {
        doorOpen = !doorOpen;

        if (doorOpen) {
            Serial.println(">> Opening door");
            hw.getHangarDoorMotor()->setPosition(90);  // apri (adatta angolo)
            hw.getL3()->switchOn();  // rosso ON quando porta aperta (solo per vedere che funziona)
        } else {
            Serial.println(">> Closing door");
            hw.getHangarDoorMotor()->setPosition(0);  // chiudi
            hw.getL3()->switchOff();
        }
    }
    prevPressed = pressed;

    // piccolo delay per non saturare la CPU
    delay(5);
}
