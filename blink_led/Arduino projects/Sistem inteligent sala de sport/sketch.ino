#include "DHT.h"

#define PIR_PIN 2
#define DHTPIN 3
#define DHTTYPE DHT22

#define LED_LIGHT 8
#define LED_ALERT 9
#define BUZZER 10

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(PIR_PIN, INPUT);

  pinMode(LED_LIGHT, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  dht.begin();
}

void loop() {
  int motion = digitalRead(PIR_PIN);
  float temp = dht.readTemperature();

  // Iluminat pe baza mișcării
  if (motion == HIGH) {
    digitalWrite(LED_LIGHT, HIGH);
  } else {
    digitalWrite(LED_LIGHT, LOW);
  }

  // Avertizare temperatură
  if (temp > 30) {
    digitalWrite(LED_ALERT, HIGH);
  } else {
    digitalWrite(LED_ALERT, LOW);
  }

  // Alertă combinată
  if (motion == HIGH && temp > 30) {
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  delay(500);
}
