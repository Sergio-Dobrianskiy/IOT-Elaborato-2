#ifndef __PROXIMITY_SENSOR__
#define __PROXIMITY_SENSOR__

class ProximitySensor {
public:
    virtual float getDistance() = 0;
};

#endif