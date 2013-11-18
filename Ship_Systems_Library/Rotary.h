#ifndef _ROTARY_H_INCLUDED // Is the header Gprmc.h already included?
#define _ROTRAY_H_INCLUDED

#include "Arduino.h"

class Rotary
{
	public:

		Rotary();
		void initialize(); 
		void updateEncoder(); 
		int updateEncoderPosition(int); 
		int getPosition(); 
		void setPosition(int);
		int getEncoderValue(); 
	
	private:

	    static const int encoderPinA = 2;
		static const int encoderPinB = 3;
 
		volatile int encoderPosition; 
		volatile int encoderValue; 
		volatile int lastEncoderValueA; 
		volatile int lastEncoderValueB; 
	
}; 


#endif
