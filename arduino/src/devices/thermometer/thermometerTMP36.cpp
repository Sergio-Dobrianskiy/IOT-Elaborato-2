#include "Arduino.h"
#include "thermometerTMP36.h"


ThermometerTMP36::ThermometerTMP36(uint8_t pin) : pin(pin) {
    pinMode(pin, INPUT); // Inizializza pin analogico
}

// Restituisce temperatura in C
float ThermometerTMP36::getTemperatureC() {
    // Override: Dice al compilatore: "Questo metodo deve sovrascrivere esattamente uno virtuale dalla base"
    float voltage = read() * 5.0 / 1024.0;
    return (voltage - 0.5) * 100.0; // Formula per TMP36
}

// Printa temperatura in C su seriale.
void ThermometerTMP36::printC(float temp) {
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.write(176);
    Serial.println("C");
}

// legge valore dal sensore
int ThermometerTMP36::read() {
    return analogRead(pin); // valore 0-1023
}
