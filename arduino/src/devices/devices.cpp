#include "devices.h"

Devices::Devices() {
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
