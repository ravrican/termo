// Code by RV

#ifndef _DATA_H_
#define _DATA_H_


#include "sensors.h"
#include "state.h"


typedef struct
{
  sensors_t* pAllSensors;
  state_t*   pState;
} data_t;


#endif // _DATA_H_
