#include "Arduino.h"
#include "buttonImpl.h"

ButtonImpl::ButtonImpl(int pin) : pin(pin) {
    pinMode(pin, INPUT);
};

bool ButtonImpl::isPressed() {
    return digitalRead(pin) == HIGH;
};

