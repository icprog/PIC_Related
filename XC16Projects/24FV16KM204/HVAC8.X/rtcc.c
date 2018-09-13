#include <xc.h>
#include "rtcc.h"
#include "user.h"
#include "lcd.h"
//***************************************************************************************************************************************************************
extern char call, powerFail;                            //call is used to set HMI delay time, based on what function you are in 

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
//***************************************************************************************************************************************************************

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
//***************************************************************************************************************************************************************


void RTCC_Initialize(void) {
    
    __builtin_write_OSCCONL(0x02);              // Turn on the secondary oscillator

    __builtin_write_RTCWEN();                   // Set the RTCWREN bit

    RCFGCALbits.RTCEN = 0;

//    _RTCCLK1 = 0;       // Set RTCC Clock Source to External Osc
//    _RTCCLK0 = 0;

    // set Thursday Dec 10 03:01:50 CST 2015
    RCFGCALbits.RTCPTR = 3;                     // start the sequence
    RTCVAL = 0x15;                              // YEAR
    RTCVAL = 0x1210;                            // MONTH-1/DAY-1
    RTCVAL = 0x403;                             // WEEKDAY/HOURS
    RTCVAL = 0x0150;                            // MINUTES/SECONDS

//    RTCPWC = 0x0400;                            // PWCPOL disabled; PWCEN disabled; RTCLK LPRC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled;
    RTCPWC = 0x0000;                            // PWCPOL disabled; PWCEN disabled; RTCLK ExtOsc; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled;

    RCFGCALbits.CAL7 = 1;                      // Enable RTCC Calibration all zeros but bit 7, too fast by ~1 sec in 24 hrs
    RCFGCALbits.CAL6 = 0;                      // Enable RTCC Calibration
    RCFGCALbits.CAL5 = 0;                      // Enable RTCC Calibration
    RCFGCALbits.CAL4 = 0;                      // Enable RTCC Calibration
    RCFGCALbits.CAL3 = 0;                      // Enable RTCC Calibration
    RCFGCALbits.CAL2 = 0;                      // Enable RTCC Calibration
    RCFGCALbits.CAL1 = 0;                      // Enable RTCC Calibration this and bit 7, at least 2 seconds fast in a day               
    RCFGCALbits.CAL0 = 0;                      // Enable RTCC Calibration this and bit 7, at least 1 seconds slow in a day
    
    RCFGCALbits.RTCEN = 1;                      // Enable RTCC

    RCFGCALbits.RTCWREN = 0;                    // Clear RTCWREN

    IEC3bits.RTCIE = 1;
}
//***************************************************************************************************************************************************************

void setRTCTime(unsigned char year, unsigned char month, unsigned char day, unsigned char weekday, unsigned char hour, unsigned char minute, unsigned char second)
{
	// Enable RTCC Timer Access
	//
	//	NVMKEY is a write only register that is used to prevent accidental writes/erasures of Flash or
	//	EEPROM memory. To start a programming or an erase sequence, the following steps must be
	//	taken in the exact order shown:
	//	1. Write 0x55 to NVMKEY.
	//	2. Write 0xAA to NVMKEY. 
	
//	NVMKEY = 0x55;
//	NVMKEY = 0xAA;
//	RCFGCALbits.RTCWREN = 1;
    
    __builtin_write_RTCWEN();                           // This should be the same as above

	RCFGCALbits.RTCEN = 0;                              // Disable RTCC module


	// Write to RTCC Timer
	RCFGCALbits.RTCPTR = 3;                             // RTCC Value Register Window Pointer bits
	RTCVAL = bin2bcd(year);                             // Set Year (#0x00YY)
	RTCVAL = (bin2bcd(month) << 8) + bin2bcd(day);      // Set Month and Day (#0xMMDD)
	RTCVAL = (bin2bcd(weekday) << 8) + bin2bcd(hour); 	// Set Weekday and Hour (#0x0WHH). Weekday from 0 to 6	
	RTCVAL = (bin2bcd(minute) << 8) + bin2bcd(second);  // Set Minute and Second (#0xMMSS)

	// Enable RTCC module
	RCFGCALbits.RTCEN = 1;

	// Disable RTCC Timer Access
	RCFGCALbits.RTCWREN = 0;
}
//***************************************************************************************************************************************************************

