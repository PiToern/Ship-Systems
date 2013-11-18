#include<GPRMC_Library.h>

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
	 found = false; 

	 if(gpsString.indexOf("GPRMC") != -1)
	 {
		 found = true; 
	 }
	 
	 if(found)
	 {
		gprmcIndex = gpsString.indexOf("GPRMC"); 
		firstCommaIndex		= gpsString.indexOf	(',', gprmcIndex		+ 1); 
		secondCommaIndex	= gpsString.indexOf	(',', firstCommaIndex	+ 1); 
		thirdCommaIndex		= gpsString.indexOf	(',', secondCommaIndex	+ 1); 
		fourthCommaIndex	= gpsString.indexOf	(',', thirdCommaIndex	+ 1); 
		fifthCommaIndex		= gpsString.indexOf	(',', fourthCommaIndex	+ 1); 
		sixthCommaIndex		= gpsString.indexOf	(',', fifthCommaIndex	+ 1); 
		seventhCommaIndex	= gpsString.indexOf	(',', sixthCommaIndex	+ 1); 
		eighthCommaIndex	= gpsString.indexOf	(',', seventhCommaIndex + 1); 
		ninthCommaIndex		= gpsString.indexOf	(',', eighthCommaIndex	+ 1); 
		tenthCommaIndex		= gpsString.indexOf	(',', ninthCommaIndex   + 1); 
		eleventhCommaIndex	= gpsString.indexOf	(',', tenthCommaIndex	+ 1); 

		/*
		 * substring()
		 * der Startindex ist inklusive, der Endindex ist exkluiv!
		 */

		timeString				= gpsString.substring(firstCommaIndex +1,	  secondCommaIndex  ); 
		statusString 			= gpsString.substring(secondCommaIndex +1,    thirdCommaIndex   ); 
		latitudeString			= gpsString.substring(thirdCommaIndex +1,	  fourthCommaIndex  ); 
		// N					= gpsString.substring(fourthCommaIndex +1,    fifthCommaIndex   ); 
		longitudeString		    = gpsString.substring(fifthCommaIndex +1,	  sixthCommaIndex   ); 
		// E					= gpsString.substring(sixthCommaIndex +1,	  seventhCommaIndex ); 
		speedOverGroundString	= gpsString.substring(seventhCommaIndex +1,   eighthCommaIndex  ); 
		//						= gpsString.substring(eighthCommaIndex +1,	  ninthCommaIndex   ); 
		dateString				= gpsString.substring(ninthCommaIndex +1,	  tenthCommaIndex   ); 
		//						= gpsString.substring(tenthCommaIndex +1,     eleventhCommaIndex); 
		//						= gpsString.substring(eleventhCommaIndex +1,  twelfthCommaIndex ); 

		/*
		 * Setzen der einzelnen Werte, die ausgelesen werden sollen. 
		 */

	
			/*
		 * String in Float konvertieren:
		 * Anleitung unter: http://stackoverflow.com/questions/18200035/how-do-you-convert-a-string-to-a-float-or-int
		 */

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
		setLongitude(atof(floatBufferSpeed)); 

		setDate(dateString.toInt()); 
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

void Gprmc::setDate(int dat)

{
	date = dat; 
}

int Gprmc::getDate()
{
	return date; 
}


void Gprmc::printGpsData()
{
  Serial.print("Time: "); 
  Serial.println(getTime()); 
  
  Serial.print("Status: "); 
  Serial.println(getStatus()); 
  
  Serial.print("Breitengrad: "); 
  Serial.println(getLatitude());
  
  Serial.print("Längengrad: "); 
  Serial.println(getLongitude());
  
  Serial.print("Geschwindigkeit: "); 
  Serial.println(getSpeedOverGround());
  
  Serial.print("Datum:"); 
  Serial.println(getDate());
}


/*

GPRMC (recommended minimum sentence)


 $GPRMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,ddmmyy,x.x,a*hh
1    = UTC of position fix
2    = Data status (V=navigation receiver warning)
3    = Latitude of fix
4    = N or S
5    = Longitude of fix
6    = E or W
7    = Speed over ground in knots
8    = Track made good in degrees True
9    = UT date
10   = Magnetic variation degrees (Easterly var. subtracts from true course)
11   = E or W
12   = Checksum


*/
//
