#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "kernel/Scheduler.h"
#include "model/CommunicationCenter.h"
#include "model/HWPlatform.h"
#include "model/UserPanel.h"
#include "tasks/CommunicationTask.h"
#include "tasks/HangarTask.h"
#include "tasks/TemperatureTask.h"

Scheduler scheduler;
HWPlatform* pHWPlatform;
UserPanel* pUserPanel;
Hangar* pHangar;
CommunicationCenter* pCommunicationCenter;

void setup() {
    MsgService.init();
    scheduler.init(SCHEDULER_PERIOD);
    Logger.log(":::::: Drone Hangar ::::::");
    pHWPlatform = new HWPlatform();
    pHWPlatform->init();

    pUserPanel = new UserPanel(pHWPlatform);
    pUserPanel->init();

    pHangar = new Hangar(pHWPlatform);
    pHangar->init();

    pCommunicationCenter = new CommunicationCenter(pHangar);
    pCommunicationCenter->init();

    Task* pCommunicationTask = new CommunicationTask(pCommunicationCenter, pHangar);
    pCommunicationTask->init(COMMUNICATION_PERIOD);

    Task* pHangarTask = new HangarTask(pCommunicationCenter, pHangar, pUserPanel);
    pHangarTask->init(DOOR_TASK);

    Task* pTemperatureTask = new TemperatureTask(pHangar, pUserPanel);
    pTemperatureTask->init(TEMPERATURE_TASK);

    scheduler.addTask(pCommunicationTask);
    scheduler.addTask(pHangarTask);
    scheduler.addTask(pTemperatureTask);
}

void loop() {
    scheduler.schedule();
}
