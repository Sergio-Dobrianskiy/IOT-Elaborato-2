#ifndef __DEVICES__
#define __DEVICES__

#include "config.h"

#include "devices/button/buttonImpl.h"
#include "devices/lcd/lcd.h"
#include "devices/led/led.h"
#include "devices/pir/pir.h"
#include "devices/proxymitySensor/sonar.h"
#include "devices/servoMotor/servoMotorImpl.h"
//#include "devices/thermometer/thermometerDHT11.h"
#include "devices/thermometer/thermometerTMP36.h"

class Devices {
public:
    Devices();
//private: // per ora è tutto pubblico senza getter
    ServoMotorImpl *myservo;
    Lcd *lcd;
    Led *redLed;
    Led *greenLed1;
    Led *greenLed2;
    Pir *pir;
    Sonar *ultrasonic;
    // ThermometerDHT11 *thermometer;
    ThermometerTMP36 *thermometer;
};


#endif