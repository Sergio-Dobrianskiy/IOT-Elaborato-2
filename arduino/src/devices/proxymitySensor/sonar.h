#ifndef __SONAR__
#define __SONAR__

#include "Arduino.h"
#include "proximitySensor.h"

class Sonar: public ProximitySensor {
public:  
    Sonar(uint8_t trigPin, uint8_t echoPin);
    virtual float getDistanceCm() override;
    virtual void printDistance(float distance) override;  

protected:  
    uint8_t trigPin;
    uint8_t echoPin;
};

#endif