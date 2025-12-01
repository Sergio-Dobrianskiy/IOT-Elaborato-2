#ifndef __THERMOMETERDHT11__
#define __THERMOMETERDHT11__

#include "Arduino.h"
#include "thermometer.h"
#include <DHT.h>

#define DHTTYPE DHT11  // Tipo di sensore (DHT11, DHT22, DHT21)

class ThermometerDHT11 : public Thermometer {
public:
    ThermometerDHT11(uint8_t pin);
    virtual float getTemperatureC() override;
    virtual void printC(float temp) override;
    virtual float getHumidity();

protected:
    uint8_t pin; // uint8_t evita di dover usare unsigned long long a causa del define A0
    DHT dht;
};

#endif