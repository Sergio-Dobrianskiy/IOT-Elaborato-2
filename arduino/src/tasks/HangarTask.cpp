#include "HangarTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

HangarTask::HangarTask(CommunicationCenter* pCommunicationCenter,
                       Hangar* pHangar,
                       UserPanel* pUserPanel)
    : pCommunicationCenter(pCommunicationCenter), pHangar(pHangar), pUserPanel(pUserPanel) {
    pHangar->setDoorState(DoorState::CLOSED);
    pHangar->setDroneState(DroneState::REST);
    droneInRange = true;
    pUserPanel->displayDroneInside();
}

void HangarTask::tick() {
    this->hangarState = pHangar->getHangarState();
    this->droneState = pHangar->getDroneState();
    this->doorState = pHangar->getDoorState();

    //* Manca Communication center
    if (!pCommunicationCenter) {
        Logger.log(F("[DR] ERRORE COMMUNICATION CENTER!!!!!"));

        //* ALLARM
    } else if (this->hangarState == HangarState::ALARM &&
               (this->droneState != DroneState::TAKING_OFF ||
                this->droneState != DroneState::LANDING)) {
        if (pUserPanel) {
            pUserPanel->sync();  // aggiorno stato del pannello (bottone reset)
            if (pUserPanel->isResetPressed()) {
                pHangar->setHangarState(HangarState::NORMAL);
                Logger.log(F("[DR] Hangar is not in alarm state anymore"));
            }
        }

        //* DOOR CLOSED AND DRONE INSIDE
    } else if (this->doorState == DoorState::CLOSED && this->droneState == DroneState::REST) {
        //* TAKE OFF REQUEST
        if (pCommunicationCenter->checkTakeOffRequest()) {
            Logger.log(F("[DR] take-off request from DRU"));
            pHangar->setDroneState(DroneState::WAITING);
            pUserPanel->displayWaitingDoor();
            pHangar->setDoorState(DoorState::OPENING);
            this->stateTimestamp = millis();
        }
        // else {
        //     pUserPanel->displayDroneInside();
        // }

        //* OUTSIDE AND LANDING REQUEST
    } else if (pCommunicationCenter->checkLandingRequest() &&
               this->doorState == DoorState::CLOSED && pHangar->isDroneAbove() &&
               this->droneState == DroneState::OPERATING) {
        // } else if (this->doorState == DoorState::CLOSED &&
        // pCommunicationCenter->checkLandingRequest() && this->droneState == DroneState::OPERATING)
        // { //TODO aggiungere pHangar->isDroneAbove()
        Logger.log(F("[DR] landing request from DRU"));
        pHangar->setDroneState(DroneState::WAITING);
        pUserPanel->displayWaitingDoor();
        pHangar->setDoorState(DoorState::OPENING);
        this->stateTimestamp = millis();

        //* DOOR OPENING
    } else if (this->doorState == DoorState::OPENING && elapsedTimeInState() > DOOR_TIME) {
        pHangar->setDoorState(DoorState::OPEN);
        // this->stateTimestamp = millis();

        //* DOOR OPEN AND DRONE WAITING
    } else if (this->doorState == DoorState::OPEN && this->droneState == DroneState::WAITING) {
        if (pCommunicationCenter->checkAndResetTakeOffRequest()) {  // take off
            pHangar->setDroneState(DroneState::TAKING_OFF);
            pUserPanel->displayTakeOff();
            this->stateTimestamp = millis();
            Logger.log(F("[DO] drone is taking off"));
        } else if (pCommunicationCenter->checkAndResetLandingRequest()) {  // landing
            pHangar->setDroneState(DroneState::LANDING);
            pUserPanel->displayLanding();
            this->stateTimestamp = millis();
            Logger.log(F("[DO] drone is Landing"));
        }

        //* DOOR OPEN AND DRONE TAKING OFF
    } else if (this->doorState == DoorState::OPEN && this->droneState == DroneState::TAKING_OFF) {
        if (pHangar->getDistance() >= D1 && droneInRange) {  // drone uscito dal range
            droneInRange = false;
            this->stateTimestamp = millis();
        } else if (pHangar->getDistance() >= D1 && !droneInRange &&
                   elapsedTimeInState() > T1) {  // drone uscito dal range per più di n secondi
            pHangar->setDroneState(DroneState::OPERATING);
            pUserPanel->displayDroneOut();
            Logger.log(F("[DO] drone is took off"));
            pHangar->setDoorState(DoorState::CLOSING);
        } else if (pHangar->getDistance() < D1 &&
                   !droneInRange) {  // drone torna in range prima di n secondi, resetto il timer
            droneInRange = true;
        }

        //* DOOR OPEN AND DRONE LANDING
    } else if (this->doorState == DoorState::OPEN && this->droneState == DroneState::LANDING) {
        if (pHangar->getDistance() <= D2 && droneInRange) {  // drone entrato nel hangar
            droneInRange = false;
            this->stateTimestamp = millis();
        } else if (pHangar->getDistance() <= D2 && !droneInRange &&
                   elapsedTimeInState() > T2) {  // drone uscito dal range per più di n secondi
            pHangar->setDroneState(DroneState::REST);
            pUserPanel->displayDroneInside();
            Logger.log(F("[DO] drone landed"));
            pHangar->setDoorState(DoorState::CLOSING);
        } else if (pHangar->getDistance() > D2 &&
                   !droneInRange) {  // drone si allontana prima di n secondi, resetto il timer
            droneInRange = true;
        }

        //* DOOR CLOSING AND DRONE OPERATING
    } else if ( this->doorState == DoorState::CLOSING && 
                elapsedTimeInState() > DOOR_TIME &&
                this->droneState == DroneState::OPERATING) {
        pHangar->setDoorState(DoorState::CLOSED);

        //* CLOSING AND DRONE RESTING
    } else if ( this->doorState == DoorState::CLOSING && 
                elapsedTimeInState() > DOOR_TIME &&
                this->droneState == DroneState::REST) {
        pHangar->setDoorState(DoorState::CLOSED);
        pUserPanel->displayDroneInside();
    }
}

long HangarTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}
