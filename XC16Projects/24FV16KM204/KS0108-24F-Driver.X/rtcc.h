#ifndef rtcc_H
#define	rtcc_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "stdbool.h"
//***************************************************************************************************************************************************************

/*
RTC Timer on a PIC24HJ128GP202.
Adapted from dsPIC33F/PIC24H Reference Manual Section 37
*/ 

typedef struct _RTCTime
{
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char weekday; // Monday is 0, Sunday is 6
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
} RTCTime;

//***************************************************************************************************************************************************************

void RTCC_Initialize(void);
//***************************************************************************************************************************************************************

void setRTCTime(unsigned char year, unsigned char month, unsigned char day, unsigned char weekday, unsigned char hour, unsigned char minute, unsigned char second);
//***************************************************************************************************************************************************************

RTCTime getRTCTime();
//***************************************************************************************************************************************************************

bool SetTime(void);

#endif