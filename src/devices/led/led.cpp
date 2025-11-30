#include "Led.h"
#include "Arduino.h"

Led::Led(int pin) : pin(pin) {
    // this->pin = pin;
    this->isOn = false;
    pinMode(pin, OUTPUT);
}

void Led::switchOn() {
    digitalWrite(pin, HIGH);
    isOn = true;
}

void Led::switchOff() {
    digitalWrite(pin, LOW);
    isOn = false;
};