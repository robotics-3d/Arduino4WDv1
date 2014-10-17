/*
  Nome: sound.ino
  -------------------------------------------------------------
  Libreria per gestire i suoni
  -------------------------------------------------------------
  Autore : Ferrarini Fabio - www.robotics-3d.com
           www.artigianitecnologici.it
 
  Data : 27/09/2014
*/
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
