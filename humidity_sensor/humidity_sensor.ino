#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11 

const int blueLedPin = 5;
const int redLedPin = 6;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("humidity sensor test");

  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  // test leds at startup
  digitalWrite(blueLedPin, HIGH);
  delay(500);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, HIGH);
  delay(500);
  digitalWrite(redLedPin, LOW);

  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();

  // check if reading failed
  if (isnan(humidity)) {
    Serial.println("failed to read from dht sensor");
    return;
  }

  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  if (humidity < 80) {
    Serial.println("-> blue led ON, red led OFF");
    digitalWrite(blueLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  } else {
    Serial.println("blue led OFF, red led ON");
    digitalWrite(blueLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
  }

  // wait between readings
  delay(1000);
}
