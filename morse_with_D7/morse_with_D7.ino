#define DOT_DURATION   250
#define DASH_DURATION  1500
#define ELEMENT_GAP    700
#define CHAR_GAP       1000
#define WORD_GAP       2000

void setup() {
  pinMode(7, OUTPUT);
}

void dot() {
  digitalWrite(7, HIGH);
  delay(DOT_DURATION);
  digitalWrite(7, LOW);
  delay(ELEMENT_GAP);
}

void dash() {
  digitalWrite(7, HIGH);
  delay(DASH_DURATION);
  digitalWrite(7, LOW);
  delay(ELEMENT_GAP);
}

void loop() {
  // 4 (....-)
  dot();
  dot();
  dot();
  dot();
  dash();

  delay(CHAR_GAP);

  // 2 (..---)
  dot();
  dot();
  dash();
  dash();
  dash();

  delay(WORD_GAP);
}
