#ifndef RTCC_H
#define	RTCC_H

#include <xc.h>
#include "lcd.h"
#include "touch.h"
//***************************************************************************************************************************************************************

typedef struct _RTCTime
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int weekday; // Monday is 0, Sunday is 6
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
} RTCTime;

//***************************************************************************************************************************************************************

void RTCC_Initialize(void);
//***************************************************************************************************************************************************************

void setRTCTime(unsigned int year, unsigned int month, unsigned int day, unsigned int weekday, unsigned int hour, unsigned int minute, unsigned int second);
//***************************************************************************************************************************************************************

RTCTime getRTCTime();
//***************************************************************************************************************************************************************

void SetTime(void);

#endif