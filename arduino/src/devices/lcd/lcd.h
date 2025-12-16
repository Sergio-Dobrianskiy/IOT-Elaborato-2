#ifndef __LCD__
#define __LCD__

#include "Arduino.h"
#include "monitor.h"
#include <LiquidCrystal_I2C.h>

class Lcd: public Monitor {
public:
    Lcd(uint8_t address, uint8_t cols, uint8_t rows);
    virtual void switchOn() override;
    virtual void switchOff() override;
    virtual void show(String str1, String str2) override;
    
protected:  // ci possono accedere solo i figli
    uint8_t address; // nella funzione LiquidCrystal_I2C gli argomenti sono uint8_t
    uint8_t cols;
    uint8_t rows;
    LiquidCrystal_I2C lcd;
};

#endif