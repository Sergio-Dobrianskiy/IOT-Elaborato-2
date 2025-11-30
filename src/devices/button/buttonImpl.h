#ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Arduino.h"
#include "button.h"

class ButtonImpl : public Button {
public:
    ButtonImpl(uint8_t pin);
    virtual bool isPressed() override;

protected:
    uint8_t pin;
};

#endif