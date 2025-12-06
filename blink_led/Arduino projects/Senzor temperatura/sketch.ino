#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22
#define LEDPIN 8

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LEDPIN, OUTPUT);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();

  if (temp > 30) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }

  delay(1000);
}
