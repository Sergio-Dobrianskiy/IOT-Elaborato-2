#include "UserPanel.h"
#include <Arduino.h>
#include "config.h"

UserPanel::UserPanel(HWPlatform* pHW)
    :   pHW(pHW),
        pResetButton(nullptr),
        resetPressed(false),
        prevResetPressed(false) {

    // Prendiamo il bottone di reset dalla piattaforma hardware
    
    if (pHW) {
        pResetButton = pHW->getResetButton();
    }
}

void UserPanel::init() {
    resetPressed = false;
    prevResetPressed = false;
}

void UserPanel::sync() {
    if (!pResetButton) {
        return;
    }

    // Se la tua classe Button ha un metodo sync() (come nel cestino), lo chiamiamo
    //pResetButton->sync();

    // Salviamo lo stato precedente e leggiamo quello nuovo
    prevResetPressed = resetPressed;
    resetPressed = pResetButton->isPressed();
}

bool UserPanel::isResetPressed() const {
    return resetPressed;
}

bool UserPanel::isResetPressedEdge() {
  // fronte di salita: ora premuto, prima no
    return (resetPressed && !prevResetPressed);
}