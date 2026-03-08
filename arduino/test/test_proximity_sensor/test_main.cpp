/* #############################################
   #############################################
   ######### PROXIMITY SENSOR TEST #############
   #############################################
   #############################################
*/

#include <Arduino.h>
#include "config.h"
#include "devices/proximity_sensor/Sonar.h"

// same pins as before

// max waiting time for echo (in microseconds)
const long MAX_TIME_US = 30000L;  // ~5 m range

// our sonar object
Sonar sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, MAX_TIME_US);

void setup() {
    Serial.begin(9600);

    // opzionale: se vuoi cambiare la temperatura rispetto ai 20° di default
    // sonar.setTemperature(20);
}

void loop() {
    float d = sonar.getDistance();  // distanza in metri

    if (d == NO_OBJ_DETECTED) {
        Serial.println("No object detected");
    } else {
        Serial.println(d);  // stampa la distanza in metri
    }

    delay(200);
}
