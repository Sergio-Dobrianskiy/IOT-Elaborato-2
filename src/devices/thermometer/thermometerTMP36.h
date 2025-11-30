#ifndef __THERMOMETERDHT11__
#define __THERMOMETERDHT11__

#include "Arduino.h"
#include "thermometer.h"

class ThermometerTMP36 : public Thermometer {
public:
    ThermometerTMP36(uint8_t pin);
    virtual float getTemperatureC() override;
    virtual void printC(float temp) override;

protected:
    uint8_t pin; // uint8_t evita di dover usare unsigned long long a causa del define A0
    int read();
};

#endif