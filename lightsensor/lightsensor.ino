const int ldrPin = A0;     // light sensor, on analogic
const int blueLedPin = 5;  // pwm
const int redLedPin = 6;   // pwm

void setup() {
  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  int lightValue = analogRead(ldrPin);

  // map() converts one range to another proportionally
  // map(value, fromLow, fromHigh, toLow, toHigh)
  // example: light at 21 maps to (21-8)/(35-8) = 48% of the range
  // so red goes from 0 to 255*48% = 122, blue goes from 255 to 255*52% = 133
  // when dark with finger (8): red = 0, blue = 255
  // when moderate light (35+): red = 255, blue = 0
  int redBrightness = map(lightValue, 8, 35, 0, 255);
  int blueBrightness = map(lightValue, 8, 35, 255, 0);

  // keep values in valid range
  redBrightness = constrain(redBrightness, 0, 255);
  blueBrightness = constrain(blueBrightness, 0, 255);

  // set the leds
  analogWrite(redLedPin, redBrightness);
  analogWrite(blueLedPin, blueBrightness);

  delay(50);
}
