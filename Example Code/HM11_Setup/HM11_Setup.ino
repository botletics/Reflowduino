/* This code configures the HM-11 Bluetooth module with a working baud rate
 *  and operating mode. It also changes the Bluetooth name from the default.
 *  
 *  See this page for a full list of AT commands: https://docs.google.com/document/d/14mHWT3GhELCj-6yxsam0k5bjzazq8nnPoz4B_gYh04k/edit#heading=h.lkl7kit1e1ct
 *  
 *  Author: Timothy Woo (botletics.com)
 *  Date: 10/4/2017
 */

#include <SoftwareSerial.h> // Library needed for Bluetooth communication

#define BT_RX 9
#define BT_TX 10

// Initialize Bluetooth software serial
SoftwareSerial BT(BT_TX,BT_RX); // Reflowduino (RX, TX), Bluetooth (TX, RX)

void setup() {
  Serial.begin(9600); // Should be different from Bluetooth baud
//  while (!Serial) {} // Wait for serial monitor to be opened
  
  BT.begin(115200); // HM-11 default baud rate, which isn't reliable
  delay(1); // This delay needs to be here in order to send the AT commands

  sendATcommand("AT+BOUD1", 1000); // Set to 57600 baud
  BT.begin(57600); // Need to use AT+BOUD1 command
  sendATcommand("AT+HOSTEN0", 1000); // Enable master/slave. Default is slave only.
  sendATcommand("AT+NAMEReflowduino", 1000); // Sets the Bluetooth name
}

void loop() {
  // Nothing here
}

void sendATcommand(String ATcommand, unsigned long timeout) {
  // Send AT command
  Serial.print("--> ");
  Serial.println(ATcommand);
  BT.print(ATcommand);

  // Print module's response without timeout
  Serial.print("<-- ");
  
  char c = ' ';
  unsigned long timer = millis(); // Start timer
  
  while (millis() - timer < timeout) {
    if (BT.available()) {
      char c = BT.read();
      Serial.print(c);
    }
  }
  
  if (c == ' ') Serial.println("\n"); // Print a new line if nothing was received
}
