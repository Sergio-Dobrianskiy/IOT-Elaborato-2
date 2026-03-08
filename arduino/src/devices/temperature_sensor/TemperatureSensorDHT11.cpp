#include "TemperatureSensorDHT11.h"
#include "Arduino.h"
#include "config.h"

TempSensorDHT11::TempSensorDHT11(uint8_t pin) : dht(pin, DHT_TYPE) {
    dht.begin();
}

float TempSensorDHT11::getTemperature() {
    float t = dht.readTemperature();  // °C di default

    if (isnan(t)) {
        return NAN;
    }

    return t;
}

float TempSensorDHT11::getHumidity() {
    float h = dht.readHumidity();

    if (isnan(h)) {
        return NAN;
    }

    return h;
}
