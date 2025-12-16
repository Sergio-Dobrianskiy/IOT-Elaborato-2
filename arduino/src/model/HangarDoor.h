#ifndef __HANGAR_DOOR__
#define __HANGAR_DOOR__

#include "config.h"
#include "devices/servoMotor/servoMotorImpl.h"

// Wrapper logico intorno al ServoMotor che controlla la porta dell'hangar.
class HangarDoor {

public:
  // doorMotor è il servo che apre/chiude la porta.
  // Gli angoli di default possono venire da config.h (se definiti),
  // altrimenti usiamo 0° chiuso, 90° aperto.
    HangarDoor(ServoMotorImpl* doorMotor);

    // Imposta angoli personalizzati (in gradi)
    void setOpenAngle(int angle);
    void setClosedAngle(int angle);

    // Comandi principali
    void open();
    void close();

    // Stato logico
    bool isOpen() const;
    bool isClosed() const;

private:
    ServoMotor* motor;
    int openAngle;
    int closedAngle;
    bool openFlag;
};

#endif