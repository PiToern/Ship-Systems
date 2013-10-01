#include <Servo.h>            //include Servo.h library to allow easy control of the two servo motors
#include <string.h>
#include <Stream.h>

Servo Sail;                   //define Servo object for the servo motor controlling the sails
Servo Rudder;                 //define Servo object for the servo motor controlling the rudder

void setup()
{
  Sail.attach(7);             //tell the sail servo object which pin on the Arduino board the servos control line is connected to
  Rudder.attach(6);
  
  Sail.write(90);             //center the servo position - position is given as int for the desired angle
  Rudder.write(90);           //(position range should be roughly from 0° to 180°)
  
  Serial.begin(115200);      //start serial bus with given data rate
  Serial.println("Enter servo position in degrees between 0 and 180.");
  Serial.println("s or r followed by the desired angle - example: s90 ");
}

void loop()
{ 
  while (Serial.available())              //check serial bus for incoming data
  {
    parseServoString(Serial.readString());
  }
  delay(500); 
}

void parseServoString(String degree)
{ 
  if (degree[0] == 's')
  {
    degree.replace("s","");
    Sail.write(degree.toInt());
  }
  else if (degree[0] == 'r')
  {
    degree.replace("r","");
    Rudder.write(degree.toInt());
  }
  else
  {
    Serial.println("illegal input");
  }
}
