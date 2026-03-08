#include <Arduino.h>
#include "model/HWPlatform.h"
#include "model/Hangar.h"
#include "model/States.h"

HWPlatform hw;
Hangar hangar(&hw);

bool doorOpen = false;
unsigned long lastPrint = 0;

void setup() {
    Serial.begin(9600);
    delay(2000);  // tempo per aprire il Serial Monitor

    hw.init();      // inizializza TUTTO l'hardware
    hangar.init();  // stato iniziale: porta chiusa, drone dentro, NORMAL

    Serial.println("=== HANGAR LOGIC TEST ===");
    Serial.println("Usa il bottone RESET per aprire/chiudere la porta.");
}

void loop() {
    unsigned long now = millis();

    /* --------- 1) Letture periodiche e stampa --------- */
    if (now - lastPrint >= 1000) {  // ogni 1 secondo
        lastPrint = now;

        float d = hangar.getDistance();     // distanza dal sonar (m)
        bool pir = hangar.isDroneAbove();   // presenza sopra l'hangar
        float t = hangar.getTemperature();  // temperatura (°C)

        DroneState ds = hangar.getDroneState();
        HangarState hs = hangar.getHangarState();

        Serial.print("Dist: ");
        Serial.print(d);
        Serial.print(" m | PIR: ");
        Serial.print(pir ? "YES" : "NO");
        Serial.print(" | Temp: ");
        Serial.print(t);
        Serial.print(" C | Door: ");
        Serial.print(hangar.isDoorOpen() ? "OPEN" : "CLOSED");
        Serial.print(" | DroneState: ");
        switch (ds) {
            case DroneState::REST:
                Serial.print("REST");
                break;
            case DroneState::TAKING_OFF:
                Serial.print("TAKING_OFF");
                break;
            case DroneState::OPERATING:
                Serial.print("OPERATING");
                break;
            case DroneState::LANDING:
                Serial.print("LANDING");
                break;
        }
        Serial.print(" | HangarState: ");
        switch (hs) {
            case HangarState::NORMAL:
                Serial.println("NORMAL");
                break;
            case HangarState::PRE_ALARM:
                Serial.println("PRE_ALARM");
                break;
            case HangarState::ALARM:
                Serial.println("ALARM");
                break;
        }
    }

    /* --------- 2) Bottone RESET → toggle porta hangar --------- */
    static bool prevPressed = false;
    bool pressed = false;
    if (hw.getResetButton()) {
        // ADATTA se il tuo Button ha un nome diverso per il metodo
        pressed = hw.getResetButton()->isPressed();
    }

    if (pressed && !prevPressed) {
        // fronte di salita → cambio stato porta
        doorOpen = !doorOpen;
        if (doorOpen) {
            Serial.println(">> Hangar: openDoor()");
            hangar.openDoor();
        } else {
            Serial.println(">> Hangar: closeDoor()");
            hangar.closeDoor();
        }
    }
    prevPressed = pressed;

    /* --------- 3) Esempio: aggiorno DroneState a mano --------- */
    // Giusto per vedere che funziona: se il drone è molto lontano,
    // considero "DRONE OUT" e metto state OPERATING
    float d = hangar.getDistance();
    if (d > 1.0) {  // > 1 m = consideriamo fuori
        hangar.setDroneInside(false);
        hangar.setDroneState(DroneState::OPERATING);
    } else {
        hangar.setDroneInside(true);
        hangar.setDroneState(DroneState::REST);
    }

    delay(5);
}
