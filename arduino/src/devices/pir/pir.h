#ifndef __PIR__
#define __PIR__

#include "PresenceSensor.h"

class Pir : public PresenceSensor {
public:
    Pir(int pin);
    bool isDetected() override;
    void sync() override;
    long getLastSyncTime() override;
    void calibrate();

private:
    void updateSyncTime(long time) override;
    long lastTimeSync;
    int pin;
    bool detected;
};

#endif