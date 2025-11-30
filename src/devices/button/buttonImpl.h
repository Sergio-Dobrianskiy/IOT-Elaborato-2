#ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "button.h"

class ButtonImpl : public Button {
public:
    ButtonImpl(int pin);
    bool isPressed();

protected:
    int pin;
};

#endif