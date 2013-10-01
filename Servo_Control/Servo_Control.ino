#include <Servo.h>            //include Servo.h library to allow easy control of the two servo motors

Servo Sail;                   //define Servo object for the servo motor controlling the sails
Servo Rudder;                 //define Servo object for the servo motor controlling the rudder

void setup()
{
  Sail.attach(7);             //tell the sail servo object which pin on the Arduino board the servos control line is connected to
  Rudder.attach(6);           //tell the rudder servo object which pin on the Arduino board the servos control line is connected to
  
  Sail.write(90);             //center the servo position - position is given as int for the desired angle
  Rudder.write(90);           //(position range should be roughly from 0° to 180°)
  
  Serial.begin(115200);      //start serial bus with given data rate
  Serial.println("Enter servo position in degrees between 0 and 180.");
  Serial.println("s or r followed by the desired angle - example: s90");
}

void loop()
{ 
  while (Serial.available())                  //check serial bus for incoming data
  {
    parseServoString(Serial.readString());    //call function parseServoString()
  }
  delay(500); 
}

void parseServoString(String degree)           //function to determine which servo should be rotated to what degree
{ 
  if (degree[0] == 's')                        //check first character of input string if sail servo should be moved
  {
    degree.replace("s","");                    //delete first character of input string
    Sail.write(degree.toInt());                //convert remaining input string to integer and use as argument for Sail.write()
  }
  else if (degree[0] == 'r')                   //check first character of input string if rudder servo should be moved
  {
    degree.replace("r","");                    //delete first character of input string
    Rudder.write(degree.toInt());              //convert remaining input string to integer and use as argument for Sail.write()
  }
  else
  {
    Serial.println("illegal input");          //debug
  }
}
