/* First time I ever got the RTCC to work was the following date
    RTCVAL = 0x15;                              // YEAR
    RTCVAL = 0x1210;                            // MONTH-1/DAY-1
    RTCVAL = 0x403;                             // WEEKDAY/HOURS
    RTCVAL = 0x0150;                            // MINUTES/SECONDS
*/

#include <xc.h>
#include "rtcc.h"
#include "user.h"
//#include "lcd.h"
//***************************************************************************************************************************************************************
extern char call, powerFail;                            //call is used to set HMI delay time, based on what function you are in 

char *WeekDay[7]    = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

char *month[13]     = {"","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};


unsigned short bin2bcd(unsigned short binary_value)
{
    unsigned short temp;
    unsigned short retval;

    temp = binary_value;
    retval = 0;

    while(1)
    {
        if(temp >= 10)
        {
            temp -= 10;             // Get the tens digit by doing multiple subtraction                                                  
            retval += 0x10;         // of 10 from the binary value.
        }
        else                        // Get the ones digit by adding the remainder.
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

    temp >>= 1;                       // Shifting upper digit right by 1 is same as multiplying by 8.

    temp &= 0x78;                     // Isolate the bits for the upper digit.


    return(temp + (temp >> 2) + (bcd_value & 0x0f));  // Now return: (Tens * 8) + (Tens * 2) + Ones
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
    RTCVAL = 0x16;                              // YEAR
    RTCVAL = 0x1208;                            // MONTH-1/DAY-1
    RTCVAL = 0x520;                             // WEEKDAY/HOURS
    RTCVAL = 0x2000;                            // MINUTES/SECONDS

//    RTCPWC = 0x0400;                            // PWCPOL disabled; PWCEN disabled; RTCLK LPRC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled;
    RTCPWC = 0x0000;                            // PWCPOL disabled; PWCEN disabled; RTCLK ExtOsc; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled;

//***************************************************************************************************************************************************************
//  Use this Cal for Final design with Blue LED's,  The larger the number, faster it runs (Makes no difference if Positive or Negative numbers, larger is faster)  
//  01111111 = Max Pos adjust( +508 pulses), 00000001 = Min pos adjust(+4 pulses), 00000000 = no adjustment,
//  11111111 = Min Neg adjustment (-4 pulses), 11111110 = -8 pulses ..., 10000000 = Max Neg Adjust (-512 pulses)  
    
    RCFGCALbits.CAL7 = 1;                      // Enable RTCC Calibration
    RCFGCALbits.CAL6 = 0;                      // Enable RTCC Calibration
    RCFGCALbits.CAL5 = 1;                      // Enable RTCC Calibration
    RCFGCALbits.CAL4 = 1;                      // Enable RTCC Calibration
    RCFGCALbits.CAL3 = 0;                      // Enable RTCC Calibration
    RCFGCALbits.CAL2 = 1;                      // Enable RTCC Calibration
    RCFGCALbits.CAL1 = 1;                      // Enable RTCC Calibration  changed to 1 & cal 0 to 0, Dec08, was slow by 3 seconds in 19 days            
    RCFGCALbits.CAL0 = 0;                      // Enable RTCC Calibration changed to 1 Nov19/2016 Clock was slow by 7 seconds in 18 days
    
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
//            LCD_Clear();
        }
        
        timer += 1;
                    
        if(timer > 1000)                      
        {
            timer = 0;
  //          LCD_Clear();
            done = true;                                                        // Exit while loop
        }


//        LCDWriteIntXY(0,0,time.year,2);
  //      LCD_Write_String(month[time.month]);
    //    LCD_Write_Int(time.day,2);
      //  LCDWriteStringXY(0,8,WeekDay[time.weekday]);
//        LCDWriteIntXY(0,12,time.hour,2);
  //      LCD_Write_String(":");
    //    LCD_Write_Int(time.minute,2);
      //  LCD_Write_String(":");
        //LCD_Write_Int(time.second,2);
//        LCDWriteStringXY(2,0," Enter = Next Field ");
  //      LCDWriteStringXY(3,0,"Up/Dn keys to change");
        
        
        
        if(sel == 0)
        {
    //        LCDWriteStringXY(1,0,"^^");                                     // Draw Character Pointer
        }
        
        else if(sel == 1)
        {
      //      LCDWriteStringXY(1,0,"  ^^^");                              // Draw Character Pointer and erase the previous pointer
        }

        else if(sel == 2)
        {
        //    LCDWriteStringXY(1,2,"   ^^");                              // Draw Character Pointer and erase the previous pointer
        }
        
        else if(sel == 3)
        {
          //  LCDWriteStringXY(1,5,"   ^^^");                              // Draw Character Pointer and erase the previous pointer
        }

        else if(sel == 4)
        {
//            LCDWriteStringXY(1,8,"    ^^");                              // Draw Character Pointer and erase the previous pointer
        }
        
        else
        {
  //          LCDWriteStringXY(1,sel*3 - 3,"   ^^");                              // Draw Character Pointer and erase the previous pointer
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
    //                    LCD_Clear();
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
      //                  LCD_Clear();
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
//    LCD_Clear();
    call = 0;                                           // Set call back to 0 before exiting function
    powerFail = 0;                                      //We have just set the time, so, re-set the powerFail Status Bit
    return (1);
}