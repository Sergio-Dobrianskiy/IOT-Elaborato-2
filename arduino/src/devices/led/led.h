#ifndef __LED__
#define __LED__

#include "Light.h"

class Led : public Light {
public:
    Led(int pin);
    void switchOn() override;
    void switchOff() override;

    void blink(unsigned long periodMs);
    void stopBlinking();
    void setBlinking(bool enable);

private:
    void toggle();
    int pin;
    bool state;
    bool blinking;
    unsigned long lastToggleMs;
    unsigned long halfPeriodMs;
};

#endif