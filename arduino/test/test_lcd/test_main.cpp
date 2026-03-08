/* #############################################
   #############################################
   ################# LCD TEST ##################
   #############################################
   #############################################
*/

/*LCD screen TEST*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Creates LCD object for I2C display
void setup() {
    Serial.begin(9600);
    // Initializes screen
    lcd.init();
    lcd.backlight();
}

void loop() {
    // lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hello World!");
}
