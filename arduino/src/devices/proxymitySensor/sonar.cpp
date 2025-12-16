#include "Arduino.h"
#include "sonar.h"

Sonar::Sonar(uint8_t trigPin, uint8_t echoPin) : trigPin(trigPin), echoPin(echoPin) {
    pinMode(trigPin, OUTPUT); // Inizializza pin analogico
    pinMode(echoPin, INPUT);  // Inizializza pin analogico
};

float Sonar::getDistanceCm() {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    float duration_us = pulseIn(echoPin, HIGH);
    return 0.017 * duration_us;
};

void printDistance(float distance) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
};