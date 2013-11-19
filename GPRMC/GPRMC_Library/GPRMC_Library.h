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

		void setDate(unsigned long dat); 

		unsigned long getDate(); 

		int hexToDec(String h);

		int chooseMultiplier(char m); 

	private:
		float time; 
		String status; 
		float latitude; 
		float longitude; 
		float speedOverGround; 
		unsigned long date; 
		bool gprmcFound; 
		bool checksumFound; 

		int checksum; 
		char character; 

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
		

		String gprmcSentence; 
		String timeString; 
		String statusString;
		String latitudeString; 
		String northSouthString; 
		String longitudeString; 
		String westEastString;
		String speedOverGroundString; 
		String trackAngleString;
		String dateString; 
		String magneticVariationString; 
		String magneticVariationSignString; 
		String checksumString; 

}; 

#endif