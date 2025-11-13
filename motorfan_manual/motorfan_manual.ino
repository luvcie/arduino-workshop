#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT11

const int ldrPin = A0;          // light sensor
const int blueLedPin = 5;  
const int redLedPin = 6; 
const int motorPin = 9;         // pwm

const float roomTemp = 26.6;
const float tempThreshold = 0.1;

// light sensor values
const int lightDark = 66; 
const int lightBright = 200;

DHT dht(DHTPIN, DHTTYPE);

// for red led blinking without using delay()
unsigned long lastBlinkTime = 0;
bool redLedState = false;

void setup() {
  Serial.begin(9600);
  Serial.println("automatic + manual ventilation system");

  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(ldrPin, INPUT);

  dht.begin();
}

void loop() {
  // read temperature from sensor
  float temperature = dht.readTemperature();

  // read light sensor
  int lightValue = analogRead(ldrPin);

  // check if temperature reading failed
  if (isnan(temperature)) {
    Serial.println("failed to read from dht sensor");
    return;
  }

  // determine if manual override is active (dark = motor off)
  bool manualOff = (lightValue < 100);  // finger on sensor = dark = manual off

  // calculate temperature excess above threshold
  float tempExcess = temperature - (roomTemp + tempThreshold);
  bool tooHot = (tempExcess >= 0);

  // debug output
  Serial.print("temp: ");
  Serial.print(temperature);
  Serial.print("°C | light: ");
  Serial.print(lightValue);

  // led control based on temperature only
  if (tooHot) {
    // too hot: blue off, red blinking
    digitalWrite(blueLedPin, LOW);

    // calculate blink interval based on temperature excess
    // more heat = faster blinking
    // each 0.1°C excess makes it blink faster
    int blinkInterval = 500 - (tempExcess * 1000);  // starts at 500ms, gets faster
    if (blinkInterval < 100) blinkInterval = 100;   // minimum 100ms

    // blink red led using millis() instead of delay()
    if (millis() - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = millis();
      redLedState = !redLedState;
      digitalWrite(redLedPin, redLedState);
    }

    Serial.print(" | TOO HOT (+" + String(tempExcess, 1) + "°C)");
  } else {
    // normal temp: blue on, red off
    digitalWrite(blueLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    redLedState = false;

    Serial.print(" | normal temp");
  }

  // motor control: automatic unless manual override
  if (manualOff) {
    // manual override: motor forced off
    analogWrite(motorPin, 0);
    Serial.println(" | MANUAL OFF (light sensor covered)");
  } else if (tooHot) {
    // automatic: motor on when too hot
    analogWrite(motorPin, 255);
    Serial.println(" | motor ON (auto)");
  } else {
    // automatic: motor off when normal temp
    analogWrite(motorPin, 0);
    Serial.println(" | motor off");
  }

  delay(50);
}
