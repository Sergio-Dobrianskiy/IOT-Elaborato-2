#include "Led.h"
#include "Arduino.h"
#include "config.h"

Led::Led(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    state = false;
    blinking = false;
    lastToggleMs = LAST_TOGGLE;
    halfPeriodMs = HALF_PERIOD;
    switchOff();
}

void Led::switchOn() {
    state = true;
    digitalWrite(pin, HIGH);
}

void Led::switchOff() {
    state = false;
    digitalWrite(pin, LOW);
}

void Led::toggle() {
    if (state)
        switchOff();
    else
        switchOn();
}

void Led::blink(unsigned long periodMs) {
    if (periodMs < 2)
        periodMs = 2;  // evita halfPeriod = 0
    halfPeriodMs = periodMs / 2;
    blinking = true;

    unsigned long now = millis();
    if (now - lastToggleMs >= halfPeriodMs) {
        lastToggleMs = now;
        toggle();
    }
}

void Led::stopBlinking() {
    blinking = false;
    switchOff();
}

void Led::setBlinking(bool enable) {
    blinking = enable;
    if (!enable) {
        switchOff();
    } else {
        lastToggleMs = millis();  // reset timing
    }
}