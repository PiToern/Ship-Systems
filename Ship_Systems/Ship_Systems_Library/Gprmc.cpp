#include<Gprmc.h>

Gprmc::Gprmc()
: time(0), status("V"), latitude(0), longitude(0), speedOverGround(0), date(0)
{}



void Gprmc::stringInterpretation(String gpsString)
{
	
	gprmcIndex			= 0; 
	firstCommaIndex		= 0; 
	secondCommaIndex	= 0; 
	thirdCommaIndex		= 0; 
	fourthCommaIndex	= 0; 
	fifthCommaIndex		= 0; 
	sixthCommaIndex		= 0;  
	seventhCommaIndex	= 0; 
	eighthCommaIndex	= 0; 
	ninthCommaIndex		= 0;  
	tenthCommaIndex		= 0; 
	eleventhCommaIndex  = 0; 
	twelfthCommaIndex	= 0; 
	

	 time = 0; 
	 status = "V"; 
	 latitude = 0; 
	 longitude = 0; 
	 speedOverGround = 0; 
	 date = 0; 

	 gprmcFound = false; 
	 checksumFound		= false; 

	 checksum = 0;
	 character = '0'; 

	 if(gpsString.indexOf("GPRMC") != -1)
	 {
		 gprmcFound = true; 
	 }
	 
	 if(gprmcFound)
	 {
		gprmcIndex = gpsString.indexOf("GPRMC"); 
		firstCommaIndex		= gpsString.indexOf	(',', gprmcIndex		 + 1); 
		secondCommaIndex	= gpsString.indexOf	(',', firstCommaIndex	 + 1); 
		thirdCommaIndex		= gpsString.indexOf	(',', secondCommaIndex	 + 1); 
		fourthCommaIndex	= gpsString.indexOf	(',', thirdCommaIndex	 + 1); 
		fifthCommaIndex		= gpsString.indexOf	(',', fourthCommaIndex	 + 1); 
		sixthCommaIndex		= gpsString.indexOf	(',', fifthCommaIndex	 + 1); 
		seventhCommaIndex	= gpsString.indexOf	(',', sixthCommaIndex	 + 1); 
		eighthCommaIndex	= gpsString.indexOf	(',', seventhCommaIndex  + 1); 
		ninthCommaIndex		= gpsString.indexOf	(',', eighthCommaIndex	 + 1); 
		tenthCommaIndex		= gpsString.indexOf	(',', ninthCommaIndex    + 1); 
		eleventhCommaIndex	= gpsString.indexOf	(',', tenthCommaIndex	 + 1); 
		twelfthCommaIndex	= gpsString.indexOf (',', eleventhCommaIndex + 1); 



		/*
		 * substring()
		 * der Startindex ist inklusive, der Endindex ist exkluiv!
		 */

		if (gpsString.substring(twelfthCommaIndex + 2, twelfthCommaIndex + 3).equals("*"))
		{
			gprmcSentence			= gpsString.substring (gprmcIndex,			   twelfthCommaIndex + 5); 
		}

		timeString					= gpsString.substring (firstCommaIndex + 1,	     secondCommaIndex  ); 
		statusString 				= gpsString.substring (secondCommaIndex + 1,     thirdCommaIndex   ); 
		latitudeString				= gpsString.substring (thirdCommaIndex + 1,	     fourthCommaIndex  ); 
	 // northSouthString			= gpsString.substring (fourthCommaIndex + 1,     fifthCommaIndex   ); 
		longitudeString				= gpsString.substring (fifthCommaIndex + 1,	     sixthCommaIndex   ); 
	 // westEastString				= gpsString.substring (sixthCommaIndex + 1,	     seventhCommaIndex ); 
		speedOverGroundString		= gpsString.substring (seventhCommaIndex + 1,    eighthCommaIndex  ); 
	 // trackAngleString			= gpsString.substring (eighthCommaIndex + 1,     ninthCommaIndex   ); 
		dateString					= gpsString.substring (ninthCommaIndex + 1,	     tenthCommaIndex   ); 
	 // magneticVariationString		= gpsString.substring (tenthCommaIndex + 1,      eleventhCommaIndex); 
	 // magneticVariationSignString	= gpsString.substring (eleventhCommaIndex + 1,   twelfthCommaIndex ); 
		
		if (gpsString.substring(twelfthCommaIndex + 2, twelfthCommaIndex + 3).equals("*"))
		{
			checksumString			= gpsString.substring (twelfthCommaIndex + 3, twelfthCommaIndex + 5); 
			checksumFound			= true; 
		}

		/*
		 * Checksumme überprüfen:
		 * Die Checksumme wird berechnet, indem alle Zeichen zwischen dem $ und dem *
		 * duch ein (bitweise) exklusiv-oder berechnet werden.
		 * Angegeben wird die Checksumme durch eine Hexadezimalzahl, die hiner dem * steht. 
		 */

		for (int i = 0; i < gprmcSentence.length() - 3; i++)
		{
			checksum = checksum ^ byte(gprmcSentence[i]); 
		}

		/*
		 * Die Daten werden nur gesetzt, falls die empfangenen Daten
		 * valide sind und die Checksumme korrekt ist.
		 */

		if(statusString.equals("A") && hexToDec(checksumString) == checksum)
		{
			char floatBufferTime[15];
			timeString.toCharArray(floatBufferTime, sizeof(floatBufferTime)); 	
			setTime(atof(floatBufferTime)); 
	
			setStatus(statusString); 
	
			char floatBufferLat[15];
			latitudeString.toCharArray(floatBufferLat, sizeof(floatBufferLat)); 	
			setLatitude(atof(floatBufferLat)); 

			char floatBufferLon[15];
			longitudeString.toCharArray(floatBufferLon, sizeof(floatBufferLon)); 	
			setLongitude(atof(floatBufferLon)); 

			char floatBufferSpeed[15];
			speedOverGroundString.toCharArray(floatBufferSpeed, sizeof(floatBufferSpeed)); 	
			setSpeedOverGround(atof(floatBufferSpeed)); 

			char floatBufferDate[15];
			dateString.toCharArray(floatBufferDate, sizeof(floatBufferDate)); 	 
			setDate(atol(floatBufferDate)); 
		}
	 }

}


