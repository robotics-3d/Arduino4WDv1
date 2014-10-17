/*
  Nome: TestUltrasuoni.ino
  -------------------------------------------------------------
  Semplice programma per misurare la distanza tramite HC-SR04
  -------------------------------------------------------------
  
  Autore : Ferrarini Fabio - www.robotics-3d.com
           www.artigianitecnologici.it
  
  Data : 27/09/2014
  Revisione : 
*/
#include "pitches.h"  


const int signalPin = 12; 
const int echoPin = 11;
const int audioPin = 13;

int distance = 0;            // distanza ostacolo
const int numOfReadings = 3; // numero letture
int readings[numOfReadings]; // memorizza le letture in un array
int arrayIndex = 0;          // 
int total = 0;               // Totale
int avgDistance = 0;         // Media
int debug =1;
const long baud = 9600;
String pDist;


void setup()  
{
  Serial.begin(baud); 
  // 
  pinMode(audioPin, OUTPUT);
  // Esegue una melodia 
  PlayMelody();  

}

void loop()
{
  distance = getDistance();

  total = total - readings[arrayIndex]; //  
  readings[arrayIndex] = distance;      //  
  total = total + readings[arrayIndex]; //  
  arrayIndex++;                         //  

  // 
  if (arrayIndex >= numOfReadings)  {
    arrayIndex = 0;
  }

  // calcola la media della distanza
  avgDistance = total / numOfReadings;
  pDist = String(avgDistance);
  Serial.print("distanza:");
  Serial.println(pDist);
 
 }

// Funzione di calcolo della distanza
long getDistance()
{
  unsigned long pulseTime;
  unsigned long distance;

  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);      //  
  delayMicroseconds(2);              // 2 microsecondi
  digitalWrite(signalPin, HIGH);     // send a trigger pulse
  delayMicroseconds(10);             // 10 microsecondi
  digitalWrite(signalPin, LOW);      // signal pin low waiting for echo pulse

  pinMode(signalPin, INPUT);
  pulseTime = pulseIn(echoPin, HIGH); // read echo pulse length in microseconds
  distance = pulseTime/58;            // distance in centimeters

  return distance;
}



