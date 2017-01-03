// Code by RV


#include "Arduino.h"
#include "leds.h"


LEDs::LEDs(Debug* pDbg)
{
  m_pDbg = pDbg;
  pinMode(LED_BUILTIN, OUTPUT);
	m_nLEDBlinkState = 0;
}


void LEDs::InverseBlinkLED()
{
  if(m_nLEDBlinkState == LOW) {
     digitalWrite(LED_BUILTIN, HIGH);
     m_nLEDBlinkState = HIGH;
  }
  else {
      digitalWrite(LED_BUILTIN, LOW);
      m_nLEDBlinkState = LOW;
  }
}
