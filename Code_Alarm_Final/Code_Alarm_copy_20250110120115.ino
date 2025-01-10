#include "discord.h"

#include "pitches.h"
#define BUZZER_PIN 9
#define button 2

int melody[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4,
  NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4,
  NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
  NOTE_A4
};

int durations[] = {
  8, 8, 4, 4,
  8, 8, 4, 4,
  8, 8, 4, 4,
  2
};

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  connectWIFI();
}

void loop() {
  int size = sizeof(durations)/sizeof(int);
  byte state = digitalRead(button);
  Serial.println(state);
  //delay(100);
  
  if(state != 1){
    for (int note = 0; note < size; note++){
      int duration = 1000/durations[note];
      tone(BUZZER_PIN, melody[note], duration);

      int pauseBetweenNotes = duration * 1.30;
      delay(pauseBetweenNotes);

      noTone(BUZZER_PIN);
    }
    discord_send("Hey! You got a package.");
  }
}
