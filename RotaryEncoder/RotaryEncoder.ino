/*
 * Der Code wurde unter Zuhilfenahme folgender Quellen erstellt:
 * Tracking Rotary movement in a Busy Sketch
 * Arduino Cookbook - chapter 6.12
 * und
 * http://playground.arduino.cc/Main/RotaryEncoders
 */
 
 
 /*
  * Wichtig: 
  * Der Rotary Encoder besitzt weder eine Anfangs noch eine Endposition.
  * Es wird lediglich bestimmt, ob im Uhrzeigersinn oder gegen den Uhrzeigersinn
  * gedreht wurde. 
  * Um die exakte Position bestimmen zu können, muss sich der Rotary Encoder 
  * zum Programmstart in der festgelegten Startposition befinden, d.h.
  * so, dass die Spitze der Fahne exakt Richtung Bug zeigt. 
  * Diese Position wird als Position 0 bezeichnet. 
  * Abbildung 7.1 (in der Ausarbeitung) zeigt die einzelnen Positionen des Rotary Encoders.
  *
  *
  * Pinbelegung: 
  * A -> 2
  * B -> 3
  * C -> GND
  *
  * Achtung: 
  * Falls Pin A und Pin B vertauscht werden,
  * sind die Positionen genau spiegelverkehrt!
  */
 
 
 const int encoderPinA = 2;
 const int encoderPinB = 3;
 
 int temp = 0; // zur Bestimmung der Encoder Position (Position 0 bis Position 11)
 
  volatile int encoderPosition   = 0; 
  volatile int encoderValue      = 0; 
  volatile int lastEncoderValueA = HIGH; 
  volatile int lastEncoderValueB = HIGH; 

  
  void setup()
  {
    Serial.begin(9600);
    
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT); 
    
    digitalWrite(encoderPinA, HIGH); 
    digitalWrite(encoderPinB, HIGH); 
    
    
    /* 
     * Syntax: 
     * attachInterrupt(interrupt, function, mode) 
     * Der erste Parameter gibt den Interrupt Pin Identifierer an:
     * 0 ist der Interrupt Pin Identifier für Pin 2
     * 1 ist der Interrupt Pin Identifier für Pin 3
     * (auf dem Arduino Mega 2560 gibt außerdem folgende Interrupt Identifier: 
     * 2 für Pin 21, 3 für Pin 20, 4 für Pin 19 und 5 für Pin 18)
     * Der zweite Parameter gibt die Funktion an, die ausgeführt werden soll,
     * sobald ein Interrupt auftritt. 
     * Der letzte Parameter gibt an, was den Interrupt auslösen soll:
     * FALLING - Stromabfall von 5V auf 0V (von hig auf low)
     * RISING - Stromanstieg von 0V auf 5V (von low auf high)
     * CHANGE - Stromabfall oder -anstieg (Wechsel von high auf low oder umgekehrt)
     * LOW - der Pin ist im Zustand low 
     */
     
    attachInterrupt(0, updateEncoder, CHANGE);
    attachInterrupt(1, updateEncoder, CHANGE); 
  }
  
  void loop()
  {
    // Bestimmen der Position des Rotary Encoders
    
    temp = (int) encoderPosition; 
    switch(temp)
    {
      case -1: 
                encoderPosition = 11;
                break;
      case -2: 
                encoderPosition = 10;
                break;
      case -3: 
                encoderPosition = 9;
                break;
      case -4: 
                encoderPosition = 8;
                break;
      case -5: 
                encoderPosition = 7;
                break;
      case -6: 
                encoderPosition = 6;
                break;
      case -7: 
                encoderPosition = 5;
                break;
      case -8: 
                encoderPosition = 4;
                break;
      case -9: 
                encoderPosition = 3;
                break;
      case -10: 
                encoderPosition = 2;
                break;
      case -11: 
                encoderPosition = 1;
                break;
       default: 
                break;
    }
 

  Serial.print("Encoder Position: "); 
  Serial.println(encoderPosition);

  delay(1000); //just here to slow down the output, and show it will work  even during a delay
  }
  
  
  void updateEncoder()
  {      
    /*
     * Drehung im Uhrzeigersinn
     */
     
    // Änderung an Pin A
    if ( lastEncoderValueA == LOW  && lastEncoderValueB == HIGH && digitalRead(encoderPinA) == HIGH && digitalRead(encoderPinB) == HIGH ) 
    {
        lastEncoderValueA = HIGH; 
        encoderValue++;
    }
    if ( lastEncoderValueA == HIGH && lastEncoderValueB == LOW  && digitalRead(encoderPinA) == LOW  && digitalRead(encoderPinB) == LOW  )
    {
        lastEncoderValueA = LOW; 
        encoderValue++;    
    }
    // Änderung an Pin B
    if ( lastEncoderValueA == HIGH && lastEncoderValueB == HIGH && digitalRead(encoderPinA) == HIGH && digitalRead(encoderPinB) == LOW  )
    {
         lastEncoderValueB = LOW; 
         encoderValue++;
    }   
    if ( lastEncoderValueA == LOW && lastEncoderValueB == LOW  && digitalRead(encoderPinA) == LOW   && digitalRead(encoderPinB) == HIGH )
    {
         lastEncoderValueB = HIGH; 
         encoderValue++;
    }   
    
     /*
     * Drehung gegen den Uhrzeigersinn
     */
     
     // Änderung an Pin A    
     if ( lastEncoderValueA == LOW  && lastEncoderValueB == LOW  && digitalRead(encoderPinA) == HIGH && digitalRead(encoderPinB) == LOW  )
     {
        lastEncoderValueA = HIGH; 
        encoderValue--; 
     }
     if ( lastEncoderValueA == HIGH && lastEncoderValueB == HIGH && digitalRead(encoderPinA) == LOW  && digitalRead(encoderPinB) == HIGH )
     {
        lastEncoderValueA = LOW; 
        encoderValue--; 
     }
    // Änderung an Pin B
    if ( lastEncoderValueA == LOW  && lastEncoderValueB == HIGH && digitalRead(encoderPinA) == LOW   && digitalRead(encoderPinB) == LOW  )
     {
         lastEncoderValueB = LOW; 
         encoderValue--;
     }   
     if (lastEncoderValueA == HIGH && lastEncoderValueB == LOW  && digitalRead(encoderPinA) == HIGH  && digitalRead(encoderPinB) == HIGH )
     {
         lastEncoderValueB = HIGH; 
         encoderValue--;
     }   
          
          
    if (encoderValue >= 48)
    {
        encoderValue = 0; 
    }
    if (encoderValue <= -48)
    {
        encoderValue = 0; 
    }
    encoderPosition = encoderValue / 4; 

  }
  
