#include <Servo.h>
#include <IRremote.h>  // ai grijă să adaugi biblioteca IRremote în Wokwi

// ----- PINI -----
#define SERVO_PIN   9      // servo (fir galben) -> D9
#define BUTTON_PIN  2      // buton verde -> D2 (celălalt pin la GND)
#define IR_PIN      3      // semnal receptor IR -> D3 (schimbă dacă ai alt pin)

// codul comenzii TEST de pe telecomanda Wokwi
const uint8_t IR_TEST_CMD = 34;   // 0x22 (NEC command 34)

// ----- OBIECTE -----
Servo mecanism;

// ----- STARE USA -----
bool doorOpen = false;   // false = închis (0°), true = deschis (90°)

// ----- FUNCTIE COMUNA: deschide/închide usa -----
void toggleDoor() {
  doorOpen = !doorOpen;

  if (doorOpen) {
    mecanism.write(90);   // DESCHIDE
    Serial.println("USA DESCHISA");
  } else {
    mecanism.write(0);    // INCHIDE
    Serial.println("USA INCHISA");
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP); // buton la GND, LOW = apasat

  mecanism.attach(SERVO_PIN);
  mecanism.write(0);                 // la start: usa inchisa

  // pornim receptorul IR
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  Serial.println("READY: buton verde sau tasta TEST = deschide/inchide usa");
}

void loop() {
  // ----- 1. BUTON VERDE FIZIC (toggle pe apasare) -----
  static bool lastButtonState = HIGH;
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // front descendent: HIGH -> LOW = tocmai a fost apasat
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    toggleDoor();
    delay(200); // debounce simplu
  }
  lastButtonState = currentButtonState;

  // ----- 2. TELECOMANDA IR (tasta TEST) -----
  if (IrReceiver.decode()) {
    uint8_t cmd = IrReceiver.decodedIRData.command;
    Serial.print("IR command = ");
    Serial.println(cmd);  // pentru debug, vei vedea 34 cand apesi TEST

    if (cmd == IR_TEST_CMD) {
      toggleDoor();
    }

    IrReceiver.resume();  // pregateste receptorul pentru urmatorul semnal
  }
}