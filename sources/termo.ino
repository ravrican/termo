#define VERSION "v.0.3.0"

#include <Wire.h>

#include "debug.h"
#include "sensors.h"
#include "state.h"
#include "leds.h"
#include "monitor.h"
#include "buttons.h"
#include "data.h"

//////////////////////////////////////////////////
// DEBUG
#define DEBUG_LEVEL           1
Debug dbg(DEBUG_LEVEL);
Debug* pDbg = 0;

///////////////////////////////
//   INTERVALS
#define DISPLAY_UPDATE_TIME       1000
#define MAIN_LOOP_DELAY           500
volatile unsigned long gv_unTimeOfLastDisplayUpdate = 0;  // for monitor

///////////////////////////////
//   OBJECTS
Monitor* pMon = 0;
LEDs* pLEDs = 0;
Sensors* pSens = 0;
State* pState = 0;
Buttons* pButtons = 0;
data_t Data;


//////////////////////////////////////////////////
// BUTTONS

//volatile boolean gv_bButtonPressFlag = false; // нажатие кнопки



void CheckButtons(int value)
{
  if(value>0)
  {
    pDbg->Mess("Press button...", value);

    //gv_bButtonPressFlag = true;
    //o_disp.DisplayButtonPress(value);

    switch(value) {
    case BUTTON_ACT_MENU: 
      {
        //if(gv_bMenuMode==false) 
        //  gv_bMenuMode=true;
        //else 
        //  gv_bMenuMode=false;

        //o_disp.SetMenuMode(gv_bMenuMode);
        break;
      }
    case BUTTON_ACT_UP: 
      {
        //if(gv_bMenuMode==true) 
          //o_disp.MenuPreview();
        break;
      }
    case BUTTON_ACT_DOWN: 
      {
        //if(gv_bMenuMode==true) 
          //o_disp.MenuNext();
        //else
          // View Journal
          break;
      }
    case BUTTON_ACT_PLUS: 
      {
        break;
      }
    case BUTTON_ACT_MINUS: 
      {
        break;
      }
    }
  }
}


void UpdateMonitor()
{
  unsigned long currentTime = millis();

    if(currentTime - gv_unTimeOfLastDisplayUpdate > DISPLAY_UPDATE_TIME)
    {
      // Get Sensors
      sensors_t* pAllSensors;
      pAllSensors = pSens->GetAllSensors();

      // Get State
      state_t* pSt;
      pSt = pState->GetState();

      // Fill DATA
      Data.pAllSensors = pAllSensors;
      Data.pState = pSt;

      // DATA to Monitor -->>
      pMon->MonitorLoop(&Data);
      
      gv_unTimeOfLastDisplayUpdate = currentTime;
    }
}

//////////////////////////////////////////////////
// SERIAL SETUP
void SerialSetup()
{
  Serial.begin(9600);
  while (!Serial) { 
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println();
  Serial.println();
  Serial.println(VERSION);
}

//////////////////////////////////////////////////
// SETUP
void setup()
{
  // SERIAL
  SerialSetup();  // Now work Debug!

  // DEBUG
  pDbg = &dbg;
  pDbg->SetDebugLevel(1);
  pDbg->Mess("New objects in Main Setup...", 5);

  // OBJECTS
  pMon     = new Monitor(pDbg);  
  pMon->SetDisplayMode(DISPLAY_MODE_SERIAL);
  pSens    = new Sensors(pDbg);
  pLEDs    = new LEDs(pDbg);
  pState   = new State(pDbg);
  pButtons = new Buttons(pDbg);
}


//////////////////////////////////////////////////
// LOOP
void loop()
{
  //delay(MAIN_LOOP_DELAY);
  //pLEDs->InverseBlinkLED();

  int value = pButtons->ReadButtons();
  CheckButtons( value );
  //UpdateMonitor();
}


