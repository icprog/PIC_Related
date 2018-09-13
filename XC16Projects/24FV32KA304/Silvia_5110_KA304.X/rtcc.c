#include "rtcc.h"
#include "rtccMenu.h"

//***************************************************************************************************************************************************************

extern int powerFail;
int run = 0;                                    // Run is declared her, so it keeps it's value between calls to OnTimer function


char *WeekDay[7]    = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
char *month[13]     = {"NUL","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

int8_t maxTimes[]       =   {23,55,23,55};

int const startHour[]   =   {40,42,44,46,48,50,52};

int const startMinute[] =   {54,56,58,60,62,64,66};

int const stopHour[]    =   {68,70,72,74,76,78,80};

int const stopMinute[]  =   {82,84,86,88,90,92,94};

signed char choice;

unsigned char testKey = None;

char sel = 0;
    
char done = 0;



//***************************************************************************************************************************************************************

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

    // set Thursday Oct 24 20:59:50 CST 2016
    RCFGCALbits.RTCPTR = 3;                     // start the sequence
    RTCVAL = 0x16;                              // YEAR
    RTCVAL = 0x1024;                            // MONTH-1/DAY-1
    RTCVAL = 0x121;                             // WEEKDAY/HOURS
    RTCVAL = 0x2930;                            // MINUTES/SECONDS

//    RTCPWC = 0x0400;                            // PWCPOL disabled; PWCEN disabled; RTCLK LPRC; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled;
    RTCPWC = 0x0000;                            // PWCPOL disabled; PWCEN disabled; RTCLK ExtOsc; PWCPRE disabled; RTCOUT Alarm Pulse; PWSPRE disabled;
// bit 7 & 6 Slow by 3 seconds in 2 days / cleared 7 & 6, fast by 6 seconds in 12 hours
// Bit 6 is -64*4 counts, so, clearing it made 27 seconds of difference(-3 in 48 hrs, to +6 in 12 hrs, (24 in 2 days)
// so, 3/27*64 =7, -64+7=-57 = 10111001!!    
    RCFGCALbits.CAL7 = 1;                      // Enable RTCC Calibration all zeros but bit 7, too fast by ~1 sec in 24 hrs
    RCFGCALbits.CAL6 = 0;                      // Enable RTCC Calibration
    RCFGCALbits.CAL5 = 1;                      // Enable RTCC Calibration
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
void displayTime(void)
{
    RTCTime time;                                                               // declare the type of the time object
    time = getRTCTime();                                                        // Read current time from RTCC
    LCDWriteIntXY(0,0,time.year,2,0,0);
    LCDWriteCharacter('/');
    LCDWriteString(month[time.month]);
    LCDWriteCharacter('/');
    LCDWriteInt(time.day,2,0,0);
    LCDWriteStringXY(37,0,WeekDay[time.weekday]);
    LCDWriteIntXY(50,0,time.hour,2,0,0);
    LCDWriteCharacter(':');
    LCDWriteInt(time.minute,2,0,0);
    LCDWriteCharacter(':');
    LCDWriteInt(time.second,2,0,0);
}


//***************************************************************************************************************************************************************
void SetTime()
{
    RTCTime time;                                                               // declare the type of the time object

    time = getRTCTime();                                                        // Read current time from RTCC

    char sel = 0, done = 0;
    
    unsigned int timer = 0;                                                     // Used to return to operation if user does not finish setting time!

    while(!done)
    {
        if(timer < 1)
        {
            LCDClear();
            LCDBitmap(&rtccMenu[0], 5, 84);                                           //Draw rtccMenu
        }
        
        timer += 1;
                    
        if(timer > 10000)                      
        {
            timer = 0;
            LCDClear();
            done = 1;                                                           // Exit while loop
        }
        
        displayTime();
        LCDWriteStringXY(4,2,"\"Enter\" = next Field");
        LCDWriteStringXY(4,3,"Up/Dn to change Time");
        
        
        if(sel == 0)
        {
            LCDWriteStringXY(0,1,"^^");                                         // Draw Pointer, to show what we are setting
        }
        
        if(sel == 1)
        {
            LCDWriteStringXY(0,1,"   ^^^");                                      // Draw Pointer, to show what we are setting
        }
        
        if(sel == 2)
        {
            LCDWriteStringXY(12,1,"    ^^");                              // Draw Pointer
        }
        
        if(sel == 3)
        {
            LCDWriteStringXY(25,1,"   ^^^");                              // Draw Pointer
        }
        
        if(sel== 4)
        {
            LCDWriteStringXY(37,1,"   ");
            LCDWriteStringXY(50,1,"^^");
        }
        
        if (sel == 5)
        {
            LCDWriteStringXY(50,1,"   ^^");
        }
        if(sel == 6)
        {
            LCDWriteStringXY(62,1,"   ^^");
        }
        
        char key = readButton();

        switch(key)
        {
            case Up:
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
            
            case Down:
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
                
            case Enter:     // Change our selection
                
                if (sel == 6)
                {
                    sel = 0;
                    LCDClear();
                    done = 1;
                }
                else
                {
                    sel += 1;
                }
            break;
        }

        __builtin_write_RTCWEN();                                   // This should be the same as above

        RCFGCALbits.RTCEN = 0;                                      // Disable RTCC module

    	// Write to RTCC Timer
        RCFGCALbits.RTCPTR = 3;                                     // RTCC Value Register Window Pointer bits
    	RTCVAL = bin2bcd(time.year);                                // Set Year (#0x00YY)
    	RTCVAL = (bin2bcd(time.month) << 8) + bin2bcd(time.day);    // Set Month and Day (#0xMMDD)
        RTCVAL = (bin2bcd(time.weekday) << 8) + bin2bcd(time.hour); // Set Weekday and Hour (#0x0WHH). Weekday from 0 to 6	
        RTCVAL = (bin2bcd(time.minute) << 8) + bin2bcd(time.second);// Set Minute and Second (#0xMMSS)
    	
        RCFGCALbits.RTCEN = 1;                                      // Enable RTCC module
    	
        RCFGCALbits.RTCWREN = 0;                                    // Disable RTCC Timer Access
        
        //setRTCTime(time.year, time.month, time.day, time.weekday, time.hour, time.minute, time.second);
    }
    LCDClear();
    powerFail = 0;                                                              //We have just set the time, so, re-set the powerFail Status Bit
}


//***************************************************************************************************************************************************************

int8_t runTimer(int16_t weekday, int16_t hour, int16_t minute)
{
    if(hour == eepromGetData(startHour[weekday]) && minute == eepromGetData(startMinute[weekday]))
    {
        run = 1;
    }
    
    if(hour == eepromGetData(stopHour[weekday]) && minute == eepromGetData(stopMinute[weekday]))
    {
        run = 0;
    }
    return run;
}

//***************************************************************************************************************************************************************


void writeStartStopTimes(void)
{
    int16_t timer = 0;                                                     // Used to return to operation if user does not finish!
    
    testKey = None;
    
    while(testKey != Enter)
    {
        testKey = readButton();
        
        if(timer > 1500)
        {
            goto Exit;                                                 
        }

        switch(testKey)
        {
             case Down:
             {
                choice -=1;
                            
                if (choice < 0)
                {
                    choice = 0;
                }
            }
            break;
            
            case Up:
            {
                choice += 1;
                            
                if(choice > 6)
                {
                    choice = 6;
                }
            }
            break;
        }

        if(timer < 3)
        {
            LCDClear();
            LCDBitmap(&rtccMenu[0], 5, 84);                                      //Draw rtccMenu
        }

        LCDWriteStringXY(0,1,"Start/Stop for ");
        LCDWriteString(WeekDay[choice]);
        LCDWriteStringXY(0,3,"Up/Dn Keys to choose");
        LCDWriteStringXY(0,4,"Enter Key to Set");

        timer += 1;
    }
    
    LCDClear();
    LCDBitmap(&rtccMenu[0], 5, 84);                                              //Draw rtccMenu
    eepromPutData(startHour[choice], setStartHour(eepromGetData(startHour[choice])));
    eepromPutData(startMinute[choice], setStartMinute(eepromGetData(startMinute[choice])));
    eepromPutData(stopHour[choice], setStopHour(eepromGetData(stopHour[choice])));
    eepromPutData(stopMinute[choice], setStopMinute(eepromGetData(stopMinute[choice])));

    Exit:
    LCDClear();
    timer = 0;
}



//***************************************************************************************************************************************************************
//int8_t setTimes(int8_t b, int8_t maxTimes)
//{
    
//}

int8_t setStartHour(int8_t b)
{
    int16_t timer = 0;                                                         // Used to return to operation if user does not finish!
    
    int8_t result = b;
    
    int8_t testKey = None;

    testKey = readButton();
    
    while(testKey != Enter)
        {
        testKey = readButton();
        
        timer += 1;
        
        __delay_ms(15);             // 15 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            testKey = Enter;
        }
        
        LCDWriteStringXY(0,1,"Start Hour = ");
        LCDWriteIntXY(61,1,result,2,0,0);

        switch(testKey)
        {
            case Down:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case Up:
            {
                result += 1;
                            
                if(result > 23)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
    
    return (result);
}



 //***************************************************************************************************************************************************************

int8_t setStartMinute(int8_t b)
{
    uint16_t timer = 0;                                                         // Used to return to operation if user does not finish!
    
    int8_t result = b;
    
    int8_t testKey = None;

    testKey = readButton();
    
    while(testKey != Enter)
        {
        testKey = readButton();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            testKey = Enter;
        }
        
        LCDWriteStringXY(0,2,"Start Minute = ");
        LCDWriteIntXY(61,2,result,2,0,0);

        
        switch(testKey)
        {
            case Down:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case Up:
            {
                result += 5;
                            
                if(result > 55)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
    
    return (result);
}


//***************************************************************************************************************************************************************


int8_t setStopHour(int8_t b)
{
    uint16_t timer = 0;                                                         // Used to return to operation if user does not finish!
    
    int8_t result = b;
    
    int8_t testKey = None;

    testKey = readButton();
    
    while(testKey != Enter)
        {
        testKey = readButton();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            testKey = Enter;
        }
        
        
        LCDWriteStringXY(0,3,"Stop Hour =");
        LCDWriteIntXY(61,3,result,2,0,0);

//        heartBeat();
        

        switch(testKey)
        {
            case Down:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case Up:
            {
                result += 1;
                            
                if(result > 23)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
        
//    call = 0;
    
    return (result);
}


//***************************************************************************************************************************************************************


int8_t setStopMinute(int8_t b)
{
    uint16_t timer = 0;                                                         // Used to return to operation if user does not finish!
    
    int8_t result = b;
    
    int8_t testKey = None;

    testKey = readButton();
    
    while(testKey != Enter)
        {
        testKey = readButton();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            testKey = Enter;
        }
        
        
        LCDWriteStringXY(0,4,"Stop Minute =");
        LCDWriteIntXY(61,4,result,2,0,0);

//        heartBeat();
        

        switch(testKey)
        {
            case Down:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case Up:
            {
                result += 5;
                            
                if(result > 55)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
    
    return (result);
}
