// Code by RV

#ifndef _MONITOR_H_
#define _MONITOR_H_

#include "serial_monitor.h"
#include "sensors.h"
#include "data.h"
#include "debug.h"

#define DISPLAY_MODE_NONE                 0
#define DISPLAY_MODE_SERIAL               1
#define DISPLAY_MODE_LCD                  2
#define DISPLAY_MODE_SERIAL_PLUS_LCD      3



class Monitor {

public:
	Monitor(Debug* pDbg);
	void MonitorLoop(data_t* pData);
  void SetDisplayMode(int nMode);

protected:
	SerialMonitor* m_pSerialMonitor;
  Debug* m_pDbg;
  int m_nDisplayMode;
};


#endif // _MONITOR_H_
