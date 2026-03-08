/* #############################################
   #############################################
   ############ TEMPERATUTE TEST ###############
   ################ DHT 11 #####################
   #############################################
*/

#include <Arduino.h>
#include "config.h"
#include "devices/temperature_sensor/TemperatureSensorDHT11.h"

DHT dht(TEMP_PIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Error: no data");
    } else {
        Serial.print("T: ");
        Serial.print(t);
        Serial.print(" °C   H: ");
        Serial.print(h);
        Serial.println(" %");
    }

    delay(2000);
}