#include "system.h"
#include "rtccMenu.h"


static void RTCC_Lock(void);
static bool rtccTimeInitialized;
static bool RTCCTimeInitialized(void);
static uint8_t ConvertHexToBCD(uint8_t hexvalue);
static uint8_t ConvertBCDToHex(uint8_t bcdvalue);

struct tm currentTime;

extern int powerFail;

extern uint8_t call;

extern uint16_t timeFU;

char *WeekDay[7]    = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

char *month[13]     = {"NUL","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};


void RTCC_Initialize(void)
{
   RTCCON1Lbits.RTCEN = 0;
   
   __builtin_write_RTCC_WRLOCK();
   
   if(!RTCCTimeInitialized())   // set 2017-09-22 11-09-15
   {
       DATEH = 0x1709;          // Year/Month
       DATEL = 0x2400;          // Date/Wday
       TIMEH = 0x0239;          // hours/minutes
       TIMEL = 0x5500;          // seconds
   }

// A crystal oscillator that is connected to the RTCC may be calibrated to provide an accurate 1 second clock in
// two  ways. First, coarse frequency adjustment is  per-formed by adjusting the value written to the DIV<15:0>
// bits.  Secondly,  a  5-bit  value  can  be  written  to  the FDIV<4:0> control bits to perform a fine clock division.
// The DIVx and FDIVx values can be concatenated and considered as a 21-bit prescaler value. If the oscillator
// source is slightly faster than ideal, the FDIV<4:0> value can be increased to make a small decrease in the RTC
// frequency.  The  value  of  DIV<15:0>  should  be increased  to  make  larger  decreases  in  the  RTC
// frequency. If the oscillator source is slower than ideal, FDIV<4:0>  may  be  decreased  for  small  calibration
// changes and DIV<15:0> may need to be decreased to make larger calibration changes. 
   
   RTCCON2L = 0xF800;           // PWCPS 1:1; PS 1:1; CLKSEL SOSC; FDIV 0; Bits 15 to 11 are for Fine Clock speed adjustment (Pg 316))
   
   RTCCON2H = 0x3FFF;           // DIV 16383; Register used for Coarse speed adjustment of RTCC (Pg 317)
   
   RTCCON3L = 0x0000;           // PWCSTAB 0; PWCSAMP 0; Used to wake up (and Power down) an external device & sample it's value
   
   RTCCON1L = 0x8000;           // RTCEN enabled; OUTSEL Alarm Event; PWCPOE disabled; PWCEN disabled; WRLOCK disabled; PWCPOL disabled; TSAEN disabled; RTCOE disabled; 
   
   RTCC_Lock();
}

static void RTCC_Lock(void)
{
    asm volatile("DISI #6");                    // Disable Interrupts for 6 instruction cycles
    asm volatile("MOV #NVMKEY, W1");            //
    asm volatile("MOV #0x55, W2");              // First Unlock Code (55))
    asm volatile("MOV W2, [W1]");               // Write Unlock sequence (to working reg?)
    asm volatile("MOV #0xAA, W3");              // Second Unlock Code (AA)
    asm volatile("MOV W3, [W1]");
    asm volatile("BSET RTCCON1L, #11");         // Clear the WriteLock bit
}

bool RTCC_TimeGet(struct tm *currentTime)
{
    uint16_t register_value;
    
    if(RTCSTATLbits.SYNC)
    {
        return 0;
    }

 
    __builtin_write_RTCC_WRLOCK();
 
    register_value = DATEH;
    currentTime->tm_year = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_mon = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = DATEL;
    currentTime->tm_mday = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_wday = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TIMEH;
    currentTime->tm_hour = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_min = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TIMEL;
    currentTime->tm_sec = ConvertBCDToHex((register_value & 0xFF00) >> 8);
   
    RTCC_Lock();

    return 1;
}


void RTCC_TimeSet(struct tm *currentTime)
{
    call = 1;
    
    uint8_t sel = 0, done = 0;
    
    uint16_t timer = 0;                                                     // Used to return to operation if user does not finish setting time!

    while(!done)
    {
        displayTime();

        __builtin_write_RTCC_WRLOCK();

        RTCCON1Lbits.RTCEN = 0;
        
        if(timer < 1)
        {
            cls();
            loadimg(&rtccMenu[0], 1024,0);                                           //Draw rtccMenu
        }
        
        timer += 1;
                    
        if(timer > 10000)                      
        {
            timer = 0;
            cls();
            done = 1;                                                           // Exit while loop
        }
        
        LCDWriteStringXY(3,3,"\"Enter\" for n");
        LCDWriteStringXY(3,16,"ext Field");
        LCDWriteStringXY(4,3,"Up/Dn keys to");
        LCDWriteStringXY(4,17,"change Time.")
        
        
        if(sel == 0)
        {
            LCDWriteStringXY(2,3,"^^");                                         // Draw Pointer, to show what we are setting
        }
        
        if(sel == 1)
        {
            LCDWriteStringXY(2,3,"   ^^^");                                      // Draw Pointer, to show what we are setting
        }
        
        if(sel == 2)
        {
            LCDWriteStringXY(2,6,"    ^^");                              // Draw Pointer
        }
        
        if(sel == 3)
        {
            LCDWriteStringXY(2,10,"   ^^^");                              // Draw Pointer
        }
        
        if(sel== 4)
        {
            LCDWriteStringXY(2,13,"   ");
            LCDWriteStringXY(2,17,"^^");
        }
        
        if (sel == 5)
        {
            LCDWriteStringXY(2,17,"   ^^");
        }
        if(sel == 6)
        {
            LCDWriteStringXY(2,20,"   ^^");
        }
        
        char key = menuRead();

        switch(key)
        {
            case KEY_2:
                if(sel==0)
                {
                    if (currentTime->tm_year == 99)
                    {
                        currentTime->tm_year = 00;
                    }
                    else
                    {
                        currentTime->tm_year += 1;
                    }
                }
                
                if(sel==1)
                {
                    if (currentTime->tm_mon == 12)
                    {
                        currentTime->tm_mon = 1;
                    }
                    else
                    {
                        currentTime->tm_mon += 1;
                    }
                }
                
                if(sel==2)
                {
                    if (currentTime->tm_mday == 31)
                    {
                        currentTime->tm_mday = 1;
                    }
                    else
                    {
                        currentTime->tm_mday +=1;
                    }
                }

                if(sel==3)
                {
                    if (currentTime->tm_wday == 6)
                    {
                        currentTime->tm_wday = 0;
                    }
                    else
                    {
                        currentTime->tm_wday += 1;
                    }
                }

                if(sel==4)
                {
                    if (currentTime->tm_hour == 23)
                    {
                        currentTime->tm_hour = 0;
                    }
                    else
                    {
                        currentTime->tm_hour += 1;
                    }
                }
                
                if(sel == 5)    
                {
                    if(currentTime->tm_min == 59)
                    {
                        currentTime->tm_min = 0;
                    }
                    else
                    {
                        currentTime->tm_min += 1;
                    }
                }
                
                if (sel == 6)
                {
                    if (currentTime->tm_sec == 59)
                    {
                        currentTime->tm_sec = 0;
                    }
                    else
                    {
                        currentTime->tm_sec += 1;
                    }
                }
            break;
            
            case KEY_1:
                if(sel == 0)
                {
                    if (currentTime->tm_year == 0)
                    {
                        currentTime->tm_year = 99;
                    }
                    else
                    {
                        currentTime->tm_year -= 1;
                    }
                }
                
                if(sel == 1)
                {
                    if (currentTime->tm_mon == 1)
                    {
                        currentTime->tm_mon = 12;
                    }
                    else
                    {
                        currentTime->tm_mon -= 1;
                    }
                }
                
                if(sel == 2)
                {
                    if (currentTime->tm_mday == 1)
                    {
                        currentTime->tm_mday = 31;
                    }
                    else
                    {
                        currentTime->tm_mday -= 1;
                    }
                }

                if(sel == 3)
                {
                    if (currentTime->tm_wday == 0)
                    {
                        currentTime->tm_wday = 6;
                    }
                    else
                    {
                        currentTime->tm_wday -= 1;
                    }
                }

                if(sel == 4)
                {
                    if (currentTime->tm_hour == 0)
                    {
                        currentTime->tm_hour = 23;
                    }
                    else
                    {
                        currentTime->tm_hour -= 1;
                    }
                }
                
                if(sel == 5)    
                {
                    if(currentTime->tm_min == 0)
                    {
                        currentTime->tm_min = 59;
                    }
                    else
                    {
                        currentTime->tm_min -= 1;
                    }
                }
                
                if (sel == 6)
                {
                    if (currentTime->tm_sec == 0)
                    {
                        currentTime->tm_sec = 59;
                    }
                    else
                    {
                        currentTime->tm_sec -= 1;
                    }
                }
            break;
                
            case KEY_3:     // Change our selection
                
                if (sel == 6)
                {
                    sel = 0;
                    cls();
                    done = 1;
                }
                else
                {
                    sel += 1;
                }
            break;
        }
        
   

        // set RTCC current time
        DATEH = (ConvertHexToBCD(currentTime->tm_year) << 8) | ConvertHexToBCD(currentTime->tm_mon) ;  // YEAR/MONTH-1
        DATEL = (ConvertHexToBCD(currentTime->tm_mday) << 8) | ConvertHexToBCD(currentTime->tm_wday) ;  // /DAY-1/WEEKDAY
        TIMEH = (ConvertHexToBCD(currentTime->tm_hour) << 8)  | ConvertHexToBCD(currentTime->tm_min); // /HOURS/MINUTES
        TIMEL = (ConvertHexToBCD(currentTime->tm_sec) << 8) ;   // SECOND
           
        // Enable RTCC, clear RTCWREN         
        RTCCON1Lbits.RTCEN = 1;  
        RTCC_Lock();
    }
    cls();
    call = 0;
    powerFail = 0; 
  
}


void displayTime(void)
{
    int8_t test = 0;
    
    test = RTCC_TimeGet(&currentTime);              // Read current time from RTCC
    
    if(test == 0)
    {
        timeFU+=1;
    }                                             
    LCDWriteIntXY(1,3,currentTime.tm_year,2,0);
    LCDWriteChar('/');
    LCDWriteString(month[currentTime.tm_mon]);
    LCDWriteChar('/');
    LCDWriteInt(currentTime.tm_mday,2,0);
    LCDWriteStringXY(1,13,WeekDay[currentTime.tm_wday]);
    LCDWriteIntXY(1,17,currentTime.tm_hour,2,0);
    LCDWriteChar(':');
    LCDWriteInt(currentTime.tm_min,2,0);
    LCDWriteChar(':');
    LCDWriteInt(currentTime.tm_sec,2,0);
}

static uint8_t ConvertHexToBCD(uint8_t hexvalue)
{
    uint8_t bcdvalue;
    bcdvalue = (hexvalue / 10) << 4;
    bcdvalue = bcdvalue | (hexvalue % 10);
    return (bcdvalue);
}

static uint8_t ConvertBCDToHex(uint8_t bcdvalue)
{
    uint8_t hexvalue;
    hexvalue = (((bcdvalue & 0xF0) >> 4)* 10) + (bcdvalue & 0x0F);
    return hexvalue;
}

void RTCC_TimeReset(bool reset)
{
    rtccTimeInitialized = reset;
}

static bool RTCCTimeInitialized(void)
{
    return(rtccTimeInitialized);
}

/*
bool RTCC_BCDTimeGet(bcdTime_t *currentTime)
{
    uint16_t register_value;
    if(RTCSTATLbits.SYNC){
        return 0;
    }


    __builtin_write_RTCC_WRLOCK();
   
    register_value = DATEH;
    currentTime->tm_year = (register_value & 0xFF00) >> 8;
    currentTime->tm_mon = register_value & 0x00FF;
    
    register_value = DATEL;
    currentTime->tm_mday = (register_value & 0xFF00) >> 8;
    currentTime->tm_wday = register_value & 0x00FF;
    
    register_value = TIMEH;
    currentTime->tm_hour = (register_value & 0xFF00) >> 8;
    currentTime->tm_min = register_value & 0x00FF;
   
    register_value = TIMEL;
    currentTime->tm_sec = (register_value & 0xFF00) >> 8;
   
    RTCC_Lock();

    return 1;
}

void RTCC_BCDTimeSet(bcdTime_t *initialTime)
{

   __builtin_write_RTCC_WRLOCK();

   RTCCON1Lbits.RTCEN = 0;
   

   // set RTCC initial time
   DATEH = (initialTime->tm_year << 8) | (initialTime->tm_mon) ;  // YEAR/MONTH-1
   DATEL = (initialTime->tm_mday << 8) | (initialTime->tm_wday) ;  // /DAY-1/WEEKDAY
   TIMEH = (initialTime->tm_hour << 8) | (initialTime->tm_min); // /HOURS/MINUTES
   TIMEL = (initialTime->tm_sec << 8);   // SECONDS   
           
   // Enable RTCC, clear RTCWREN         
   RTCCON1Lbits.RTCEN = 1;  
   RTCC_Lock();

}
*/
/**
 This function implements RTCC_TimeReset.This function is used to
 used by application to reset the RTCC value and reinitialize RTCC value.
*/


/*
void RTCC_TimestampAEventManualSet(void)
{
    RTCSTATLbits.TSAEVT = 1;
}

bool RTCC_TimestampADataGet(struct tm *currentTime)
{
    uint16_t register_value;
    if(!RTCSTATLbits.TSAEVT){
        return false;
    }
  
    register_value = TSADATEH;
    currentTime->tm_year = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_mon = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TSADATEL;
    currentTime->tm_mday = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_wday = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TSATIMEH;
    currentTime->tm_hour = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_min = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TSATIMEL;
    currentTime->tm_sec = ConvertBCDToHex((register_value & 0xFF00) >> 8);
   
    RTCSTATLbits.TSAEVT = 0;

    return true;
}



bool RTCC_TimestampA_BCDDataGet(bcdTime_t *currentTime)
{
    uint16_t register_value;
    if(!RTCSTATLbits.TSAEVT){
        return false;
    }
  
    register_value = TSADATEH;
    currentTime->tm_year = (register_value & 0xFF00) >> 8;
    currentTime->tm_mon = (register_value & 0x00FF);
    
    register_value = TSADATEL;
    currentTime->tm_mday = (register_value & 0xFF00) >> 8;
    currentTime->tm_wday = (register_value & 0x00FF);
    
    register_value = TSATIMEH;
    currentTime->tm_hour = (register_value & 0xFF00) >> 8;
    currentTime->tm_min = (register_value & 0x00FF);
    
    register_value = TSATIMEL;
    currentTime->tm_sec = (register_value & 0xFF00) >> 8;
   
    RTCSTATLbits.TSAEVT = 0;

    return true;
}
*/


/* Function:
    bool RTCC_Task(void)

  Summary:
    Status function which returns the RTCC interrupt flag status

  Description:
    This is the status function for the RTCC peripheral. 
*/

/*
bool RTCC_Task(void)
{
    bool status;
    status = IFS3bits.RTCIF;
    if( IFS3bits.RTCIF)
    {
       IFS3bits.RTCIF = 0;
    }
    return status;
}
  */  