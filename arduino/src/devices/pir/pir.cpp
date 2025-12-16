#include "Arduino.h"
#include "pir.h"

Pir::Pir(uint8_t pin) : pin(pin) {
    pinMode(pin, INPUT);
};

// ritorna true se rileva un oggetto
bool Pir::isPresent() {
    return digitalRead(pin) == HIGH;
}