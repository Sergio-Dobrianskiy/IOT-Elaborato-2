#ifndef __TEMP_SENSOR_DHT11__
#define __TEMP_SENSOR_DHT11__

#include "TempSensor.h"

class TempSensorDHT11 : public TempSensor {
public:
    TempSensorDHT11(int pin);
    virtual float getTemperature();

private:
    int pin;
};

#endif