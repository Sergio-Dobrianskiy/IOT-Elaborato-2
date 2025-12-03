#ifndef __STATES__
#define __STATES__

enum class HangarState {
    NORMAL = 1,
    PRE_ALARM,
    ALARM
};

enum class DroneState {
    REST = 1,
    TAKING_OFF,
    OPERATING,
    LANDING
};

enum class TestState {
    NO_TEST = 1,
    BUTTON_TEST,
    LCD_TEST,
    LED_TEST,
    PIR_TEST,
    PROXIMITY_TEST,
    SERVO_TEST,
    THERMOMETER_TEST
};


#endif