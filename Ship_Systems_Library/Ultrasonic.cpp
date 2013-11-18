#include <ultrasonic.h>

/*
 *	Standard Konstruktor 
 */

Ultrasonic::Ultrasonic()
{}

void Ultrasonic::initialize()
{
  pinMode(getTrigPin(), OUTPUT); 
  pinMode(getEchoPin(), INPUT); 
}

int Ultrasonic::getDistance()
{
	// Hier wird das Signal ausgesendet. 
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(trigPin, LOW);
  
	// Hier wird das empfangene Signal verarbeitet. 
	zeitdifferenz = pulseIn(echoPin, HIGH);
	entfernung = (zeitdifferenz * 343) / 20000;
	return entfernung; 
}

int Ultrasonic::getTrigPin()
{
	return trigPin; 
}

int Ultrasonic::getEchoPin()
{
	return echoPin;  
}