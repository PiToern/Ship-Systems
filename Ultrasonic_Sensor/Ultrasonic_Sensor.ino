/*
 * Der Quellcode wurde mithilfe folgender Quelle erstellt: 
 * http://arduino.cc/en/Tutorial/Ping?from=Tutorial.UltrasoundSensor
 *
 */


/* 
 * Pinbelegung: 
 *
 * VCC  -> 5V
 * TRIG -> 12
 * ECHO -> 13
 * GND  -> GND
 *
 */
 
 const int trigPin = 12; 
 const int echoPin = 13; 
 long zeitdifferenz; 
 int entfernung; 
 
 void setup()
 {
   Serial.begin(9600); 
   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 
 }
 
 void loop()
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

  // Signal ausgeben
  Serial.print(entfernung);
  Serial.print(" cm");
  Serial.println(); 
 
  delay(100);
 
 }
