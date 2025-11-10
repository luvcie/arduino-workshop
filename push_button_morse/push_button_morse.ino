const int buttonPin = 2;
const int ledPin = 7;
const int morseLedPin = LED_BUILTIN;

#define DOT         250
#define DASH        1500
#define ELEM_GAP    700
#define CHAR_GAP    1000

// array containing "42" morse code timing
const int morse_timing[] = {
    DOT, ELEM_GAP, DOT, ELEM_GAP, DOT, ELEM_GAP, DOT, ELEM_GAP, DASH, CHAR_GAP,
    DOT, ELEM_GAP, DOT, ELEM_GAP, DASH, ELEM_GAP, DASH, ELEM_GAP, DASH, CHAR_GAP
};
// calculates the number of steps in the sequence
const int morse_steps = sizeof(morse_timing) / sizeof(int);

int current_step = 0;
unsigned long last_morse_change = 0;

// this function gets called automatically whenever the button changes
// ISR = Interrupt Service Routine
void buttonISR() {
  int buttonState = digitalRead(buttonPin);
  // with INPUT_PULLUP: released = HIGH, pressed = LOW
  // so we just copy the button state directly to the led
  digitalWrite(ledPin, buttonState);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, HIGH);
  pinMode(morseLedPin, OUTPUT);

  // attach interrupt so button works independently from the morse code
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, CHANGE);

  last_morse_change = millis();
}

// morse always runs continuously, independent of button
void loop() {
  if (millis() - last_morse_change >= morse_timing[current_step]) {
    last_morse_change = millis();
    current_step = (current_step + 1) % morse_steps;
    // even steps (0,2,4...) are signals -> turn led on
    // odd steps (1,3,5...) are gaps -> turn led off
    bool isSignal = (current_step % 2 == 0);
    digitalWrite(morseLedPin, isSignal);
  }
}
