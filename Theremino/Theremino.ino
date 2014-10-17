/*
 DIstanza

*/
#include "pitches.h"  

const int signalPin = 12; 
const int echoPin = 11;
const int audioPin = 13;

unsigned long pulseTime = 0;                    // stores the pulse in Micro Seconds
unsigned long distance = 0;                     // variable for storing the distance (cm) we'll use distance as a switch for the speaker
unsigned long soundDelay = 0;   
const long baud = 9600;



void setup()  
{
  Serial.begin(baud); 
 
  pinMode(audioPin, OUTPUT);                  // sets pin 6 as output
  pinMode(signalPin, OUTPUT);                     // set init pin 3 as output
  pinMode(echoPin, INPUT);                      // set echo pin 2 as input

  PlayMelody();  

}

void loop()
{
  digitalWrite(signalPin, HIGH);                  // send 10 microsecond pulse
  delayMicroseconds(10);                        // wait 10 microseconds before turning off
  digitalWrite(signalPin, LOW);                   // stop sending the pulse
  pulseTime = pulseIn(echoPin, HIGH);           // Look for a return pulse, it should be high as the pulse goes low-high-low
  distance = pulseTime/58;                      // convert the pulse into distance (cm)
  soundDelay = pulseTime/3;                     // alter this variable to alter the pitch of the sound emitted

  // make the sound.
  // check the distance, if over 30cm make no sound
  //if (distance < 30) {
  digitalWrite(audioPin, HIGH);
  delayMicroseconds(soundDelay);
  digitalWrite(audioPin, LOW);
  delayMicroseconds(soundDelay);
// }
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
