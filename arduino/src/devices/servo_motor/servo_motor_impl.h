#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include <arduino.h>
#include "ServoTimer2.h"
#include "servo_motor.h"
// #include <Servo.h> //! non si può usare perché usa Timer1 che serve per l'interrupt dello
// scheduler

class ServoMotorImpl : public ServoMotor {
public:
    ServoMotorImpl(int pin);
    void motorOn() override;
    bool isOn() override;
    void setPosition(int angle) override;
    void off() override;

private:
    int pin;
    bool _on;
    ServoTimer2 motor;
};

#endif