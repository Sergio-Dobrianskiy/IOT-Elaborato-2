#ifndef __DRONE_REMOTE_TASK__
#define __DRONE_REMOTE_TASK__

#include "kernel/Task.h"
#include "model/CommunicationCenter.h"
#include "model/Hangar.h"
#include "model/States.h"

/*
 * Task che gestisce la comunicazione con il DRU (Drone Remote Unit).
 * - legge i comandi dal PC (take-off, landing, reset...)
 * - aggiorna lo stato del drone nell'hangar
 * - notifica al DRU lo stato corrente (drone, hangar, distanza)
 */
class CommunicationTask : public Task {
public:
    CommunicationTask(CommunicationCenter* pCommunicationCenter, Hangar* pHangar);
    void tick();

private:
    unsigned long lastStateUpdate;
    unsigned long now;
    void setState(DroneState state);
    long elapsedTimeInState();

    DroneState state;
    long stateTimestamp;
    bool justEntered;

    CommunicationCenter* pCommunicationCenter;
    Hangar* pHangar;
};

#endif
