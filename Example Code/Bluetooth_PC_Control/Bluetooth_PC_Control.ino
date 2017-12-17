#include <SoftwareSerial.h>

SoftwareSerial BT(10, 9); // Arduino RX, TX

const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  BT.begin(57600);
}

void loop() {
  if (BT.available() < 1) return;

  char request = BT.read();  // Read request
  Serial.print("REQUEST: "); Serial.println(request); // DEBUG

  if (request == 'H') {
    Serial.println("HIGH");
    digitalWrite(LED, HIGH);
  }
  else if (request == 'L') {
    Serial.println("LOW");
    digitalWrite(LED, LOW);
  }
  else {
    Serial.print("REQUEST: "); Serial.println(request); // DEBUG
  }
}
