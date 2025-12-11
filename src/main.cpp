#include <Arduino.h>
#include "scheduler/states.h"
#include "scheduler/scheduler.h"
#include "devices/devices.h"



/************** GLOBALI **************/

HangarState hangarState;
DroneState droneState;
TestState testState;

ServoMotorImpl *myservo;


Lcd *lcd;

Led *redLed;
Led *greenLed1;
Led *greenLed2;

Pir *pir;

Sonar *ultrasonic;

// ThermometerDHT11 *thermometer;
ThermometerTMP36 *thermometer;

Scheduler *scheduler;


float distance_cm;
/************** SETUP **************/
void setup() {
    hangarState = HangarState::NORMAL;
    droneState = DroneState::REST;
    testState = TestState::FULL_TEST;

    Serial.begin(9600);

    scheduler = new Scheduler(TICK_TIME);
}

/************** LOOP **************/
void loop() {
    // scheduler->schedule(); //TODO Deve rimanere solo questo
    switch (testState) { // TODO rifare e
    case TestState::FULL_TEST:
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
        break;
    
    case TestState::NO_TEST:
        break;
    
    default:
        break;
    }

}
