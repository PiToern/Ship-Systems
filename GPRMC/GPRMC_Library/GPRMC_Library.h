#ifndef _GPRMC_H_INCLUDED 
#define _GPRMC_H_INCLUDED

#include<Arduino.h>
#include<stdlib.h> // für Methode atof

class Gprmc
{
	public: 
		Gprmc(); 

		void stringInterpretation(String); 

		void printGpsData(); 


		void setTime(float t);
			
		float getTime();

		void setStatus (String s);
			
		String getStatus();
			
		void setLatitude(float lat);
			
		float getLatitude();
			
		void setLongitude(float lon);
		
		float getLongitude();
			
		void setSpeedOverGround(float speed);
			
		float getSpeedOverGround();

		void setDate(int dat); 

		int getDate(); 

	private:
		float time; 
		String status; 
		float latitude; 
		float longitude; 
		float speedOverGround; 
		int date; 
		bool found; 

		int gprmcIndex; 
		int firstCommaIndex; 
		int secondCommaIndex; 
		int thirdCommaIndex; 
		int fourthCommaIndex; 
		int fifthCommaIndex; 
		int sixthCommaIndex; 
		int seventhCommaIndex; 
		int eighthCommaIndex; 
		int ninthCommaIndex;  
		int tenthCommaIndex; 
		int eleventhCommaIndex; 
		int twelfthCommaIndex; 

		String timeString; 
		String statusString;
		String latitudeString; 
		String longitudeString; 
		String speedOverGroundString; 
		String dateString; 

}; 

#endif