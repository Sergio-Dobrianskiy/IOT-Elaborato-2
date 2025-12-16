#include "DroneRemoteUnit.h"

DroneRemoteUnit::DroneRemoteUnit()
    :   takeOffReq(false),
        landingReq(false),
        alarmResetReq(false) {
}

void DroneRemoteUnit::init() {
  // Di solito MsgService.init() lo fai in main(), qui non è strettamente necessario.
  // Ma se vuoi essere robusta, puoi assicurarti che sia stato chiamato almeno una volta.
  // MsgService.init();
}

void DroneRemoteUnit::sync() {
    if (MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();
        if (msg != nullptr) {
        String content = msg->getContent();
        parseCommand(content);
        delete msg;   // evitiamo leak di memoria
        }
    }
}

void DroneRemoteUnit::parseCommand(const String& cmd) {
    // Comandi previsti: "TAKEOFF", "LANDING", "RESET"
    String up = cmd;
    up.toUpperCase();   // normalizziamo a maiuscolo

    if (up == "TAKEOFF") {
        takeOffReq = true;
    } else if (up == "LANDING") {
        landingReq = true;
    } else if (up == "RESET") {
        alarmResetReq = true;
    }
}

bool DroneRemoteUnit::checkAndResetTakeOffRequest() {
    bool bak = takeOffReq;
    takeOffReq = false;
    return bak;
}

bool DroneRemoteUnit::checkAndResetLandingRequest() {
    bool bak = landingReq;
    landingReq = false;
    return bak;
}

bool DroneRemoteUnit::checkAndResetAlarmResetRequest() {
    bool bak = alarmResetReq;
    alarmResetReq = false;
    return bak;
}

void DroneRemoteUnit::notifyNewState(DroneState ds, HangarState hs, float distance) {
    String msg = "STATE,";
    msg += droneStateToString(ds);
    msg += ",";
    msg += hangarStateToString(hs);
    msg += ",";
    msg += String(distance, 2);    // 2 cifre decimali

    MsgService.sendMsg(msg);
}

void DroneRemoteUnit::notifyAlarm() {
    MsgService.sendMsg("ALARM");
}

/* --- helper per convertire enum → string --- */

String DroneRemoteUnit::droneStateToString(DroneState ds) {
    switch (ds) {
        case DroneState::REST:        return "REST";
        case DroneState::TAKING_OFF:  return "TAKING_OFF";
        case DroneState::OPERATING:   return "OPERATING";
        case DroneState::LANDING:     return "LANDING";
        default:                      return "UNKNOWN";
    }
}

String DroneRemoteUnit::hangarStateToString(HangarState hs) {
    switch (hs) {
        case HangarState::NORMAL:     return "NORMAL";
        case HangarState::PRE_ALARM:  return "PRE_ALARM";
        case HangarState::ALARM:      return "ALARM";
        default:                      return "UNKNOWN";
    }
}