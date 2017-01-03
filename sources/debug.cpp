// Code by RV

#include "Arduino.h"
#include "debug.h"

Debug::Debug(int nLevel)
{
  	m_nDebug = nLevel;
}

void Debug::SetDebugLevel(int n)
{
  m_nDebug = n;
}

void Debug::Mess(String out) 
{ 
  String mess;
  
  if (m_nDebug == 1) 
      mess = String( String("      D >> ") + String(out) ); 

    Serial.println( mess ); 
}

void Debug::Mess(String out, int n) 
{ 
  String mess;
  
  if (m_nDebug == 1) 
      mess = String( String("      D >> ") + String(out) + String(" [") + String(n, DEC) +String("]") ); 

    Serial.println( mess ); 
}

void Debug::Mess(String out, float f) 
{ 
  String mess;
  
  if (m_nDebug == 1) 
      mess = String( String("      D >> ") + String(out) + String(" [") + String(f, FLOAT_DECIMAL_PLACES) +String("]") ); 

    Serial.println( mess ); 
}

