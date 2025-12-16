#include "Arduino.h"
#include "led.h"

Led::Led(uint8_t pin) : pin(pin) {
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