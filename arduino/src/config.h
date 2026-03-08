// Sotto sta il mio
#ifndef __CONFIG__
#define __CONFIG__

#define SCHEDULER_PERIOD     100 // interrupt fa ripartire lo scheduler ogni n millisecondi
#define STATE_UPDATE_PERIOD  500 // periodo di invio stato da CommunicationCenter in ms


#define L1_PIN              9 // green 
#define L2_PIN              2 // green
#define L3_PIN              6 // red
#define L2_BLINK_PERIOD     100
#define LAST_TOGGLE         0
#define HALF_PERIOD         250

#define DHT_TYPE            DHT11  

#define BUTTON_PIN          5

#define TEMP_PIN            A0
#define PIR_PIN             11
#define MAX_TIME_US         30000L      
#define LCD_ADDR            0x27
#define SONAR_TRIG_PIN      8
#define SONAR_ECHO_PIN      7

#define SERVO_PIN           3

#define DOOR_CLOSED_ANGLE   0
#define DOOR_OPEN_ANGLE     90
#define DOOR_TIME           1500      // ms per aprire/chiudere la porta
#define SPILLING_MAX_TIME   20000     // ms di "operazione" (decollo/landing)

#define D1                  0.1       // 0.1 è circa una spanna, 0 durante lo sviluppo
#define D2                  0.1       // 0.1 è circa una spanna, 1 durante lo sviluppo
#define SONAR_NO_OBJ_DETECTED 1       // default -1, 1 durante sviluppo
#define T1                  3000      // tempo conferma decollo drone
#define T2                  3000      // tempo conferma atterraggio drone

#define DOOR_TASK            500       // tempo tick porte
#define COMMUNICATION_PERIOD 500       // tempo tick communication center
#define TEMPERATURE_TASK     1000      // tempo tick termometro

#define MAXTEMP      40                 // temperatura oltre la quale scatta prealarm e poi alarm
#define MAXTEMPTIME  10000              // ms di prealarm dopo i quali scatta allarm

#endif
