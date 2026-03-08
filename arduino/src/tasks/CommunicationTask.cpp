#include "CommunicationTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

CommunicationTask::CommunicationTask(CommunicationCenter* pCommunicationCenter, Hangar* pHangar)
    : pCommunicationCenter(pCommunicationCenter), pHangar(pHangar) {
    setState(DroneState::NORMAL);
}

void CommunicationTask::tick() {
    // 1) aggiorna informazioni dal canale seriale / remoto
    if (pCommunicationCenter) {
        pCommunicationCenter->sync();  // leggere eventuali messaggi in arrivo dal DRU
    }

    // 2) invia periodicamente lo stato corrente al DRU
    lastStateUpdate = 0;
    now = millis();

    if (pCommunicationCenter && (now - lastStateUpdate >= STATE_UPDATE_PERIOD)) {
        lastStateUpdate = now;
        pCommunicationCenter->notifyNewState();
    }
}

void CommunicationTask::setState(DroneState state) {
    this->state = state;
    stateTimestamp = millis();
    justEntered = true;
}

long CommunicationTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}
