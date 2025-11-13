#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("room temperature checker");

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("failed to read from dht sensor");
    return;
  }

  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  delay(2000);
}
