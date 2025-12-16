#include "Arduino.h"
#include "thermometerDHT11.h"


ThermometerDHT11::ThermometerDHT11(uint8_t pin) : pin(pin), dht(pin, DHTTYPE) {
    dht.begin();
}

// restituisce temperatura in C
float ThermometerDHT11::getTemperatureC() {
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        Serial.println("Errore lettura temperatura DHT11");
        return NAN;
    }
    return temp;
}

// restituisce % umidità
float ThermometerDHT11::getHumidity() {
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
        Serial.println("Errore lettura umidità DHT11");
        return NAN;
    }
    return humidity;
}