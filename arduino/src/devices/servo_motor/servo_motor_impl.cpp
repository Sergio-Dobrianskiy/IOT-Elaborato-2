#include "servo_motor_impl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin) {
    this->pin = pin;
    _on = false;
}

void ServoMotorImpl::motorOn() {
    motor.attach(pin);
    _on = true;
    Serial.println("PIN " + String(pin));
}

bool ServoMotorImpl::isOn() {
    return _on;
}

void ServoMotorImpl::setPosition(int angle) {
    if (angle > 180) {
        angle = 180;
    } else if (angle < 0) {
        angle = 0;
    }
    float coeff = (2500.0 - 500.0) / 180.0;
    int pulse = static_cast<int>(500.0 + angle * coeff + 0.5);  // Calcola e arrotonda
    Serial.println("ANGLE " + String(angle) + " (pulse: " + String(pulse) + ")");
    motor.write(pulse);
}

void ServoMotorImpl::off() {
    _on = false;
    // motor.detach();// servo2 non ha detach
}