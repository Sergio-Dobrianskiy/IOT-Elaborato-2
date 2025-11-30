#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "devices/led/led.h"
#include "devices/button/buttonImpl.h"
//#include "devices/thermometer/thermometerDHT11.h"
#include "devices/thermometer/thermometerTMP36.h"

/************** PROTOTIPI **************/


class Ultrasonic
{
public:
    virtual float getDistanceCm() = 0;
    virtual void printDistance(float distance) = 0;
};

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

class UltrasonicImpl : Ultrasonic
{
public:
    UltrasonicImpl(uint8_t trigPin, uint8_t echoPin) : trigPin(trigPin), echoPin(echoPin)
    {
        pinMode(trigPin, OUTPUT); // Inizializza pin analogico
        pinMode(echoPin, INPUT);  // Inizializza pin analogico
    }

    virtual float getDistanceCm() override
    {
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        float duration_us = pulseIn(echoPin, HIGH);
        return 0.017 * duration_us;
    };
    virtual void printDistance(float distance) override
    {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    };

protected:
    uint8_t trigPin;
    uint8_t echoPin;
};

Led *redLed;
Led *greenLed1;
Led *greenLed2;

// ThermometerDHT11 *thermometer;
ThermometerTMP36 *thermometer;

UltrasonicImpl *ultrasonic;

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

    ultrasonic = new UltrasonicImpl(TRIG, ECHO);

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
