/*
 * Title: Reflowduino Relay Test
 * Author: Timothy Woo
 * Website: www.botletics.com
 * Last modified: 10/21/2017
 * 
 * -----------------------------------------------------------------------------------------------
 * This is an example sketch to test the Reflowduino solid-state relay. Simply enter "ON" or "OFF"
 * in the serial monitor (case sensitive) and the relay will turn ON or OFF accordingly!
 * 
 * Order a Reflowduino at https://www.botletics.com/products/reflowduino
 * Full documentation and design resources at https://github.com/botletics/Reflowdiuno
 * 
 * -----------------------------------------------------------------------------------------------
 * License: This code is released under the GNU General Public License v3.0
 * https://choosealicense.com/licenses/gpl-3.0/ and appropriate attribution must be
 * included in all redistributions of this code.
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
