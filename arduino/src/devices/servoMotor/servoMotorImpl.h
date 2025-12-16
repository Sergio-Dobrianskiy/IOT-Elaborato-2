#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "Arduino.h"
#include "servoMotor.h"
#include <Servo.h>

class ServoMotorImpl : public ServoMotor {
public:
    ServoMotorImpl(uint8_t pin);
    virtual void setAngle(int angle) override;
    virtual int getAngle() override;

protected:  
    uint8_t pin;
    Servo myservo;
    int angle;
};


#endif