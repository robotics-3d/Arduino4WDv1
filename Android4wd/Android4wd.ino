/*
  Nome: Arduino4WD.ino
  -------------------------------------------------------------
  Semplice programma per comandare tramite bluetooth il 4wd
  -------------------------------------------------------------
  
  Autore : Ferrarini Fabio - www.robotics-3d.com
           www.artigianitecnologici.it
  
  Data : 27/09/2014
  Revisione : 
*/
// Impostato ad 1 abilita il livello di debug
int debug = 1; //1 on 0 Off

#include "pitches.h"  
// DFRobot motor shield
#include <SoftwareSerial.h>


//
// Definizione dei pin utilizzati
//
const int signalPin = 12; 
const int echoPin = 11;
const int audioPin = 13;  //
const int bluetoothTx = 2;
const int bluetoothRx = 3;
// Pin shield Motori 
const int E1 = 5; 
const int M1 = 4;
const int E2 = 6;                     
const int M2 = 7;   

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

int distance = 0;            // obstacle distance
const int numOfReadings = 3; // number of readings to take items in the array
int readings[numOfReadings]; // stores the distance readings in an array
int arrayIndex = 0;          // arrayIndex of the current item in the array
int total = 0;               // stores the cumlative total
int avgDistance = 0;         // stores the average value

const long baud = 9600;

String pDist;
String pVelo;
String pDire;
String pVers;

String strPrint;


int mspeed = 100;  // Contiene il valore della velocita' 


void setup()  
{
  Serial.begin(baud); 
 // Setup Bluetooth 
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
 
  
  MotorStop();
  // Abilitazione pin audio
  pinMode(audioPin, OUTPUT);
  // Abilitazione pin motor shield
  pinMode(M1, OUTPUT);  
  pinMode(M2, OUTPUT);
  PlayMelody();  
  
}

uint8_t isColliding(){
  static uint8_t alreadyCollided = false;
  unsigned long buffer = 0;
  unsigned long temp = 0;
  for (uint8_t i=0; i<5; i++) {
    temp = getDistance();
    Serial.println(temp);

     buffer += temp;
  }
if ((buffer/5) < 50) { 
  if (!alreadyCollided) beeperr(); 
  alreadyCollided = true;
  MotorIndietro(mspeed);
  delay(400);
  MotorAvanti(mspeed);
  delay(100);
  MotorStop();
  return true;
    }
  alreadyCollided = false;
  return false;
}

uint8_t halt = false;

void loop()
{
isColliding();
  //Read from bluetooth and write to usb serial
  if(bluetooth.available())
  {
    char cCommand = (char)bluetooth.read();
    Serial.print(cCommand);
    if (cCommand == 'x') {
       MotorStop();
    }
       
    if (cCommand == 'a' && !halt) {
       MotorAvanti( mspeed );
    }
    if (cCommand == 'i') {
        MotorIndietro( mspeed );
    }
    if (cCommand == 'd') {
        MotorDestra( mspeed * 0.6);
    }
    if (cCommand == 's') {
        MotorSinistra( mspeed * 0.6 );
    }
    if (cCommand == 'h') {
        Help();
    }
    if (cCommand == '3') {
        mspeed = 30;
        if (debug == 1) {
         bluetooth.println("Vel : 30%");
        } 
    }
    if (cCommand == '9') {
        mspeed = 90;
        if (debug == 1) {
         bluetooth.println("Vel : 90%");
        } 
    }
   
      delay(100);
     // MotorStop();
  }


 }

void Help() {
  
   bluetooth.println("Arduino 4WD");
   bluetooth.println("----------");
   bluetooth.println("A=Avanti");
   bluetooth.println("I=Indietro");
   bluetooth.println("D=Destra");
   bluetooth.println("S=Sisistra");
   
  }

