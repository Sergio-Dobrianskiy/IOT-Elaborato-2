#ifndef __DRONE_REMOTE_UNIT__
#define __DRONE_REMOTE_UNIT__

#include "Arduino.h"
#include "kernel/MsgService.h"
#include "scheduler/states.h"     // contiene DroneState, HangarState

/*
 * Classe che incapsula la comunicazione con il DRU (Drone Remote Unit) sul PC.
 * - Riceve comandi testuali via seriale (TAKEOFF, LANDING, RESET).
 * - Espone metodi "checkAndReset..." per i Task.
 * - Invia periodicamente lo stato corrente al DRU.
 */
class DroneRemoteUnit {

public:
    DroneRemoteUnit();

    // opzionale: se vuoi inizializzarla, ma di solito MsgService.init() lo fai in main
    void init();

    // Da chiamare periodicamente (es. all'inizio del tick del DroneRemoteTask)
    // Legge eventuali messaggi via MsgService e imposta i flag di richiesta.
    void sync();

    // Chiamato dal DroneRemoteTask per notificare lo stato attuale
    void notifyNewState(DroneState ds, HangarState hs, float distance);

    // Chiamato quando l'hangar va in allarme
    void notifyAlarm();

    // Questi tre metodi sono "edge triggered":
    // tornano true una sola volta per ogni comando ricevuto (e poi resettano il flag).

    bool checkAndResetTakeOffRequest();
    bool checkAndResetLandingRequest();
    bool checkAndResetAlarmResetRequest();

private:
    bool takeOffReq;
    bool landingReq;
    bool alarmResetReq;

    void parseCommand(const String& cmd);

    String droneStateToString(DroneState ds);
    String hangarStateToString(HangarState hs);
};

#endif