/*
 *	Methoden zur Zeit
 */

void Gprmc::setTime(float t)
{
	time = t; 
}

float Gprmc::getTime()
{
	return time; 
}

/*
 *	Methoden zum Status
 */

void Gprmc::setStatus (String s)
{
	status = s;
}

String Gprmc::getStatus()
{
	return status; 
}

/*
 *	Methoden zum Breitengrad
 */

void Gprmc::setLatitude(float lat)
{
	latitude = lat; 
}

float Gprmc::getLatitude()
{
	return latitude; 
}

/*
 *	Methoden zum Längengrad
 */

void Gprmc::setLongitude(float lon)
{
	longitude =  lon; 
}

float Gprmc::getLongitude()
{
	return longitude; 
}

/*
 *	Methoden zur Geschwindigkeit
 */

void Gprmc::setSpeedOverGround(float speed)
{
	speedOverGround = speed; 
}

float Gprmc::getSpeedOverGround()
{
	return speedOverGround; 
}

void Gprmc::setDate(unsigned long dat)

{
	date = dat; 
}

unsigned long Gprmc::getDate()
{
	return date; 
}


void Gprmc::printGpsData()
{
  //Serial.print("Time: "); 
  Serial.println(getTime()); 
  
  //Serial.print("Status: "); 
  Serial.println(getStatus()); 
  
  //Serial.print("Breitengrad: "); 
  Serial.println(getLatitude());
  
  //Serial.print("Längengrad: "); 
  Serial.println(getLongitude());
  
  //Serial.print("Geschwindigkeit: "); 
  Serial.println(getSpeedOverGround());
  
  //Serial.print("Datum:"); 
  Serial.println(getDate());
}

int Gprmc::hexToDec(String hex)
{
	int multiplier = 0; 
	int decOne; 
	int decTwo; 
	
	char one  = hex.charAt(0);
	multiplier = chooseMultiplier(one); 
	decOne =  multiplier *16; 

	char two = hex.charAt(1); 
	multiplier = chooseMultiplier(two); 
	decTwo = multiplier; 

	return decOne + decTwo; 
}


int Gprmc::chooseMultiplier(char mult)
{
	int multiplier = 0; 

	switch(mult)
	{
		case '1':	multiplier =  1; 
					break; 
		case '2':	multiplier =  2; 
					break; 
		case '3':	multiplier =  3; 
					break; 
		case '4':	multiplier =  4; 
					break; 
		case '5':	multiplier =  5; 
					break; 
		case '6':	multiplier =  6; 
					break; 
		case '7':	multiplier =  7; 
					break; 
		case '8':	multiplier =  8; 
					break; 
		case '9':	multiplier =  9; 
					break; 
		case 'A':   multiplier = 10; 
					break;	
		case 'B':	multiplier = 11;
					break;	
		case 'C':   multiplier = 12; 
					break; 
		case 'D':	multiplier = 13; 
					break; 
		case 'E':	multiplier = 14; 
					break; 
		case 'F':	multiplier = 15; 
					break; 
	}
	return multiplier; 
}

