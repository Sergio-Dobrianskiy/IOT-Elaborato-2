#ifndef __HANGAR_TASK__
#define __HANGAR_TASK__

#include "kernel/Task.h"
#include "model/CommunicationCenter.h"
#include "model/Hangar.h"
#include "model/States.h"
#include "model/UserPanel.h"

/*
 * Task che gestisce la porta dell'hangar.
 * - legge lo stato delle richieste/notifiche
 * - apre e chiude la porta
 */
class HangarTask : public Task {
public:
    HangarTask(CommunicationCenter* pCommunicationCenter, Hangar* pHangar, UserPanel* pPanel);
    void tick();

private:
    void setDoorState(DoorState state);
    long elapsedTimeInState();

    bool droneInRange;

    HangarState hangarState;
    DoorState doorState;
    DroneState droneState;
    long stateTimestamp;

    CommunicationCenter* pCommunicationCenter;
    Hangar* pHangar;
    UserPanel* pUserPanel;
};

#endif
