// Code by RV

#ifndef _LEDS_H_
#define _LEDS_H_

#include "debug.h"

//////////////////////////////////////////////////
// LED
#define LED_BUILTIN        13


class LEDs {
public:
	LEDs(Debug* pDbg);
	void InverseBlinkLED();

private:
	int m_nLEDBlinkState;

protected:
  Debug* m_pDbg;

};


#endif // _LEDS_H_
