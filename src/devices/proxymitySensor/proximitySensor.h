#ifndef __LIGHT__
#define __LIGHT__

class ProximitySensor {
public:
    virtual float getDistanceCm() = 0;
    virtual void printDistance(float distance) = 0;
};

#endif