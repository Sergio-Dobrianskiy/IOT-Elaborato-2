#ifndef __THERMOMETER__
#define __THERMOMETER__

class Thermometer {
public:
    virtual float getTemperatureC() = 0;
    virtual void printC(float temp) = 0;
};

#endif