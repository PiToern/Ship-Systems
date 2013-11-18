#include<rotary.h>

/*
 *	Konstruktor  - Initialisierung der Variablen auf 0, bzw. auf HIGH für die Pins
 */

Rotary::Rotary()
: encoderValue(0), encoderPosition(0), lastEncoderValueA(HIGH), lastEncoderValueB(HIGH)
{}


void Rotary::initialize()
{
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT); 
    
    digitalWrite(encoderPinA, HIGH); 
    digitalWrite(encoderPinB, HIGH); 	
}

void Rotary::updateEncoder()
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
  

	// Falls encoderValue <= -48 oder >= 48 ist muss die Variable wieder auf auf Null gesetzt werden, 
	// da die Position des Encoders nur Werte zwischen 0 und 11 annehmen soll.
    if (encoderValue >= 48)
    {
        encoderValue = 0; 
    }
    if (encoderValue <= -48)
    {
        encoderValue = 0; 
    }
    encoderPosition = encoderValue / 4; 

	// Angleichen der Variable encoderPosition auf die gewünschten Werte.
	// Falls gegen den Uhrzeigersinn gedreht wird, 
	// sollen keine negativen Werte für die Position angezeigt werden,
	// sondern, es soll einfach "rückwärts" gezählt werden. 
	encoderPosition = updateEncoderPosition(encoderPosition); 
}



int Rotary::updateEncoderPosition(int encoderPos)
{
	 switch(encoderPos)
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

	 return encoderPosition; 
}

int Rotary::getPosition()
{
	return encoderPosition; 
}

void Rotary::setPosition(int encoderPos)
{
	encoderPosition = encoderPos; 
}

int Rotary::getEncoderValue()
{
	return encoderValue; 
}