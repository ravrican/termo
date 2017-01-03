// Code by RV

#ifndef _SENSORS_H_
#define _SENSORS_H_


//////////////////////////////////////////////////////////////////////////
// DHT
#include "DHT.h"
#define DHTPIN 7     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

//////////////////////////////////////////////////
// RTC
#include <RTClib.h>

//////////////////////////////////////////////////////////////////////////
// DS18
#include <OneWire.h>
#define DSPIN 8
#define DSPARAZITE 0
/*  Chip = DS18B20
    ROM = 28 DC 29 78 6 0 0 C9
    ROM = 28 2D F0 77 6 0 0 BB
    ROM = 28 3 51 77 6 0 0 E0
    ROM = 28 8F 70 77 6 0 0 42
*/


#include "debug.h"


typedef struct
{
    DateTime      TimeNow;
    String        StringTime;
    float fHumidity;
    float fTempInside;
    float fTempInsideSecond;
    float fTempPodacha;
    float fTempObratka;
    float fTempOutside;
    float fHeatIndex;
    
} sensors_t;


class Sensors {
public:
	Sensors(Debug* pDbg);
  sensors_t* GetAllSensors();
	
	//////////////////////////////////////////////////
	// RTC
	void GetStringTime(String* Time);
	int  GetHour();

	//////////////////////////////////////////////////////////////////////////
	// DHT
	float GetTemperature();
	float GetHumidity();
	float HeatIndex();

  //////////////////////////////////////////////////
  // DS18
  float GetTemperature(int nSensorNum);
  
private:
	//////////////////////////////////////////////////
	// RTC
	void GetTime();

  //////////////////////////////////////////////////
  // DS18
  float OneWireReadTemperature(byte addr[8]);

protected:
	Debug* m_pDbg;
  sensors_t m_AllSensors;
  
	//////////////////////////////////////////////////
	// RTC
	RTC_DS1307*   m_pRTC;
	DateTime*     m_pTimeNow; // указывает на элемент в структуре данных

	//////////////////////////////////////////////////
	// 22
  DHT* m_pDHT;

  //////////////////////////////////////////////////
  // DS18
  // DS18B20 temperature sensors' addresses: 
  byte sensor_1[8] = {0x28,0xDC,0x29,0x78,0x06,0x00,0x00,0xC9}; 
  byte sensor_2[8] = {0x28,0x2D,0xF0,0x77,0x06,0x00,0x00,0xBB}; 
  byte sensor_3[8] = {0x28,0x03,0x51,0x77,0x06,0x00,0x00,0xE0}; 
  byte sensor_4[8] = {0x28,0x8F,0x70,0x77,0x06,0x00,0x00,0x42};
  OneWire* m_pDS;
  
};


#endif // _SENSORS_H_
