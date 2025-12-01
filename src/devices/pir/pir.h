#ifndef __PIR__
#define __PIR__

#include "Arduino.h"
#include "presenceSensor.h"

class Pir: public PresenceSensor {
public:  
    Pir(uint8_t pin);
    virtual bool isPresent() override;

protected:  
    uint8_t pin;
};

#endif