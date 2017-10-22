/*
 * Title: Buzzer Test
 * Author: Tom Igoe
 * Modified: 10/21/2017 by Timothy Woo
 * Last modified: 10/21/2017
 * 
 * This example code is in the public domain.
 * http://www.arduino.cc/en/Tutorial/Tone
 * 
 * -----------------------------------------------------------------------------------------------
 * This code tests the piezo buzzer on the Reflowduino by playing a simple melody.
 */
 
#include "pitches.h"

#define buzzer 5

// Notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// I found that NOTE_G6 catches my attention pretty well:
//int melody[] = {
//  NOTE_G6 // About the right frequency for beeping
//};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  // Nothing here
}

void loop() {
  playMelody();
  delay(3000); // Wait 3s before playing again
}

void playMelody() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }
}
