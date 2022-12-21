/******************************************************************************
Basic_Readings.ino

https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DSO
https://github.com/sparkfun/SparkFun_Qwiic_6DoF_LSM6DSO_Arduino_Library
******************************************************************************/

#include "SparkFunLSM6DSO.h"
#include "Wire.h"
#include <Servo.h>
//#include "SPI.h"

LSM6DSO myIMU; //Default constructor is I2C, addr 0x6B
Servo servoX;
Servo servoY;

#define servoXPin 9
#define servoYPin 10
int buttonPin = 4;

int currentBtn;
int lastBtn;
bool fix = false; 

int angleX = 0;
int angleY = 0;

char msg;
int msgInt;


void setup() {
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  pinMode(buttonPin, INPUT);

  Serial.begin(115200);
  delay(500); 
  
  Wire.begin();
  delay(10);
  if( myIMU.begin() )
    Serial.println("Ready.");
  else { 
    Serial.println("Could not connect to IMU.");
    Serial.println("Freezing");
  }

  if( myIMU.initialize(BASIC_SETTINGS) )
    Serial.println("Loaded Settings.");

}


void loop()
{
  // get serial input
  msg=Serial.read();
  msgInt = msg -'0';


  while(msgInt=0){
    servoX.write(100);
    delay(100);
    servoX.write(10);
    delay(100);

    msg=Serial.read();
    msgInt = msg -'0';
  }

  while(msgInt=1){
    //button toggle
    currentBtn = digitalRead(buttonPin);
    // Serial.println(currentBtn);
    if (lastBtn == LOW && currentBtn == HIGH) {
      fix =! fix;         // LED 가 LOW 면 HIGH 로 바꿔준다.
    }
    lastBtn = currentBtn;

    if(fix==true){
      
    } else {
      angleX = myIMU.readFloatAccelX()*10;
      angleY = myIMU.readFloatAccelY()*10;
      // Serial.print(angleX);
      // Serial.print(',');
      // Serial.print(angleY);
      // Serial.println(',');

      int servoAngleX = map(angleX, -10, 10, 1, 179);
      int servoAngleY = map(angleY, -10, 10, 1, 179);

      servoX.write(servoAngleX);
      servoY.write(servoAngleY);
      delay(30);
    }  
  msg=Serial.read();
  msgInt = msg -'0';
  }

  //active mode

}
