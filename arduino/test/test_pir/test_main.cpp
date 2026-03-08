/* #############################################
   #############################################
   ################ PIR TEST ###################
   #############################################
   #############################################
*/

#include <Arduino.h>
#include "config.h"  // has PIR_PIN defined as 9
#include "devices/pir/Pir.h"

// Create PIR sensor object
Pir pirSensor(PIR_PIN);

void setup() {
    Serial.begin(9600);
    // pinMode is already done inside Pir constructor
}

void loop() {
    bool detected = pirSensor.isDetected();

    Serial.println(detected);  // prints 1 or 0

    if (detected) {
        Serial.println("HIGH");
    } else {
        Serial.println("LOW");
    }
}

/* #############################################
   #############################################
   ############ NON OOP PIR TEST ###############
   #############################################
   #############################################
*/

/*
#include <Arduino.h>
#define PIR 9

void setup(){
  Serial.begin(9600);
  pinMode(PIR, INPUT);
}

void loop(){
  int val = digitalRead(PIR);
  Serial.println(val);
  if(val == HIGH){
    Serial.println("HIGH");
  } else {
    Serial.println("LOW");
  }
}
*/