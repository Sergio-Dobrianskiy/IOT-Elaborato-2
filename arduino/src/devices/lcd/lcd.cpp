#include "Arduino.h"
#include "lcd.h"

Lcd::Lcd(uint8_t address, uint8_t cols, uint8_t rows) : address(address), cols(cols), rows(rows), lcd(address, cols, rows) {
    lcd.init();
}

// accende l'lcd
void Lcd::switchOn() {
    lcd.backlight();
}

// spegne l'lcd
void Lcd::switchOff() {
    lcd.noBacklight();
};

// TODO migliorare
void Lcd::show(String str1, String str2) {
    lcd.setCursor(0, 0);
    lcd.print(str1);
    lcd.setCursor(0, 1);
    lcd.print(str1);
};