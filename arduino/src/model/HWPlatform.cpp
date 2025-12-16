// #include "HWPlatform.h"

// #include "devices/button/ButtonImpl.h"
// #include "devices/led/Led.h"
// #include "devices/pir/Pir.h"
// #include "devices/proxymitySensor/sonar.h"
// #include "devices/thermometer/thermometerDHT11.h"
// #include "devices/servoMotor/servoMotorImpl.h"

// HWPlatform::HWPlatform()
//     :   pDdd(nullptr),
//         pDpd(nullptr),
//         pDoorMotor(nullptr),
//         pTempSensor(nullptr),
//         pLcd(nullptr),
//         pL1(nullptr),
//         pL2(nullptr),
//         pL3(nullptr),
//         pResetButton(nullptr) {
// }

// void HWPlatform::init() {
//     // --- crea i sensori / attuatori usando i pin da config.h ---

//     // Sonar per distanza del drone (DDD)
//     pDdd = new Sonar(ECHO, TRIG, MAX_TIME_US); 
//     // se non hai DDD_MAX_TIME_US, puoi definirlo in config.h (es. 30000L)

//     // PIR per presenza drone (DPD)
//     pDpd = new Pir(PIR_PIN);

//     // Servo porta hangar
//     pDoorMotor = new ServoMotorImpl(SERVO_PIN);
//     pDoorMotor->on();    // attacca subito il servo

//     // Sensore temperatura (DHT11) dietro interfaccia TempSensor
//     pTempSensor = new TempSensorDHT11(TEMP_PIN);

//     // LCD I2C operatore
//     pLcd = new LiquidCrystal_I2C(LCD_ADDR, 16, 2);
//     pLcd->init();
//     pLcd->backlight();
//     pLcd->clear();
//     pLcd->setCursor(0, 0);
//     pLcd->print("DRONE INSIDE");   // stato iniziale richiesto

//     // LED
//     pL1 = new Led(L1_PIN);
//     pL2 = new Led(L2_PIN);
//     pL3 = new Led(L3_PIN);

//     // Assicuriamoci che all'inizio siano nello stato di default
//     pL1->switchOn();     // ad esempio "sistema acceso"
//     pL2->switchOff();
//     pL3->switchOff();

//     // Bottone reset allarme
//     pResetButton = new ButtonImpl(BUTTON_PIN);
// }

// /*

// In HWPlatform::test() scrivo tutte le prove:

// muovi il servo,

// leggi sonar e stampi sul seriale,

// accendi/spegni led,

// scrivi qualcosa sull’LCD,

// ecc.

// Registri questo task nello Scheduler con un certo periodo (es. 100 ms).

// Finché il task è attivo, chiamerà continuamente pHW->test() e tu vedi se tutto funziona.

// */

// #include <Arduino.h>
// #include "HWPlatform.h"

// void HWPlatform::test() {
//   // --- static state (persists between calls) ---
//     static bool doorOpen = false;

//     static unsigned long lastBlink = 0;
//     static bool l2State = false;

//     static unsigned long lastPrint = 0;
//     static bool prevPressed = false;

//     unsigned long now = millis();

//     /* --------- 1) Blink L2 every 500 ms --------- */
//     if (now - lastBlink >= 500) {
//         lastBlink = now;
//         l2State = !l2State;

//         if (pL2) {
//         if (l2State) {
//             pL2->switchOn();
//         } else {
//             pL2->switchOff();
//         }
//         }
//     }

//   /* --------- 2) Read sensors every 1 s --------- */
//     if (now - lastPrint >= 1000) {
//         lastPrint = now;

//         // Sonar (DDD)
//         float d = 0.0f;
//         if (pDdd) {
//         d = pDdd->getDistance();   // in meters (adjust if your API is different)
//         }

//         // PIR (DPD)
//         bool above = false;
//         if (pDpd) {
//         // adapt this to your real method name if needed
//             above = pDpd->isDetected();
//         }

//         // Temperature (DHT11)
//         float t = 0.0f;
//         if (pTempSensor) {
//             t = pTempSensor->getTemperature();
//         }

//         Serial.print("Distance: ");
//         Serial.print(d);
//         Serial.print(" m  |  Drone above (PIR): ");
//         Serial.print(above ? "YES" : "NO");
//         Serial.print("  |  Temp: ");
//         Serial.print(t);
//         Serial.println(" C");

//         // Show something on LCD (second row)
//         if (pLcd) {
//         pLcd->setCursor(0, 1);  // second row
//         pLcd->print("D:");
//         pLcd->print(d, 2);
//         pLcd->print("m T:");
//         pLcd->print(t, 1);
//         pLcd->print("C ");
//         }
//     }

//   /* --------- 3) RESET button → toggle door --------- */
//     bool pressed = false;
//     if (pResetButton) {
//         // adapt to your real button method if different
//         pressed = pResetButton->isPressed();
//     }

//     // rising edge: not pressed -> pressed
//     if (pressed && !prevPressed) {
//         doorOpen = !doorOpen;

//         if (doorOpen) {
//         Serial.println(">> Opening door");
//         if (pDoorMotor) {
//             pDoorMotor->setPosition(90);   // open (adjust angle if needed)
//         }
//         if (pL3) {
//             pL3->switchOn();               // e.g. red LED ON when door open
//         }
//         } else {
//         Serial.println(">> Closing door");
//         if (pDoorMotor) {
//             pDoorMotor->setPosition(0);    // close
//         }
//         if (pL3) {
//             pL3->switchOff();
//         }
//         }
//     }
//     prevPressed = pressed;

//   // small delay so we don't hammer the CPU too hard
//     delay(5);
// }


// // --- getters ---

// Sonar* HWPlatform::getDDD() {
//     return pDdd;
// }

// Pir* HWPlatform::getDPD() {
//     return pDpd;
// }

// ServoMotor* HWPlatform::getHangarDoorMotor() {
//     return pDoorMotor;
// }

// TempSensor* HWPlatform::getTempSensor() {
//     return pTempSensor;
// }

// LiquidCrystal_I2C* HWPlatform::getOperatorLcd() {
//     return pLcd;
// }

// Led* HWPlatform::getL1() {
//     return pL1;
// }

// Led* HWPlatform::getL2() {
//     return pL2;
// }

// Led* HWPlatform::getL3() {
//     return pL3;
// }

// Button* HWPlatform::getResetButton() {
//     return pResetButton;
// }