#include <Wire.h>
#include <VL53L0X.h>
#include <MPU9250_asukiaaa.h>
#define XSHUT_pin1 12
#define XSHUT_pin2 11
#define XSHUT_pin3 10
#define Sensor1_newAddress 42
#define Sensor2_newAddress 43
#define Sensor3_newAddress 44
MPU9250 mySensor;
VL53L0X Sensor1;
VL53L0X Sensor2;
VL53L0X Sensor3;

uint8_t sensorId;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;


void setup() {

  Serial.begin(9600);

  Wire.begin();

////////////////////////////// ToF Sensor Setup \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  pinMode(XSHUT_pin1, OUTPUT);
  pinMode(XSHUT_pin2, OUTPUT);
  pinMode(XSHUT_pin3, OUTPUT);

  mySensor.setWire(&Wire);
  
  pinMode(XSHUT_pin3, INPUT);
  delay(10);
  Sensor3.setAddress(Sensor3_newAddress);
  pinMode(XSHUT_pin2, INPUT);
  delay(10);
  Sensor2.setAddress(Sensor2_newAddress);
  pinMode(XSHUT_pin1, INPUT);
  delay(10);
  Sensor1.setAddress(Sensor1_newAddress);

  Sensor1.init();
  Sensor2.init();
  Sensor3.init();

  Sensor1.setTimeout(500);
  Sensor2.setTimeout(500);
  Sensor3.setTimeout(500);

  Sensor1.startContinuous();
  Sensor2.startContinuous();
  Sensor3.startContinuous();

////////////////////////////// IMU Setup \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  mySensor.beginMag();
  mySensor.beginGyro();
  sensorId = mySensor.readId();
  
  
////////////////////////////// Vibration Motor Setup \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  int outMin = 2; // Lowest input pin
  int outMax = 9; // Highest input pin

  for(int i=outMin; i<=outMax; i++)
  {
    pinMode(i, OUTPUT);
  }

}

void loop() {

////////////////////////////// Vibration Motor Control Navigation \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
          
  if(Serial.available() > 0){
    char command = Serial.read();

      switch(command){

        case 'a':
          tapMot(1);
          break;
        case 'b':
          tapMot(2);
          break;
        case 'c':
          tapMot(3);
          break;
        case 'd':
          tapMot(4);
          break;
        case 'e':
          tapMot(5);
          break;
        case 'f':
          tapMot(6);
          break;
        case 'g':
          tapMot(7);
          break;
        case 'h':
          break;
          tapMot(8);
        case 'z':
          mySensor.magUpdate();
          mDirection = mySensor.magHorizDirection();
          Serial.print(mDirection);
          break;

      }



  }

////////////////////////////// ToF Obstacle Avoidance \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

          
  if (Sensor1.readRangeContinuousMillimeters() < 300 && gX > -50 && gX < 50){ 
    digitalWrite(2, HIGH);
  }
  
  else{
    digitalWrite(2, LOW);
  }

  if (Sensor2.readRangeContinuousMillimeters() < 300 && gX > -50 && gX < 50){
    digitalWrite(4, HIGH);
  }
  
  else{
    digitalWrite(4, LOW);  
  }

  if (Sensor3.readRangeContinuousMillimeters() < 300 && gX > -50 && gX < 50){
    digitalWrite(6, HIGH);
  }
  
  else{
    digitalWrite(6, LOW);
  }
  

  delay(10);
  
}

//          a
//    h   * * *  b
//     *        *
//    *          *
// g *            * c
//    *          *
//     *        *
//     f  * * *  d
//          e

void tapMot(int vibMot){
////////////////////////////// "Tap" Motors \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);

  delay (500);


  digitalWrite(vibMot+1, HIGH);
  delay(400);
  digitalWrite(vibMot+1, LOW);
  delay(200);
  digitalWrite(vibMot+1, HIGH);
  delay(400);
  digitalWrite(vibMot+1, LOW);
  delay(500);
  
}

