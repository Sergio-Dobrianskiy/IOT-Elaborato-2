/* Maybe remove? */

#ifndef __STATES__
#define __STATES__

enum class DroneState { REST, WAITING, TAKING_OFF, OPERATING, LANDING, NORMAL };
enum class HangarState { NORMAL, PRE_ALARM, ALARM };
enum class DoorState { OPEN, OPENING, CLOSED, CLOSING };
#endif
