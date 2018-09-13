#include <xc.h>
#include "rtcc.h"

unsigned short bin2bcd(unsigned short binary_value)
{
  unsigned short temp;
  unsigned short retval;

  temp = binary_value;
  retval = 0;

  while(1)
  {
    // Get the tens digit by doing multiple subtraction
    // of 10 from the binary value.
    if(temp >= 10)
    {
      temp -= 10;
      retval += 0x10;
    }
    else // Get the ones digit by adding the remainder.
    {
      retval += temp;
      break;
    }
  }

  return(retval);
}

// Input range - 00 to 99.
unsigned short bcd2bin(unsigned short bcd_value)
{
  unsigned short temp;

  temp = bcd_value;
  // Shifting upper digit right by 1 is same as multiplying by 8.
  temp >>= 1;
  // Isolate the bits for the upper digit.
  temp &= 0x78;

  // Now return: (Tens * 8) + (Tens * 2) + Ones

  return(temp + (temp >> 2) + (bcd_value & 0x0f));
} 


void RTCC_Initialize(void) {
    
    __builtin_write_OSCCONL(0x02);              // Turn on the secondary oscillator

    __builtin_write_RTCWEN();                   // Set the RTCWREN bit

    RCFGCALbits.RTCEN = 0;

    // set Wed Nov 25 11:45:36 CST 2015
    RCFGCALbits.RTCPTR = 3;                     // start the sequence
    RTCVAL = 0x15;                              // YEAR
    RTCVAL = 0x1129;                            // MONTH-1/DAY-1
    RTCVAL = 0x601;                             // WEEKDAY/HOURS
    RTCVAL = 0x2600;                            // MINUTES/SECONDS

    RTCPWC = 0x0400;                            // PWCPOL disabled; PWCEN disabled; RTCLK LPRC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled;

    RCFGCALbits.RTCEN = 1;                      // Enable RTCC

    RCFGCALbits.RTCWREN = 0;                    // Clear RTCWREN

    IEC3bits.RTCIE = 1;
}

void setRTCTime(unsigned char year, unsigned char month, unsigned char day, unsigned char weekday, unsigned char hour, unsigned char minute, unsigned char second)
{
	// Enable RTCC Timer Access
	/*
		NVMKEY is a write only register that is used to prevent accidental writes/erasures of Flash or
		EEPROM memory. To start a programming or an erase sequence, the following steps must be
		taken in the exact order shown:
		1. Write 0x55 to NVMKEY.
		2. Write 0xAA to NVMKEY. 
	*/
//	NVMKEY = 0x55;
//	NVMKEY = 0xAA;
//	RCFGCALbits.RTCWREN = 1;
    
    __builtin_write_RTCWEN();       // This should be the same as above

	RCFGCALbits.RTCEN = 0;  	// Disable RTCC module


	// Write to RTCC Timer
	RCFGCALbits.RTCPTR = 3;			// RTCC Value Register Window Pointer bits
	RTCVAL = bin2bcd(year); 					// Set Year (#0x00YY)
	RTCVAL = (bin2bcd(month) << 8) + bin2bcd(day);// Set Month and Day (#0xMMDD)
	RTCVAL = (bin2bcd(weekday) << 8) + bin2bcd(hour); 	// Set Weekday and Hour (#0x0WHH). Weekday from 0 to 6	
	RTCVAL = (bin2bcd(minute) << 8) + bin2bcd(second);  // Set Minute and Second (#0xMMSS)

	// Enable RTCC module
	RCFGCALbits.RTCEN = 1;

	// Disable RTCC Timer Access
	RCFGCALbits.RTCWREN = 0;
}

RTCTime getRTCTime()
{
	RTCTime retVal;

	// Wait for RTCSYNC bit to become ?0?
	while(RCFGCALbits.RTCSYNC==1);

	// Read RTCC timekeeping register
	RCFGCALbits.RTCPTR=3;

	retVal.year = bcd2bin(RTCVAL);

	unsigned int month_date=RTCVAL;
	retVal.month = bcd2bin(month_date >> 8);
	retVal.day = bcd2bin(month_date & 0xFF);

	unsigned int wday_hour=RTCVAL;
	retVal.weekday = bcd2bin(wday_hour >> 8);
	retVal.hour = bcd2bin(wday_hour & 0xFF);

	unsigned int min_sec=RTCVAL;
	retVal.minute = bcd2bin(min_sec >> 8);
	retVal.second = bcd2bin(min_sec & 0xFF);

	return retVal;
}