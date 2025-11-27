#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <Servo.h>


/************** PROTOTIPI **************/
// TODO Andrà nel .h
class Light {
public: // pubblico, tutti possono accedere ai metodi
    virtual void switchOn() = 0; // virtual permette override
    virtual void switchOff() = 0; // vuol dire astratto
};



/************** DEFINE **************/

#define LCD_LEN 16

#define LG2 10
#define LG1 9
#define LR 6

#define BTN1 5

#define PIR 4
#define SERVO 3

#define TRIG 8
#define ECHO 7

#define DISTANCE_THRESHOLD 100

#define TEMP A0


/************** GLOBALI **************/
LiquidCrystal_I2C lcd(0x27, LCD_LEN, 2);
Servo myservo;
float duration_us, distance_cm;

// TODO Andrà nel .h
class Led : public Light {
public:
    Led(int pin);
    void switchOn();
    void switchOff();
protected: // ci possono accedere solo i figli
    int pin;
    bool isOn;
};

Led::Led(int pin) {
    this->pin = pin;
    this->isOn = false;
    pinMode(pin, OUTPUT);
}

void Led::switchOn() {
    // :: scope resolution operator, specifica che 
    // il metodo switchOn appartiene alla classe led
    digitalWrite(pin, HIGH);
    isOn = true;
}

void Led::switchOff() {
    digitalWrite(pin, LOW);
    isOn = false;
}


Led* redLed;
Led* greenLed1;
Led* greenLed2;

/************** SETUP **************/
void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  
  pinMode(PIR,INPUT);
  // pinMode(LR,OUTPUT);

  redLed = new Led(LR);
  greenLed1 = new Led(LG1);
  greenLed1 = new Led(LG2);

  myservo.attach(SERVO);
  pinMode(TRIG, OUTPUT); 
  pinMode(ECHO, INPUT);
  pinMode(TEMP, INPUT);

}

/************** LOOP **************/
void loop() {
  int val = digitalRead(PIR);
  Serial.println(val);
  if(val==HIGH){
    redLed->switchOn();
    myservo.write(150);
  } else{
    redLed->switchOff();
    myservo.write(0);
  }
    
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration_us = pulseIn(ECHO, HIGH);
  distance_cm = 0.017 * duration_us;

  if(distance_cm < DISTANCE_THRESHOLD)
    greenLed1->switchOn();
  else
    greenLed1->switchOff();

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
  
  int tread = analogRead(TEMP);                // valore 0-1023
  float voltage = tread * (5.0 / 1023.0);      // in volt
  float tempC = (voltage - 0.5) * 100.0;       // formula TMP36

  Serial.print("raw: ");
  Serial.print(tread);
  Serial.print(" | V: ");
  Serial.print(voltage, 3);   // 3 decimali
  Serial.print(" V | Temp: ");
  Serial.print(tempC, 2);     // 2 decimali

  // opzione per stampare il simbolo grado (se vuoi provarlo)
  // Serial.print(" "); Serial.write(176); Serial.println("C");

  // oppure più sicuro (compatibilità): niente simbolo grado
  Serial.println(" C");
  
  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
  
  
}

