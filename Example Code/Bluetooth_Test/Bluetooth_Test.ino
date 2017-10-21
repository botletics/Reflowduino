/*
 * Title: Reflowduino Bluetooth Demo
 * Author: Timothy Woo
 * Website: www.botletics.com
 * Last modified: 10/21/2017
 * 
 * -----------------------------------------------------------------------------------------------
 * This is an example sketch to test the Reflowduino Bluetooth functionality. Simply upload this
 * sketch to the Reflowduino, open up the Reflowduino app on your Android device, connect to the
 * Reflowduino via Bluetooth, and you should see the arbitrary values appear on your screen!
 * To test sending data to the Reflowduino from the app, press the "START" and "STOP" buttons
 * and in the serial monitor you should see the commands being received. Note that the command
 * is only sent once when you press "START" and once when you press "STOP".
 * 
 * Order a Reflowduino at www.botletics.com
 * Full documentation and design resources at https://github.com/botletics/reflowduino
 * 
 * -----------------------------------------------------------------------------------------------
 * License: This code is released under the Creative Commons Share Alike v3.0 license
 * http://creativecommons.org/licenses/by-sa/3.0/ and appropriate attribution must be
 * included in all redistributions of this code.
 */

#include <SoftwareSerial.h> // Library needed for Bluetooth communication

// Define pins
#define BT_RX 9
#define BT_TX 10

// Initialize Bluetooth software serial
SoftwareSerial BT = SoftwareSerial(BT_TX,BT_RX); // Reflowduino (RX, TX), Bluetooth (TX, RX)

// Bluetooth app settings. Define which characters belong to which functions
#define dataChar '*' // App is receiving data from Reflowduino
#define stopChar '!' // App is receiving command to stop reflow process (process finished!)
#define startReflow 'A' // Command from app to "activate" reflow process
#define stopReflow 'S' // Command from app to "stop" reflow process at any time

double temperature;
unsigned long previousMillis = 0;
unsigned long sendRate = 2000; // Send data to app every 2s

void setup() {
  Serial.begin(9600); // This should be different from the Bluetooth baud rate
  BT.begin(57600); // Please see the "Bluetooth_Setup" sketch before using this code

  while (!Serial) delay(1); // OPTIONAL: Wait for serial to connect
  Serial.println("*****Reflowduino Bluetooth Demo*****");
}

void loop() {
  BT.flush();
  char request = ' ';

  // Send data to the app periodically
  if (millis() - previousMillis > sendRate) {
    previousMillis = millis();
    temperature = analogRead(A0) / 5.67; // Read arbitrary values
    Serial.print("--> Temperature: "); // The right arrow means it's sending data out
    Serial.print(temperature);
    Serial.println(" *C");
    BT.print(dataChar); // This tells the app that it's data
    BT.print(String(temperature)); // Need to cast to String for the app to receive it properly
  }
  
  // Check for an incoming command. If nothing was sent, return to loop()
  if (BT.available() < 1) return;

  request = BT.read();  // Read request
  Serial.print("REQUEST: "); Serial.println(request); // DEBUG

  if (request == startReflow) { // Command from app to start reflow process
    Serial.println("<-- ***Starting reflow process!"); // Left arrow means it received a command
    // Do other stuff here
  }
  else if (request == stopReflow) { // Command to stop reflow process
    Serial.println("<-- ***Reflow process aborted!");
    // Do other stuff here
  }
  // Add you own functions here and have fun with it!
}
