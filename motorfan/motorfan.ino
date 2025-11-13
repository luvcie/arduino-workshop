#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

const int blueLedPin = 5;
const int redLedPin = 6;
const int motorPin = 9;  // pwm

const float roomTemp = 26.6;      // baseline room temperature in celsius
const float tempThreshold = 0.1;  // temperature increase to trigger motor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("automatic ventilation system");

  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  // test leds at startup
  digitalWrite(redLedPin, HIGH);
  digitalWrite(blueLedPin, HIGH);
  delay(1000);
  digitalWrite(redLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
  delay(1000);

  dht.begin();
}

void loop() {
  // read temperature from sensor
  float temperature = dht.readTemperature();

  // check if reading failed
  if (isnan(temperature)) {
    Serial.println("failed to read from dht sensor");
    return;
  }

  // display temperature
  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.print("°C");

  // check if temperature exceeds threshold
  if (temperature >= roomTemp + tempThreshold) {
    // too hot: blue led off, red led on, motor on
    Serial.println(" -> TOO HOT! motor on");
    digitalWrite(blueLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    analogWrite(motorPin, 255);  // motor at full speed
  } else {
    // normal temperature: blue led on, red led off, motor off
    Serial.println(" -> normal temp, motor off");
    digitalWrite(blueLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    analogWrite(motorPin, 0);  // motor off
  }

  // wait half a second between readings
  delay(500);
}
