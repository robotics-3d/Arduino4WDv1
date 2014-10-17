/*
 Test Audio
*/
 

#include "pitches.h"  

const int audioPin = 13;
const int baud = 9600;


void setup()  
{
  Serial.begin(baud); 
  
  pinMode(audioPin, OUTPUT);
  PlayMelody();  

}

void loop()
{
  beep();
  delay(3000);
 }



void PlayMelody()
{
  
  int melody[] = {NOTE_C4,NOTE_G3,NOTE_G3,NOTE_A3,NOTE_G3,0,NOTE_B3,NOTE_C4};
  int noteDurations[] = {4,8,8,4,4,4,4,4};
  for (byte Note = 0; Note < 8; Note++)
  {
    int noteDuration = 1000/noteDurations[Note];
    tone(audioPin,melody[Note],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}
void beep(){
   tone(audioPin,NOTE_C7,100);
     
}

void beeperr(){
  
   tone(audioPin,NOTE_B3, 200);
   delay(29);
   tone(audioPin,NOTE_C4,200);  
   delay(29);
   tone(audioPin,NOTE_B3,200);
}
