// ================== PINI ==================
#define TRIG_PIN 2
#define ECHO_PIN 3

#define RED_LED    8
#define YELLOW_LED 9
#define GREEN_LED  10

#define BUTTON_PIN 4
#define BUZZER     11

// ================== FUNCȚIE DISTANȚĂ ==================
long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  // conversie microsecunde → cm
  long distance = duration * 0.034 / 2;

  return distance;
}

// ================== OPREȘTE LED-URI ==================
void allLedsOff() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

// ================== SETUP ==================
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
}

// ================== LOOP ==================
void loop() {

  int buttonState = digitalRead(BUTTON_PIN);

  // ===== MOD URGENȚĂ =====
  if (buttonState == LOW) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    delay(300);

    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, LOW);

    delay(300);
    return;
  }

  // ===== CITIM DISTANȚA =====
  long distance = readDistanceCM();

  bool carDetected = (distance > 0 && distance < 20);

  // ===== ROȘU =====
  allLedsOff();
  digitalWrite(RED_LED, HIGH);
  delay(2000);

  // ===== VERDE =====
  allLedsOff();
  digitalWrite(GREEN_LED, HIGH);

  if (carDetected) {
    delay(5000);   // trafic mare
  } else {
    delay(2000);   // trafic normal
  }

  // ===== GALBEN =====
  allLedsOff();
  digitalWrite(YELLOW_LED, HIGH);
  delay(1000);
}
