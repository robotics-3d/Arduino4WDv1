#include <QTRSensors.h>

// This example is designed for use with a SINGLE QTR-1RC sensor 
// This is a much cut-down version of the Pololu Example code

#define NUM_SENSORS   4     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low

// Create instance of sensors. Only using one sensor connected to pin 12
QTRSensorsRC qtrrc((unsigned char[]) {10,9,8,7},  NUM_SENSORS, 
                          TIMEOUT,QTR_EMITTERS_ON ); 

unsigned int sensors[NUM_SENSORS];
 unsigned int sensorValues[NUM_SENSORS];
void setup()
{
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  qtrrc.read(sensorValues);

  // print the sensor values
  unsigned char i;
  for (i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print (",");
  }
  Serial.println(" ");
  delay(250);
  // follow_segment(); // follow the black line - segui la linea nera
}


// PID parameters
int Kp=120;
int Ki=100;
int Kd=100;
// follow the black line - segui la linea nera 
void follow_segment()
{
  int last_proportional = 0;
  long integral=0;
  int primo=0;
  int posizione = qtrrc.readLine(sensors); // read the IR sensors - leggi i sensori IR 
 

  long int proportional = posizione;
  int P = proportional * Kp/1000; // Proportional parameter 
  long int derivative = proportional - last_proportional; //Derivative parameter
  if (primo==0) // firt cycle set derivative to zero - al primo giro imposta il derivativo a zero
     {
      primo=1;
      derivative=0;
    }
  int D=derivative*Kd/1000;
  integral += proportional;
  int I=integral*Ki/1000; //integral parameter 
  // Remember the last position - ricorda l'ultima posizione
  last_proportional = proportional;
  int PID =P + I + D; //calculate the PID 
  // print some values on the serial port - scrivi qualche valore sulla seriale
  unsigned char zz;
   for (zz = 0; zz < NUM_SENSORS; zz++)
    {
      Serial.print(sensors[zz]);
      Serial.print(' ');
    }
    Serial.print(" position: ");
    Serial.print(posizione);
    Serial.print(" P:");
    Serial.print(P);
    Serial.print(" I:");
    Serial.print(I);
    Serial.print(" D:");
    Serial.print(D);
    Serial.print(" PID:");
    Serial.print(PID);
  // set the values for the motors based on the PID gain - setta i valori del motore basati sul PID
    const int maximum = 40; // the maximum speed
     if (PID > 0){
       if (PID > maximum) PID=maximum;
       //motor_speed2(motor_B,maximum);
       //motor_speed2(motor_A,maximum-PID);
      Serial.print(" Motore_B:");     Serial.print(maximum);
    Serial.print(" Motore_A:");      Serial.print(maximum-PID);
      }
      else {
       if (PID < -maximum) PID=-maximum;
        //motor_speed2(motor_B,maximum+PID);
        //motor_speed2(motor_A,maximum);
      Serial.print(" Motore_B:");     Serial.print(maximum+PID);
    Serial.print(" Motore_A:");      Serial.print(maximum);
      }
      Serial.println("");
}
// IR sensor calibration 
void SensorCalibration() {
  int counter, i;
  for (counter=0; counter<40; counter++)
  {
    if (counter < 10 || counter >= 30) {
      //motor_speed2(motor_A,10);
      //motor_speed2(motor_B,-10);
    }
    else   {
      //motor_speed2(motor_A,-10);
      //motor_speed2(motor_B,10);
    }
    qtrrc.calibrate();
    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
     // print the calibration minimum values measured when emitters were on
    for (i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
    // print the calibration maximum values measured when emitters were on
  for (i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  //MotorStop();
  delay(2000);
}
