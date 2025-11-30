#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "devices/led/led.h"
#include "devices/button/buttonImpl.h"
//#include "devices/thermometer/thermometerDHT11.h"
#include "devices/thermometer/thermometerTMP36.h"
#include "devices/proxymitySensor/sonar.h"


/************** DEFINE **************/

#define LCD_LEN 16

#define LG2 10
#define LG1 9
#define LR 6

#define BTN1 5

#define PIR 11
#define SERVO 3

#define TRIG 8
#define ECHO 7

#define DISTANCE_THRESHOLD 100

#define TEMP A0

/************** GLOBALI **************/
LiquidCrystal_I2C lcd(0x27, LCD_LEN, 2);
Servo myservo;

Led *redLed;
Led *greenLed1;
Led *greenLed2;

// ThermometerDHT11 *thermometer;
ThermometerTMP36 *thermometer;

Sonar *ultrasonic;

float distance_cm;
/************** SETUP **************/
void setup()
{
    Serial.begin(9600);
    Serial.println("0");
    // lcd.init();
    // lcd.backlight();

    pinMode(PIR, INPUT);
    // pinMode(LR,OUTPUT);

    redLed = new Led(LR);
    greenLed1 = new Led(LG1);
    greenLed1 = new Led(LG2);

    thermometer = new ThermometerTMP36(TEMP);

    ultrasonic = new Sonar(TRIG, ECHO);

    myservo.attach(SERVO);
}

/************** LOOP **************/
void loop()
{
    int val = digitalRead(PIR);
    Serial.println(val);
    if (val == HIGH)
    {
        redLed->switchOn();
        myservo.write(150);
    }
    else
    {
        redLed->switchOff();
        myservo.write(0);
    }

    distance_cm = ultrasonic->getDistanceCm();

    if (distance_cm < DISTANCE_THRESHOLD)
        greenLed1->switchOn();
    else
        greenLed1->switchOff();

    ultrasonic->printDistance(distance_cm);

    delay(500);

    float tempC = thermometer->getTemperatureC();
    thermometer->printC(tempC);

    // lcd.setCursor(0, 0);
    // lcd.print("Hello World!");
}
