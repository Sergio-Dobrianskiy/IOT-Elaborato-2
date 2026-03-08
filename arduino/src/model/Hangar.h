#ifndef __HANGAR__
#define __HANGAR__

#include "HWPlatform.h"
#include "States.h"
#include "config.h"

class Hangar {
public:
    Hangar(HWPlatform* hw);

    void init();
    void sync();

    void setDoorState(DoorState state);

    DoorState getDoorState();

    /* --------- Stato drone --------- */
    void setDroneState(DroneState state);
    DroneState getDroneState();

    /* --------- Porta hangar --------- */
    void openDoor();
    void closeDoor();
    bool isDoorOpen();

    /* --------- Letture sensori --------- */
    // distanza dal sonar (DDD), in metri
    float getDistance();

    // presenza sopra l’hangar dal PIR (DPD)
    bool isDroneAbove();

    // temperatura interna (°C)
    float getTemperature();

    /* --------- Stato hangar / allarmi --------- */
    void setHangarState(HangarState state);
    HangarState getHangarState();
    void raiseAlarm();
    void resetAlarm();

    void setL1On();
    void setL2Blinking();
    void setL3On();

    void setL1Off();
    void setL2Off();
    void setL3Off();
    ButtonImpl* getResetButton();

private:
    HWPlatform* pHW;
    DroneState droneState;
    DoorState doorState;
    HangarState hangarState;
    ButtonImpl* pResetButton;

    bool L1isOn;
    bool L2isBlinking;
    bool L3isOn;
    bool doorOpen;
    float lastDistance;
    float currentTemp;
    float lastTemperature;
    bool alarmRaised;
    void manageLeds();
    void manageAlarm();
    void manageDoor();
};

#endif
