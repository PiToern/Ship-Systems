#ifndef _ULTRASONIC_H_INCLUDED // Is the header Gprmc.h already included?
#define _ULTRASONIC_H_INCLUDED

#include "Arduino.h"

class Ultrasonic
{
	public:

		Ultrasonic();
		void initialize(); 
		int getDistance(); 
		int getTrigPin(); 
		int getEchoPin();
		

	private:

		static const int trigPin = 12; 
		static const int echoPin = 13; 
		long zeitdifferenz; 
		int entfernung; 
}; 

#endif
