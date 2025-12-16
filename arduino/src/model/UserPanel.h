#ifndef __USER_PANEL__
#define __USER_PANEL__

#include "HWPlatform.h"

// Pannello utente locale dell'hangar.
// Al momento gestisce solo il bottone di RESET ALLARME.
class UserPanel {

public:
    // pHW è la piattaforma hardware da cui prendiamo il Button di reset
    UserPanel(HWPlatform* pHW);

    // inizializzazione logica (reset degli stati interni)
    void init();

    // Legge lo stato fisico del bottone e aggiorna le variabili interne.
    // Va chiamata periodicamente (es. ad ogni tick di un Task).
    void sync();

    // Ritorna true se il bottone è attualmente premuto
    bool isResetPressed() const;

    // Ritorna true SOLO quando il bottone passa da "non premuto" a "premuto"
    // (fronte di salita). Utile per non reagire mille volte mentre è tenuto premuto.
    bool isResetPressedEdge();

private:
    HWPlatform* pHW;
    Button* pResetButton;

    bool resetPressed;       // stato attuale
    bool prevResetPressed;   // stato al tick precedente
};

#endif