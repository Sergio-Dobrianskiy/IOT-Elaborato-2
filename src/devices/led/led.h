#ifndef __LED__
#define __LED__

#include "Arduino.h"
#include "light.h"

class Led: public Light {
public:
    Led(uint8_t pin);
    virtual void switchOn() override;
    virtual void switchOff() override;
    
protected:  // ci possono accedere solo i figli
    int pin;
    bool isOn;
};

#endif