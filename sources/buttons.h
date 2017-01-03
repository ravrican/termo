// Code by RV

#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include <Bounce2.h>
#include "data.h"


#define BUTTON_MENU   2
#define BUTTON_UP     3
#define BUTTON_DOWN   4
#define BUTTON_PLUS   5
#define BUTTON_MINUS  6
#define BUTTON_ACT_MENU    1
#define BUTTON_ACT_UP      2  
#define BUTTON_ACT_DOWN    3    
#define BUTTON_ACT_PLUS    4
#define BUTTON_ACT_MINUS   5 
#define BUTTON_BOUNCE_TIME 	300


class Buttons {

public:
  Buttons(Debug* pDbg);
  int ReadButtons();

private:
	void BounceInitialize();
	void ButtonsInitialize();

protected:
	Debug* m_pDbg;
  Bounce* m_pBouncer_menu; 
	Bounce* m_pBouncer_up; 
	Bounce* m_pBouncer_down; 
	Bounce* m_pBouncer_plus; 
	Bounce* m_pBouncer_minus; 

};


#endif // _BUTTONS_H_
