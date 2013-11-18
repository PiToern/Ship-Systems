#include<string.h>
#include<GPRMC_Library.h>

/* 
 * Die Pins des GPS müssen folgendermaßen mit denen des Arduino verbunden werden:
 * 5V -> 5V
 * GND -> GND
 * Shield -> GND
 * TX -> RX (Pin 15)
 * RX -> TX (Pin 14)
 */

char incomingChar;  
String incomingData = ""; 

Gprmc gpsData; 

void setup()
{
  Serial.begin(9600);
  Serial3.begin(38400); 
}

void loop()
{
  while(Serial3.available())
  {
    incomingChar = Serial3.read(); 
    incomingData += incomingChar; 
  }
    
  if(incomingData.length() >= 420)
  {
    gpsData.stringInterpretation(incomingData);
    gpsData.printGpsData(); 
    incomingData = "";
  }
}


