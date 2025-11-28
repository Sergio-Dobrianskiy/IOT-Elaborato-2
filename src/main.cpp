#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <Servo.h>


/************** PROTOTIPI **************/
// TODO Andrà nel .h
class Led {
public: // pubblico, tutti possono accedere ai metodi
    virtual void switchOn() = 0; // virtual permette override
    virtual void switchOff() = 0; // vuol dire astratto
};

class Button {
public:
    virtual bool isPressed() = 0;
};


class Thermometer {
public:
    virtual float getTempC() = 0;
    virtual void printC(float temp) = 0;
};

class Ultrasonic {
public:
    virtual float getDistanceCm() = 0;
    virtual void printDistance(float distance) = 0;
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

// TODO Andrà nel .h
class LedImpl : public Led {
public:
    LedImpl(int pin) : pin(pin) {
      this->isOn = false;
      pinMode(pin, OUTPUT);
}
    void switchOn() {
        digitalWrite(pin, HIGH);
        isOn = true;
}
    void switchOff() {
        digitalWrite(pin, LOW);
        isOn = false;
}
protected: // ci possono accedere solo i figli
    int pin;
    bool isOn;
};
class ButtonImpl: public Button {
public:
    ButtonImpl(int pin) : pin(pin) {
    pinMode(pin, INPUT);
}
    bool isPressed(){
        return digitalRead(pin) == HIGH;
}
protected:
    int pin;
};

class ThermometerImpl: Thermometer {
public:
    ThermometerImpl(uint8_t pin) : pin(pin) {
        pinMode(pin, INPUT); // Inizializza pin analogico
    }
    // Restituisce temperatura in C
    virtual float getTempC() override {
    // Override: Dice al compilatore: "Questo metodo deve sovrascrivere esattamente uno virtuale dalla base"
        float voltage = read() * 5.0 / 1024.0;
        return (voltage - 0.5) * 100.0;  // Formula per TMP36
    }

    // Printa temperatura in C su seriale.
    virtual void printC(float temp) override {
        Serial.print("Temp: ");
        Serial.print(temp);
        Serial.write(176); 
        Serial.println("C");
    }
protected:
    uint8_t pin; // salvato da : pin(pin), equivale a this->pin = pin;
    // uint8_t evita di dover usare unsigned long long a causa del define A0
    
    // legge valore dal sensore
    int read(){
        return analogRead(pin);                // valore 0-1023
    }
};

class UltrasonicImpl: Ultrasonic {
public:
    UltrasonicImpl(uint8_t trigPin, uint8_t echoPin) : trigPin(trigPin), echoPin(echoPin) {
        pinMode(trigPin, OUTPUT); // Inizializza pin analogico
        pinMode(echoPin, INPUT); // Inizializza pin analogico
    }

    virtual float getDistanceCm() override {
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      float duration_us = pulseIn(echoPin, HIGH);
      return 0.017 * duration_us;

    };
    virtual void printDistance(float distance) override {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    };

protected:
    uint8_t trigPin;
    uint8_t echoPin;
};


LedImpl* redLed;
LedImpl* greenLed1;
LedImpl* greenLed2;

ThermometerImpl* thermometer;

UltrasonicImpl* ultrasonic;

float distance_cm;
/************** SETUP **************/
void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  
  pinMode(PIR,INPUT);
  // pinMode(LR,OUTPUT);

  redLed = new LedImpl(LR);
  greenLed1 = new LedImpl(LG1);
  greenLed1 = new LedImpl(LG2);

  thermometer = new ThermometerImpl(TEMP);

  ultrasonic = new UltrasonicImpl(TRIG, ECHO);

  myservo.attach(SERVO);
  


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
  

  

  distance_cm = ultrasonic->getDistanceCm();

  if(distance_cm < DISTANCE_THRESHOLD)
    greenLed1->switchOn();
  else
    greenLed1->switchOff();

  ultrasonic->printDistance(distance_cm);

  delay(500);
  
  float tempC = thermometer->getTempC();
  thermometer->printC(tempC);

  
  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
  
  
}

