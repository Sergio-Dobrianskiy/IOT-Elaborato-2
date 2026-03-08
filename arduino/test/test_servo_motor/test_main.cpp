/* #############################################
   #############################################
   ############### SERVO TEST ##################
   #############################################
   #############################################
*/

#include <Arduino.h>
#include "config.h"
#include "devices/servo_motor/servo_motor_impl.h"

ServoMotorImpl servo(SERVO_PIN);

int c;  // counter
enum { MINUS_90, PLUS_90 } state;

void setup() {
    Serial.begin(9600);
    servo.on();  // attach the servo
    c = 0;
    state = MINUS_90;  // start from -90 (0°)
}

void loop() {
    c++;

    switch (state) {
        case MINUS_90:
            // equivalent to pulse 250µs in old code: extreme position
            servo.setPosition(0);  // 0°  (≈ -90 in your naming)
            if (c > 100) {
                Serial.println("--> +90");
                state = PLUS_90;
                c = 0;
            }
            break;

        case PLUS_90:
            // equivalent to pulse 2250µs: opposite extreme
            servo.setPosition(180);  // 180° (≈ +90)
            if (c > 100) {
                Serial.println("--> -90");
                state = MINUS_90;
                c = 0;
            }
            break;
    }

    delay(15);  // similar timing to the original pulse loop
}
