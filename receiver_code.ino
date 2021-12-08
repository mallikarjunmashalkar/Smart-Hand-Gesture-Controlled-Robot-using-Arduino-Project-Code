//The Radiohead library for the RF transmitter and reciever can be downloaded from http://www.airspayce.com/mikem/arduino/RadioHead/
//Extraxt the zip files into the Documents/Arduino/Libraries folder

#include <RH_ASK.h>
RH_ASK driver;
String str;

void setup()
{
    Serial.begin(9600); 
    if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN]; //max size of the buffer
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen))  //receive the message and store it in a buffer
    {
	      str=(char*)buf;  //copy the message from the buffer to a string
	      Serial.println(str);  //print the message in the serial monitor
    }
    delay(200);
    
    if(str=="Front")
    {
        digitalWrite(5,HIGH); //5,6 - Left Motor
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH); //7,8 - Right Motor
        digitalWrite(8,LOW);
    }
    else if(str=="Back")
    {
        digitalWrite(5,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(8,HIGH);
    }
    else if(str=="Left")
    {
        digitalWrite(5,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(8,LOW);
    }
    else if(str=="Right")
    {
        digitalWrite(5,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        digitalWrite(8,HIGH); 
    }    
    else
    {
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        digitalWrite(8,LOW);
    }
}
