//* main alternativo per debuggare componenti singoli
// Commentato perché dava errori di main() loop() ecc multipli

// #include <Arduino.h>
// #include "config.h"
// #include "kernel/Scheduler.h"
// #include "kernel/Logger.h"
// #include "kernel/MsgService.h"
// #include "model/HWPlatform.h"
// #include "model/UserPanel.h"
// #include "model/CommunicationCenter.h"
// #include "tasks/CommunicationTask.h"
// #include "tasks/HangarTask.h"
// #include "tasks/TemperatureTask.h"


// Scheduler scheduler;


// HWPlatform* pHWPlatform;
// UserPanel* pUserPanel;
// Hangar* pHangar;
// CommunicationCenter* pCommunicationCenter;


// void setup() {
// 	MsgService.init();
// 	scheduler.init(SCHEDULER_PERIOD);
// 	Logger.log(":::::: Drone Hangar ::::::");
// 	pHWPlatform = new HWPlatform();
// 	pHWPlatform->init();

// 	pUserPanel = new UserPanel(pHWPlatform);
// 	pUserPanel->init();

// 	pHangar = new Hangar(pHWPlatform);
// 	pHangar->init();

// 	pCommunicationCenter = new CommunicationCenter(pHangar);
// 	pCommunicationCenter->init();

// 	Task* pCommunicationTask = new CommunicationTask(pCommunicationCenter, pHangar);
// 	pCommunicationTask->init(COMMUNICATION_PERIOD);

// 	Task* pHangarTask = new HangarTask(pCommunicationCenter, pHangar, pUserPanel);
// 	pHangarTask->init(DOOR_TASK);

// 	Task* pTemperatureTask = new TemperatureTask(pHangar, pUserPanel);
// 	pTemperatureTask->init(TEMPERATURE_TASK);

// 	scheduler.addTask(pCommunicationTask);
// 	scheduler.addTask(pHangarTask);
// 	scheduler.addTask(pTemperatureTask);
// }




// void loop() {
// 	scheduler.schedule();
	
// 	// pHWPlatform->getResetButton()->sync();
// 	// Logger.log("Reset Alarm Pressed" + String(pHangar->getResetButton()->isPressed()));


// 	// pHWPlatform->getL1()->switchOn();
// 	// pHWPlatform->getL2()->switchOn();
// 	// pHWPlatform->getL3()->switchOn();
// 	// Serial.println("LED ON");

// 	// float distance = pHangar->getDistance();
// 	// MsgService.sendMsg(String(distance).substring(0,5));

// 	// pHangar->openDoor();
// 	// MsgService.sendMsg("OPEN");
// 	// delay(1000);
// 	// pHangar->closeDoor();
// 	// MsgService.sendMsg("CLOSE");
// 	// delay(1000);

// 	// pHWPlatform->getHangarDoorMotor()->setPosition(90);     // Vai a 90°
//     // delay(1000);         // Aspetta 1 secondo per completare il movimento
//     // pHWPlatform->getHangarDoorMotor()->setPosition(0);      // Vai a 0°
//     // delay(1000);         // Aspetta 1 secondo

// }

