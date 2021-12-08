//The Radiohead library for the RF transmitter and reciever can be downloaded from http://www.airspayce.com/mikem/arduino/RadioHead/
//The GY6050 library for the MPU6050 sensor can be downloaded from https://github.com/Freddrup/GY6050
//Extraxt the zip files into the Documents/Arduino/Libraries folder

#include <RH_ASK.h>
#include <Wire.h>
#include <GY6050.h>

GY6050 acc(0x68); //I2C address of MPU6050
RH_ASK driver;  //transmitter object
char* msg="100";

void setup()
{   
     acc.initialisation();   //initialize acc obj
     Serial.begin(9600);
     if (!driver.init())
     Serial.println("init failed");
}

void loop()
{
     const char *msg = "hello";
     int AcX=acc.refresh('A', 'X'); //Acccelration along X axis
     int AcY=acc.refresh('A', 'Y'); //Acccelration along Y axis
     delay(25); 
     if(AcX>=20 && AcX<=60)
     {
          msg="Front";
          Serial.println("Front");
     }
     else if(AcX<=-20 && AcX>=-60)
     {
          Serial.println("Back");
          msg="Back";
     }
     else if(AcY>=20 && AcY<=60)
     {
          Serial.println("Left");
          msg="Left";
     }
     else if(AcY<=-20 && AcY>=-60)
     {
          Serial.println("Right");
          msg="Right";
     }
     else
     {
          Serial.println("Stop");
          msg="Stop";
     }
     delay(100);
     
     driver.send((uint8_t *)msg, strlen(msg));  // transmits the data
     driver.waitPacketSent();
     delay(200);  
}
