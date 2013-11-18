#include<Ultrasonic.h>
#include<Rotary.h>
#include<Gprmc.h>
#include<Gy80.h>
#include<Wire.h>  // wird für I2C benötigt (GY80) 
#include <Servo.h> //include Servo.h library to allow easy control of the two servo motors

/* 
 * Pinbelegung: 
 *
 * Ultraschallsensor: 
 * VCC      -> 5V
 * TRIG     -> 12
 * ECHO     -> 13
 * GND      -> GND
 *
 * Rotary Encoder: 
 * A        -> 2
 * B        -> 3
 * C        -> GND
 *
 * GPS Modul:
 * 5V       -> 5V
 * GND      -> GND
 * Shield   -> GND
 * TX       -> RX (Pin 15)
 * RX       -> TX (Pin 14)
 *
 * GY80:
 * VCC 3.3V ->3.3V
 * GND      -> GND
 * SCL      -> 21
 * SDA      -> 2
 */


Servo Sail;                   //define Servo object for the servo motor controlling the sails
Servo Rudder;                 //define Servo object for the servo motor controlling the rudder

/*
 * Initialisierung der einzelnen Objekte
 */
Ultrasonic UltrasonicModul; 
Rotary RotaryEncoder; 
Gprmc GpsData; 
GY80 MultiSensorModul; 
 
// Benötigte Variablen für das Auslesen der Daten des GPS Moduls: 
char incomingChar = 0;  
String incomingData = ""; 



void setup()
{
  Serial.begin(115200); 
  Serial3.begin(38400); 
  
  Wire.begin(); 
 
  UltrasonicModul.initialize(); 
  RotaryEncoder.initialize(); 
  MultiSensorModul.initialize(); 
  
  attachInterrupt(0, doUpdate, CHANGE); 
  attachInterrupt(1, doUpdate, CHANGE); 
  
  Sail.attach(7);             //tell the sail servo object which pin on the Arduino board the servos control line is connected to
  Rudder.attach(6);           //tell the rudder servo object which pin on the Arduino board the servos control line is connected to
  
  Sail.write(90);             //center the servo position - position is given as int for the desired angle
  Rudder.write(90);           //(position range should be roughly from 0° to 180°)
}

void loop()
{
 
  Serial.print("Entfernung (Ultraschallmodul): ");  // Zeile nur zu Test- und Vorführungszwecken - ansonsten auskommentieren und ggf. Identifizierer mitschicken
  Serial.println(UltrasonicModul.getDistance() );
  
 
  Serial.print("Position (Rotary Encoders): ");  // Zeile nur zu Test- und Vorführungszwecken - ansonsten auskommentieren und ggf. Identifizierer mitschicken
  Serial.println(RotaryEncoder.getPosition());
 
  
  readGPSData(); 
   
  Serial.print("Latitude (GPS Modul): ");  // Zeile nur zu Test- und Vorführungszwecken - ansonsten auskommentieren und ggf. Identifizierer mitschicken
  Serial.println(GpsData.getLatitude()); 
  
  Serial.print("Longitude (GPS Modul): ");  // Zeile nur zu Test- und Vorführungszwecken - ansonsten auskommentieren und ggf. Identifizierer mitschicken
  Serial.println(GpsData.getLongitude()); 
  
  getDataFromGY80(); 
  
  while (Serial.available())                  //check serial bus for incoming data
  {
    parseServoString(Serial.readString());    //call function parseServoString()
  }
  delay(500); 
  
  
}

void doUpdate()
{
  RotaryEncoder.updateEncoder(); 
}

void readGPSData()
{
    while(Serial3.available())
    {
      incomingChar = Serial3.read(); 
      incomingData += incomingChar; 
    }
    
    if(incomingData.length() >= 420)
    {
      GpsData.stringInterpretation(incomingData);
      // GpsData.printGpsData(); 
      incomingData = ""; 
    }
}

void getDataFromGY80()
{
  /***BEGIN GET L3G4200D VALUES***/

  MultiSensorModul.getGyroValues();
  MultiSensorModul.printGyroValues();
  delay(MultiSensorModul.getGyroDelay());
  
/***END GET L3G4200D VALUES***/


/***BEGIN GET ADXL345 VALUES***/

MultiSensorModul.getAccValues();
MultiSensorModul.printAccValues();
delay(MultiSensorModul.getAccDelay());

/***END GET ADXL345 VALUES***/


/***BEGIN GET HMC5883L VALUES***/

MultiSensorModul.getMagValues();
MultiSensorModul.printMagValues();
delay(MultiSensorModul.getMagDelay());

/***END GET HMC5883L VALUES***/
  
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
  
