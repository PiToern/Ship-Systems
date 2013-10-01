#include <Servo.h>

Servo Sail;

void setup()
{
  Sail.attach(7);
  Sail.write(90);
  Serial.begin(115200);
  Serial.println("Enter servo position in degrees between 0 and 180.");
}

void loop()
{ 
  while (Serial.available())
  {
    int degree = Serial.parseInt();
    Serial.println(degree);
    Sail.write(degree);
    Serial.println("Again?!");
    delay (250);
  }
}


