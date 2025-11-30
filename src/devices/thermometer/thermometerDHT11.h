#ifndef __THERMOMETERDHT11__
#define __THERMOMETERDHT11__

#include "thermometer.h"

class ThermometerDHT11 : public Thermometer {
public:
    ThermometerDHT11(int pin);
    float getTemperatureC();
    void printC(float temp);

protected:
    int pin;
};

#endif