// Code by RV

#include "Arduino.h"
#include "state.h"

State::State(Debug* pDbg)
{
  m_pDbg = pDbg;
  
  m_State.bDayFlag = true;
  m_State.bHumidityCorrectionFlag = false;
  m_State.bHeatIndexCorrectionFlag = false;
  m_State.fWantTempDay = 22.0;
  m_State.fWantTempNight = 23.0;
  m_State.nHourUtro = 7;
  m_State.nHourVecher = 21;

  ReadState();
}

state_t* State::GetState()
{
  return &m_State;
}
  
void State::SaveState(state_t* pState)
{
  WriteState();
}
  
void State::ReadState()
{
  
}

void State::WriteState()
{
  
}



