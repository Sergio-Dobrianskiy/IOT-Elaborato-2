#ifndef __PROXIMITY_SENSOR__
#define __PROXIMITY_SENSOR__

class ProximitySensor {
public:
    virtual float getDistanceCm() = 0;
    virtual void printDistance(float distance) = 0;
};

#endif