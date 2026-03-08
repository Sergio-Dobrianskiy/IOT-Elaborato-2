#ifndef __COMMUNICATIONCENTER__
#define __COMMUNICATIONCENTER__

#include "HWPlatform.h"
#include "config.h"
#include "model/Hangar.h"

/*
 * Classe che comunica con il con il DRU (Drone Remote Unit) sul PC.
 * - Riceve comandi testuali via seriale (TAKEOFF, LANDING, RESET).
 * - Espone metodi "checkAndReset..." per i Task.
 * - Invia periodicamente lo stato corrente al DRU.
 */
class CommunicationCenter {
public:
    CommunicationCenter(Hangar* pHangar);

    void init();

    void notifyNewState();

    bool checkAndResetOpenDoorRequest();
    bool checkAndResetTakeOffRequest();
    bool checkTakeOffRequest();
    bool checkAndResetLandingRequest();
    bool checkLandingRequest();
    bool checkAndResetAlarmRequest();
    bool notifyAlarm();

    void sync();

private:
    Hangar* pHangar;
    bool openDoorNotification;
    bool takeOffNotification;
    bool landingNotification;
    bool resetAlarmsNotification;
    bool alarmNotification;
    bool droneAbove;
    float droneDistance;
    float currentTemp;
    DroneState droneState;
    HangarState hangarState;
};

#endif
