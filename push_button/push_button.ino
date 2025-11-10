const int buttonPin = 2;
const int ledPin = 7;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  digitalWrite(ledPin, HIGH);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // button pin will be LOW when pressed because of the INPUT_PULLUP
  if (buttonState == LOW) {
    digitalWrite(ledPin, LOW); // turn led off
  } else {
    digitalWrite(ledPin, HIGH); // turn on
  }
}
