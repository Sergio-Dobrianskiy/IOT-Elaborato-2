#include "Arduino.h"
#include "servoMotorImpl.h"

ServoMotorImpl::ServoMotorImpl(uint8_t pin) : pin(pin), myservo(myservo) {
    myservo.attach(pin);
};

void ServoMotorImpl::setAngle(int angle) {
    myservo.write(angle);
}