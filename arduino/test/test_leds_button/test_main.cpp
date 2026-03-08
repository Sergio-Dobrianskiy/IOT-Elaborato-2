/* #############################################
   #############################################
   ########## OOP LEDS AND BUTTON TEST #########
   #############################################
   #############################################
*/

#include <Arduino.h>

#include "config.h"
#include "devices/button/ButtonImpl.h"
#include "devices/led/Led.h"

// NOTE: config.h defines L3_pin (lowercase "pin")
// so we use that exact name here.

// LED objects
Led led1(L1_PIN);  // green
Led led2(L2_PIN);  // green
Led led3(L3_PIN);  // red

// Button object
ButtonImpl button(BUTTON_PIN);

void setup() {
    Serial.begin(9600);
    // pinMode is already called in Led and ButtonImpl constructors
}

void loop() {
    if (button.isPressed()) {
        led1.switchOn();
        led2.switchOn();
        led3.switchOn();
        Serial.println("ON");
    } else {
        led1.switchOff();
        led2.switchOff();
        led3.switchOff();
        Serial.println("OFF");
    }
}

/* #############################################
   #############################################
   ######## NON OOP LEDS AND BUTTON TEST #######
   #############################################
   #############################################
*/

/*
#include <Arduino.h>

#define BUTTON 10
#define L1 13 // green
#define L2 12 // green
#define L3 11 // red


void setup()
{
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int buttonState = digitalRead(BUTTON);
  if (buttonState == HIGH){
    digitalWrite(L1, HIGH);
    digitalWrite(L2, HIGH);
    digitalWrite(L3, HIGH);
    Serial.println("ON");
  } else {
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    Serial.println("OFF");
  }
}
*/