RTCTime getRTCTime()
{
	RTCTime retVal;

	while(RCFGCALbits.RTCSYNC==1);                      // Wait for RTCSYNC bit to become ?0?
	
	RCFGCALbits.RTCPTR=3;                               // Read RTCC timekeeping register

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
//***************************************************************************************************************************************************************

bool SetTime()
{
    call = 1;                       // Set call (calling function) to 1)
    
    RTCTime time;                   // declare the type of the time object

    time = getRTCTime();            // Read current time from RTCC

    char sel = 0;
    
    bool done = false;

    unsigned int timer = 0;                 // Used to return to operation if user does not finish setting time! (MAX SETTING 4096!!)

    while(!done)
    {
        if(timer < 1)
        {
            LCD_Clear();
        }
        
        timer += 1;
                    
        if(timer > 1000)                      
        {
            timer = 0;
            LCD_Clear();
            done = true;                    // Exit while loop
        }


        LCDWriteIntXY(0,0,time.year,2);
        LCDWriteStringXY(0,2,"/");
        LCDWriteIntXY(0,3,time.month,2);
        LCDWriteStringXY(0,5,"/");
        LCDWriteIntXY(0,6,time.day,2);
        LCDWriteIntXY(0,9,time.weekday,2);
        LCDWriteIntXY(0,12,time.hour,2);
        LCDWriteStringXY(0,14,":");
        LCDWriteIntXY(0,15,time.minute,2);
        LCDWriteStringXY(0,17,":");
        LCDWriteIntXY(0,18,time.second,2);
        
        LCDWriteStringXY(2,0," Enter = Next Field ");
        LCDWriteStringXY(3,0,"Up/Dn keys to change");
        
        
        
        if(sel*3 == 0)
        {
            LCDWriteStringXY(1,sel*3,"^^");     // Draw Pointer
        }
        
        else
        {
            LCDWriteStringXY(1,sel*3 - 3,"   ^^");     // Draw Pointer
        }
        
        char key = menuRead();

        switch(key)
        {
            case KEY_UP:
                if(sel==0)
                {
                    if (time.year == 99)
                    {
                        time.year = 00;
                    }
                    else
                    {
                        time.year += 1;
                    }
                }
                
                if(sel==1)
                {
                    if (time.month == 12)
                    {
                        time.month = 1;
                    }
                    else
                    {
                        time.month += 1;
                    }
                }
                
                if(sel==2)
                {
                    if (time.day == 31)
                    {
                        time.day = 1;
                    }
                    else
                    {
                        time.day +=1;
                    }
                }

                if(sel==3)
                {
                    if (time.weekday == 6)
                    {
                        time.weekday = 0;
                    }
                    else
                    {
                        time.weekday += 1;
                    }
                }

                if(sel==4)
                {
                    if (time.hour == 23)
                    {
                        time.hour = 0;
                    }
                    else
                    {
                        time.hour += 1;
                    }
                }
                
                if(sel == 5)    
                {
                    if(time.minute == 59)
                    {
                        time.minute = 0;
                    }
                    else
                    {
                        time.minute += 1;
                    }
                }
                
                if (sel == 6)
                {
                    if (time.second == 59)
                    {
                        time.second = 0;
                    }
                    else
                    {
                        time.second += 1;
                    }
                }
            break;
            
            case KEY_DOWN:
                if(sel == 0)
                {
                    if (time.year == 0)
                    {
                        time.year = 99;
                    }
                    else
                    {
                        time.year -= 1;
                    }
                }
                
                if(sel == 1)
                {
                    if (time.month == 1)
                    {
                        time.month = 12;
                    }
                    else
                    {
                        time.month -= 1;
                    }
                }
                
                if(sel == 2)
                {
                    if (time.day == 1)
                    {
                        time.day = 31;
                    }
                    else
                    {
                        time.day -= 1;
                    }
                }

                if(sel == 3)
                {
                    if (time.weekday == 0)
                    {
                        time.weekday = 6;
                    }
                    else
                    {
                        time.weekday -= 1;
                    }
                }

                if(sel == 4)
                {
                    if (time.hour == 0)
                    {
                        time.hour = 23;
                    }
                    else
                    {
                        time.hour -= 1;
                    }
                }
                
                if(sel == 5)    
                {
                    if(time.minute == 0)
                    {
                        time.minute = 59;
                    }
                    else
                    {
                        time.minute -= 1;
                    }
                }
                
                if (sel == 6)
                {
                    if (time.second == 0)
                    {
                        time.second = 59;
                    }
                    else
                    {
                        time.second -= 1;
                    }
                }
                break;

                case KEY_RIGHT:     // Change our selection
                {
                    if (sel == 6)
                    {
                        sel = 0;
                        LCD_Clear();
                        done = true;
                    }
                    else
                    {
                        sel += 1;
                    }
                break;
                }
                
                case KEY_ENTER:     // Change our selection
                {
                    if (sel == 6)
                    {
                        sel = 0;
                        LCD_Clear();
                        done = true;
                    }
                    else
                    {
                        sel += 1;
                    }
                break;
            }
        }
        
        setRTCTime(time.year, time.month, time.day, time.weekday, time.hour, time.minute, time.second);
    }
    LCD_Clear();
    call = 0;                                           // Set call back to 0 before exiting function
    powerFail = 0;                                      //We have just set the time, so, re-set the powerFail Status Bit
    return (1);
}

