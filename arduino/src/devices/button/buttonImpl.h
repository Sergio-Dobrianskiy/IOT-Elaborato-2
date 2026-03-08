#ifndef __BUTTON_IMPL__
#define __BUTTON_IMPL__

#include "Button.h"

class ButtonImpl : public Button {
public:
    ButtonImpl(int pin);
    bool isPressed() override;
    bool isClicked() override;
    void sync() override;

private:
    int pin;
    bool pressed;
    bool clicked;
};

#endif