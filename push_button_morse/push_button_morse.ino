const int buttonPin = 2;
const int ledPin = 7;
const int morseLedPin = LED_BUILTIN;

#define DOT         250
#define DASH        1500
#define ELEM_GAP    700
#define CHAR_GAP    1000

// array containing "42"
const int morse_timing[] = {
    DOT, ELEM_GAP, DOT, ELEM_GAP, DOT, ELEM_GAP, DOT, ELEM_GAP, DASH, CHAR_GAP,
    DOT, ELEM_GAP, DOT, ELEM_GAP, DASH, ELEM_GAP, DASH, ELEM_GAP, DASH, CHAR_GAP
};
// calculates the number of steps in the sequence
const int morse_steps = sizeof(morse_timing) / sizeof(int);

int current_step = 0;
unsigned long last_morse_change = 0;

// this function gets called automatically whenever the button changes
void buttonISR() {
  int buttonState = digitalRead(buttonPin);
  // button released = led off, button pressed = led on
  digitalWrite(ledPin, (buttonState == HIGH) ? LOW : HIGH);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
  pinMode(morseLedPin, OUTPUT);

  // attach interrupt so button works independently from the morse code
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, CHANGE);

  last_morse_change = millis();
}

void loop() {
  // morse code just keeps running no matter what
  if (millis() - last_morse_change >= morse_timing[current_step]) {
    last_morse_change = millis();
    current_step = (current_step + 1) % morse_steps;
    digitalWrite(morseLedPin, (current_step % 2 == 0));
  }
}
