const int pirPin = 2;
const int ledPins[] = {8, 9, 10};

void setup() {
  pinMode(pirPin, INPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int motion = digitalRead(pirPin);

  if (motion == HIGH) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  } else {
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }

  delay(200);
}
