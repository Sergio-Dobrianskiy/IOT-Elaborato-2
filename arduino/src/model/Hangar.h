#ifndef __HANGAR__
#define __HANGAR__

#include "scheduler/states.h"
#include "HWPlatform.h"

class Hangar {

public:
    Hangar(HWPlatform* hw);

    void init();
    void sync();

    /* --------- Stato drone --------- */

    void setDroneState(DroneState s);
    DroneState getDroneState() const;

    void setDroneInside(bool inside);
    bool isDroneInside() const;

    /* --------- Porta hangar --------- */

    void openDoor();
    void closeDoor();
    bool isDoorOpen() const;

    /* --------- Letture sensori --------- */

    // distanza dal sonar (DDD), in metri
    float getDistance();

    // presenza sopra l’hangar dal PIR (DPD)
    bool isDroneAbove();

    // temperatura interna (°C)
    float getTemperature();

    /* --------- Stato hangar / allarmi --------- */

    void setHangarState(HangarState s);
    HangarState getHangarState() const;

private:
    HWPlatform* hw;

    DroneState droneState;
    HangarState hangarState;

    bool droneInside;
    bool doorOpen;

    float lastDistance;
    float currentTemp;
    float lastTemperature;
};

#endif