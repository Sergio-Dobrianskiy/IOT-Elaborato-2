#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

class ServoMotor {
public:
    virtual void setAngle(int angle) = 0;
    virtual int getAngle() = 0;
};

#endif