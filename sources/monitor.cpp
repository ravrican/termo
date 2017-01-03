// Code by RV


#include "Arduino.h"
#include "monitor.h"


Monitor::Monitor(Debug* pDbg)
{
  m_pDbg = pDbg;
  m_pSerialMonitor = new SerialMonitor();
  m_nDisplayMode = DISPLAY_MODE_SERIAL;
}

void Monitor::SetDisplayMode(int nMode)
{
  m_nDisplayMode = nMode;
}

void Monitor::MonitorLoop(data_t* pData)
{
  m_pDbg->Mess("Monitor::MonitorLoop...");
  
  switch (m_nDisplayMode) {
    case DISPLAY_MODE_NONE:
      break;
    case DISPLAY_MODE_SERIAL:
      m_pSerialMonitor->Loop(pData);
      break;
    case DISPLAY_MODE_LCD:
      break;
    case DISPLAY_MODE_SERIAL_PLUS_LCD:
      m_pSerialMonitor->Loop(pData);
      break;
    default:
    break;
  }
}
