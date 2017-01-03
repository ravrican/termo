// Code by RV

#ifndef _STATE_H_
#define _STATE_H_

#include "debug.h"


typedef struct
{
    bool  bDayFlag;
    bool  bHumidityCorrectionFlag;
    bool  bHeatIndexCorrectionFlag;
    float fWantTempDay;
    float fWantTempNight;
    int   nHourUtro;
    int   nHourVecher;

} state_t;


class State {
public:
	State(Debug* pDbg);
  state_t* GetState();
  void SaveState(state_t* pState);
	
private:
  void ReadState();
  void WriteState();

protected:

  Debug*  m_pDbg;
  state_t m_State;
 
};


#endif // _STATE_H_
