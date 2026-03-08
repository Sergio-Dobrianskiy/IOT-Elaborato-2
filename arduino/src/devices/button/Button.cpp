#include "Button.h"

Button::Button() {}

void Button::updateSyncTime(long time) {
    lastTimeSync = time;
}

long Button::getLastSynchTime() {
    return lastTimeSync;
}