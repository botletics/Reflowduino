/* This code controls the Reflowduino solid state relay on and off
 *  to test that it's working. Simply enter "ON" or "OFF" in the serial
 *  monitor (case sensitive) and the relay will turn ON or OFF accordingly!
 *  
 *  Author: Timothy Woo (botletics.com)
 *  Last Modified: 10/20/2017
 *  License: GNU General Public License v3.0
 */

#define relay 7

char charBuff[15];

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW); // Default is OFF

  while (!Serial) delay(1);
  Serial.println("*****Reflowduino Relay Test*****");
  Serial.println("Enter \"ON\" or \"OFF\" into serial monitor");
}

void loop() {
  if (!Serial.available()) return;
  
  int x = 0;
  while (Serial.available()) {
    charBuff[x] = Serial.read();
    x++;
  }
  charBuff[x] = 0; // Null termination
  
  if (strcmp(charBuff, "ON") == 0) {
    Serial.println("Turning relay ON!");
    digitalWrite(relay, HIGH);
  }
  else if (strcmp(charBuff, "OFF") == 0) {
    Serial.println("Turning relay OFF!");
    digitalWrite(relay, LOW);
  }
}
