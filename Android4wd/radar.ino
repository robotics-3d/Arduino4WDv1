/*
  Nome: radar.ino
  -----------------------------------------------------------------------
  Libreria per gestire gli ultrasuoni per il rilevamento degli ostacoli
  -----------------------------------------------------------------------
  Autore : Ferrarini Fabio - www.robotics-3d.com
    email: ferrarini
           www.artigianitecnologici.it
           
  Data : 27/09/2014
*/
/**
 * Calcola  la distanza dall'oggetto
 * 
 */
long getDistance()
{
  unsigned long pulseTime;
  unsigned long distance;

  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);      // set signal pin low
  delayMicroseconds(2);              // for 2 microseconds
  digitalWrite(signalPin, HIGH);     // send a trigger pulse
  delayMicroseconds(10);             // 10 microseconds long
  digitalWrite(signalPin, LOW);      // signal pin low waiting for echo pulse

  pinMode(signalPin, INPUT);
  pulseTime = pulseIn(echoPin, HIGH); // read echo pulse length in microseconds
  distance = pulseTime/58;              // distance in centimeters

  return distance;
}
