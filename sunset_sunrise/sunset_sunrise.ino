const int buttonPin = 8;
const int ledPin = 3;  // pwm pin

int brightness = 0;  // current brightness (0-255)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // button pressed (LOW) -> sunset (decrease brightness)
  // button released (HIGH) -> sunrise (increase brightness)
  if (buttonState == LOW) {
    if (brightness > 0) {
      brightness--;
    }
    delay(20);
  } else {
    if (brightness < 255) {
      brightness++;
    }
    delay(50);
  }

  analogWrite(ledPin, brightness);
}
