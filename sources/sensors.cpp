// Code by RV

#include "Arduino.h"
#include "sensors.h"

Sensors::Sensors(Debug* pDbg)
{
  m_pDbg = pDbg;
  m_pTimeNow = &(m_AllSensors.TimeNow);

  //////////////////////////////////////////////////
  // RTC
  m_pRTC = new RTC_DS1307();
  
  if (! m_pRTC->begin()) {
    m_pDbg->Mess("Couldn't find RTC. I don't work...");
    while (1);
  }
  else
    m_pDbg->Mess("RTC is find!");

  if (! m_pRTC->isrunning()) {
    m_pDbg->Mess("RTC is NOT running! Setup RTC now from compilation file...");
    m_pRTC->adjust(DateTime(F(__DATE__), F(__TIME__)));
 }
 else
     m_pDbg->Mess("RTC is running!");

  //////////////////////////////////////////////////
  // DHT
  m_pDHT = new  DHT(DHTPIN, DHTTYPE);
  m_pDHT->begin();

  //////////////////////////////////////////////////
  // DS18
  m_pDS = new OneWire(DSPIN);
}

sensors_t* Sensors::GetAllSensors()
{
  GetTime();                                            // RTC
  m_AllSensors.fHumidity          = GetHumidity();      // DHT22
  m_AllSensors.fTempInside        = GetTemperature();   // DHT22
  m_AllSensors.fTempInsideSecond  = GetTemperature(1);  // DS18
  m_AllSensors.fTempPodacha       = GetTemperature(2);  // DS18
  m_AllSensors.fTempObratka       = GetTemperature(3);  // DS18
  m_AllSensors.fTempOutside       = GetTemperature(4);  // DS18
  m_AllSensors.fHeatIndex         = HeatIndex();        // DHT22

  return &m_AllSensors;
}
  
//////////////////////////////////////////////////
// RTC
void Sensors::GetTime()
{
  if(m_pRTC != 0)
  {
    *m_pTimeNow = m_pRTC->now();
  }
  
  m_AllSensors.StringTime  = String(m_pTimeNow->day(), DEC);
  m_AllSensors.StringTime += '/';
  m_AllSensors.StringTime += String(m_pTimeNow->month(), DEC);
  m_AllSensors.StringTime += '/';
  m_AllSensors.StringTime += String(m_pTimeNow->year(), DEC);
  m_AllSensors.StringTime += ' ';
  m_AllSensors.StringTime += String(m_pTimeNow->hour(), DEC);
  m_AllSensors.StringTime += ':';
  m_AllSensors.StringTime += String(m_pTimeNow->minute(), DEC);
  m_AllSensors.StringTime += ':';
  m_AllSensors.StringTime += String(m_pTimeNow->second(), DEC);
}

void Sensors::GetStringTime(String* Time)
{
  GetTime();
  *Time = m_AllSensors.StringTime;
}

int Sensors::GetHour()
{
  GetTime();
  return m_pTimeNow->hour();
}


//////////////////////////////////////////////////////////////////////////
// DHT
float Sensors::GetTemperature()
{
	float t;
	t = m_pDHT->readTemperature();
	m_pDbg->Mess("Read Temperature from DHT22", t);
	return t;
}

float Sensors::GetHumidity()
{
	float h;
	h = m_pDHT->readHumidity();
	m_pDbg->Mess("Read Humidity from DHT22", h);
	return h;
}

float Sensors::HeatIndex()
{
	float h;
	float t;
	float hic;
	h   = m_pDHT->readHumidity();
	t   = m_pDHT->readTemperature();
	hic = m_pDHT->computeHeatIndex(t, h, false);
	m_pDbg->Mess("Read Heat Index from DHT22", hic);
	return hic;
}

//////////////////////////////////////////////////
// 18

float Sensors::GetTemperature(int nSensorNum)
{
  float fTemp = 0.0;
  switch (nSensorNum) {
    case 1:
      fTemp = OneWireReadTemperature(sensor_1);
      break;
    case 2:
      fTemp = OneWireReadTemperature(sensor_2);
      break;
    case 3:
      fTemp = OneWireReadTemperature(sensor_3);
      break;
    case 4:
      fTemp = OneWireReadTemperature(sensor_4);
      break;
    default:
    break;
  }

  return fTemp;
}
float Sensors::OneWireReadTemperature(byte addr[8])
{
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  float celsius;

  m_pDS->reset();
  m_pDS->select(addr);
  if(DSPARAZITE)
    m_pDS->write(0x44, 1);        // start conversion, with parasite power on at the end
  else
    m_pDS->write(0x44);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a m_pDS->depower() here, but the reset will take care of it.
  
  present = m_pDS->reset();
  m_pDS->select(addr);    
  m_pDS->write(0xBE);         // Read Scratchpad

  //Serial.print("  DEBUG [DS18] >>>>>>>>>>");
  //Serial.print("  Data = ");
  //Serial.print(present, HEX);
  //Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = m_pDS->read();
    //Serial.print(data[i], HEX);
    //Serial.print(" ");
  }
  //Serial.print(" CRC=");
  //Serial.print(OneWire::crc8(data, 8), HEX);
  //Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  //Serial.print("  Temperature = ");
  //Serial.print(celsius);
  //Serial.println(" C");
  //Serial.println("  DEBUG [DS18] <<<<<<<<<<<");
  m_pDbg->Mess("Temperature from DS18", celsius);

  return celsius;
}




