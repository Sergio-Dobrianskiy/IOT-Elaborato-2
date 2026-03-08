#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "kernel/Task.h"
#include "model/CommunicationCenter.h"
#include "model/HWPlatform.h"
#include "model/Hangar.h"
#include "model/States.h"
#include "model/UserPanel.h"

class TemperatureTask : public Task {
public:
    TemperatureTask(Hangar* pHangar, UserPanel* pUserPanel);
    void tick();

private:
    void setState(HangarState s);
    long elapsedTimeInState();
    void log(const String& msg);

    long stateTimestamp;
    bool justEntered;
    HangarState state;

    UserPanel* pUserPanel;
    Hangar* pHangar;
};

#endif