#include <Arduino.h>

#include "config.h"

#include "devices/button/buttonImpl.h"
#include "devices/lcd/lcd.h"
#include "devices/led/led.h"
#include "devices/pir/pir.h"
#include "devices/proxymitySensor/sonar.h"
#include "devices/servoMotor/servoMotorImpl.h"
//#include "devices/thermometer/thermometerDHT11.h"
#include "devices/thermometer/thermometerTMP36.h"



/************** GLOBALI **************/

ServoMotorImpl *myservo;


Lcd *lcd;

Led *redLed;
Led *greenLed1;
Led *greenLed2;

Pir *pir;

Sonar *ultrasonic;

// ThermometerDHT11 *thermometer;
ThermometerTMP36 *thermometer;


float distance_cm;
/************** SETUP **************/
void setup() {
    Serial.begin(9600);
    Serial.println("0");

    lcd = new Lcd(0x27, LCD_LEN, 2);

    lcd->switchOn();
    pir = new Pir(PIR);

    redLed = new Led(LR);
    greenLed1 = new Led(LG1);
    greenLed1 = new Led(LG2);

    thermometer = new ThermometerTMP36(TEMP);

    ultrasonic = new Sonar(TRIG, ECHO);

    myservo = new ServoMotorImpl(SERVO);
}

/************** LOOP **************/
void loop() {
    int val = pir->isPresent();

    if (val) {
        redLed->switchOn();
        myservo->setAngle(150);
    } else {
        redLed->switchOff();
        myservo->setAngle(0);
    }

    distance_cm = ultrasonic->getDistanceCm();

    if (distance_cm < DISTANCE_THRESHOLD) {
        greenLed1->switchOn();
    } else {
        greenLed1->switchOff();
    }

    ultrasonic->printDistance(distance_cm);

    delay(500);

    float tempC = thermometer->getTemperatureC();
    thermometer->printC(tempC);

    lcd->show("Riga1", "Riga2");
}
