#include "TemperatureTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

bool DEBUG_TEMP = true;

TemperatureTask::TemperatureTask(Hangar* pHangar, UserPanel* pUserPanel) : pHangar(pHangar) {
    setState(HangarState::NORMAL);
}

void TemperatureTask::tick() {
    pHangar->sync();

    float temp = pHangar->getTemperature();

    if (!DEBUG_TEMP) {
        switch (state) {
            case HangarState::NORMAL: {
                pHangar->setHangarState(HangarState::NORMAL);

                if (temp > MAXTEMP) {
                    setState(HangarState::PRE_ALARM);
                }
                break;
            }

            case HangarState::PRE_ALARM: {
                Logger.log(F("[TEMP] pre-alarm"));

                if (temp < MAXTEMP) {
                    // la temperatura è tornata sotto soglia
                    setState(HangarState::NORMAL);
                } else if (elapsedTimeInState() > MAXTEMPTIME) {
                    // troppo tempo sopra soglia -> allarme
                    setState(HangarState::ALARM);
                    pUserPanel->displayAlarm();
                }
                break;
            }

            case HangarState::ALARM: {
                Logger.log(F("[TEMP] alarm"));
                pHangar->setHangarState(HangarState::ALARM);

                // Esci dall'allarme quando qualcuno rimette l'hangar in stato normale
                if (pHangar->getHangarState() == HangarState::NORMAL) {
                    setState(HangarState::NORMAL);
                }
                break;
            }
        }  // end switch
    }
}

void TemperatureTask::setState(HangarState state) {
    this->state = state;
    stateTimestamp = millis();
    justEntered = true;
}

long TemperatureTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}