#include "Arduino.h"
#include "buttonImpl.h"

ButtonImpl::ButtonImpl(uint8_t pin): pin(pin) {
    pinMode(pin, INPUT);
};

bool ButtonImpl::isPressed() {
    return digitalRead(pin) == HIGH;
};

