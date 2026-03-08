#ifndef __SONAR__
#define __SONAR__

#include "ProximitySensor.h"
#include "config.h"

class Sonar : public ProximitySensor {
public:
    Sonar(int echoPin, int trigPin, long maxTime);
    float getDistance() override;
    void setTemperature(float temp);

private:
    const float vs = 331.5 + 0.6 * 20;
    float getSoundSpeed();

    float temperature;
    int echoPin, trigPin;
    long timeOut;
};

#endif