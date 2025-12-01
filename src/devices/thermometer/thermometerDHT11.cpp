#include "Arduino.h"
#include "thermometerDHT11.h"

ThermometerDHT11::ThermometerDHT11(uint8_t pin) : pin(pin) {
    pinMode(pin, INPUT); // Inizializza pin analogico
}


