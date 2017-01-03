// Code by RV


#include "Arduino.h"
#include "buttons.h"


Buttons::Buttons(Debug* pDbg)
{
  m_pDbg = pDbg;

  pDbg->Mess("New objects in Buttons constructor", 5);
  m_pBouncer_menu  = new Bounce(); 
  m_pBouncer_up    = new Bounce(); 
  m_pBouncer_down  = new Bounce(); 
  m_pBouncer_plus  = new Bounce(); 
  m_pBouncer_minus = new Bounce(); 

  // Setup the first button with an internal pull-up 
  ButtonsInitialize();
  BounceInitialize();
}


void Buttons::BounceInitialize()
{
  m_pBouncer_menu->attach( BUTTON_MENU );
  m_pBouncer_menu->interval(BUTTON_BOUNCE_TIME);

  m_pBouncer_up->attach( BUTTON_UP );
  m_pBouncer_up->interval(BUTTON_BOUNCE_TIME);

  m_pBouncer_down->attach( BUTTON_DOWN );
  m_pBouncer_down->interval(BUTTON_BOUNCE_TIME);

  m_pBouncer_plus->attach( BUTTON_PLUS );
  m_pBouncer_plus->interval(BUTTON_BOUNCE_TIME);

  m_pBouncer_minus->attach( BUTTON_MINUS );
  m_pBouncer_minus->interval(BUTTON_BOUNCE_TIME);
}


void Buttons::ButtonsInitialize()
{
  pinMode(BUTTON_MENU,  INPUT_PULLUP);
  pinMode(BUTTON_UP,    INPUT_PULLUP);
  pinMode(BUTTON_DOWN,  INPUT_PULLUP);
  pinMode(BUTTON_PLUS,  INPUT_PULLUP);
  pinMode(BUTTON_MINUS, INPUT_PULLUP);
}


int Buttons::ReadButtons()
{
  // Vovan, retrigger example read!!!
  bool state_menu   = m_pBouncer_menu->update();
  bool state_up     = m_pBouncer_up->update();
  bool state_down   = m_pBouncer_down->update();
  bool state_plus   = m_pBouncer_plus->update();
  bool state_minus  = m_pBouncer_minus->update();

  int button_menu   = m_pBouncer_menu->read();
  int button_up     = m_pBouncer_up->read();
  int button_down   = m_pBouncer_down->read();
  int button_plus   = m_pBouncer_plus->read();
  int button_minus  = m_pBouncer_minus->read();

  int value = 0;
  if(button_menu==LOW)        value = BUTTON_ACT_MENU;
  else if(button_up==LOW)     value = BUTTON_ACT_UP;
  else if(button_down==LOW)   value = BUTTON_ACT_DOWN;
  else if(button_plus==LOW)   value = BUTTON_ACT_PLUS;
  else if(button_minus==LOW)  value = BUTTON_ACT_MINUS;

  return value;
}
