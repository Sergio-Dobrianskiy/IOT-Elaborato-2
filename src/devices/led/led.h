#ifndef __LED__
#define __LED__

#include "light.h"

class Led: public Light {
public:
    Led(int pin);
    void switchOn();
    void switchOff();
protected:  // ci possono accedere solo i figli
    int pin;
    bool isOn;
};

#endif