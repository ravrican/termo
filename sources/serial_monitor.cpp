// Code by RV

#include "Arduino.h"
#include "serial_monitor.h"

void SerialMonitor::Loop(data_t* pData)
{
  String strDayNight;
  float fWantTemperature;
  if(pData->pState->bDayFlag)
  {
    strDayNight = "Day";
    fWantTemperature = pData->pState->fWantTempDay;
  }
  else
  {
    strDayNight = "Night";
    fWantTemperature = pData->pState->fWantTempNight;
  }

  String strHumidityCorrection;
  if(pData->pState->bHumidityCorrectionFlag)
    strHumidityCorrection = "ON";
  else
    strHumidityCorrection = "OFF";

  String strHeatIndexCorrection;
  if(pData->pState->bHeatIndexCorrectionFlag)
    strHeatIndexCorrection = "ON";
  else
    strHeatIndexCorrection = "OFF";


  Serial.println(" ----------------------------------------------------------");
  Serial.println( String( String("| Time...      ") + pData->pAllSensors->StringTime ) );
  Serial.print  ( String( String("| Utro / Vecher         = ") + String(pData->pState->nHourUtro, DEC) + " / " + String(pData->pState->nHourVecher, DEC) + " hour. " ) );
  Serial.println( String( String(" Now is: ") + strDayNight ) );
  Serial.println( String( String("| Inside Temp /2        = ") + String( (pData->pAllSensors->fTempInside + pData->pAllSensors->fTempInsideSecond)/2, DEC) + String(" C") ) );
  Serial.println( String( String("| Inside Humidity       = ") + String(pData->pAllSensors->fHumidity, DEC)  + String(" %") ) );
  Serial.println( String( String("| Inside HeatIndex      = ") + String(pData->pAllSensors->fHeatIndex, DEC) + String(" k") ) );
  Serial.println( String( String("| Outside               = ") + String(pData->pAllSensors->fTempOutside, DEC) + String(" C") ) );
  Serial.println( String( String("| Podacha               = ") + String(pData->pAllSensors->fTempPodacha, DEC) + String(" C") ) );
  Serial.println( String( String("| Obratka               = ") + String(pData->pAllSensors->fTempObratka, DEC) + String(" C") ) );
  Serial.println( String( String("| I Want Temperature    = ") + String(fWantTemperature, 1) ) );
  Serial.println( String( String("| Humidity Correction   = ") + strHumidityCorrection  ) );
  Serial.println( String( String("| Heat Index Correction = ") + strHeatIndexCorrection ) );
  Serial.println(" ----------------------------------------------------------");
  //m_pDbg->Mess("SerialMonitor::MonitorLoop...");
}

