#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include <stdint.h>                     // Includes uint16_t definition
#include <stdbool.h>                    // Includes true/false definition
#include <stdio.h>
#include "system.h"                     // System funct/params, like osc/peripheral config
#include "lcd.h"                        // 4 Bit LCD Library
#include "user.h"                       // User Functions (ADC Conversion))
#include "rtcc.h"
#include "AnalogKeyInput.h"

#define TRUE        1
#define FALSE       0
#define KEY_RIGHT   1

// uint8_t hr, min, sec;
uint8_t yr, mnth, dy, dw, hr, min, sec;


int16_t main(void)
{
    
    char n = 0;
   
//    unsigned char yr, mnth, dy, dw, hr, min, sec;

//    unsigned char yr=15,mnth=11,dy=28,dw=6,hr=02,min=02,sec=50;

//    unsigned char n = 0;
    
    ConfigureOscillator();

    InitApp();
    
    ADCInit();

    __delay_ms(1000);
    
    LCD_Init();
    
    LCD_Clear();
    
    RTCC_Initialize();
    
    
    while(1)
    {
    //      unsigned char yr, mnth, dy, dw, hr, min, sec;

 //   unsigned char yr=15,mnth=11,dy=28,dw=6,hr=02,min=02,sec=50;

        
    RTCTime time; // declare the type of the time object
    time = getRTCTime(); // get the time

/*    if (n == 10)
    {
        if(hr == 23)
        {
            min = 59;
            sec = 50;
            n = 11;
        }
        
        else
        {
            n = 0;
            hr+=1;
        }
               
        setRTCTime(yr, mnth, dy, dw, hr, min, sec);
//        n = 0;
    }

    n+=1;
    
    if (n == 5)
    {
        yr = time.year;
        mnth = time.month;
        dy = time.day;
        dw = time.weekday;
        hr = time.hour;
        min = time.minute;
        sec = time.second;
 //       n = 0;
 //       LCD_Clear();
    }
*/
    _RC8 = 1;
    __delay_ms(500);
    _RC8 = 0;
    __delay_ms(500);
    
    hr = time.hour;
    min = time.minute;
    sec = time.second;
    
    n+=1;
    
        sprintf(s,"20%d%d/%d%d/%d%d %d%d:%d%d:%d%d", time.year/10%10,(time.year%10),time.month/10%10, time.month%10, time.day/10%10, time.day%10, time.hour/10%10, time.hour%10, time.minute/10%10, time.minute%10, time.second/10%10, time.second%10);
        LCD_Set_Cursor(3,0);
        LCD_Write_String(s);
        
        if (n > 9)
        {
            n = 0;
            SetTime();
//    		break;
        }

       
//        sprintf(s,"20%d%d/%d%d/%d%d %d%d:%d%d:%d%d", yr/10%10, yr%10, mnth/10%10, mnth%10, dy/10%10, dy%10, hr/10%10, hr%10, min/10%10, min%10, sec/10%10, sec%10);
  //      LCD_Set_Cursor(0,0);
    //    LCD_Write_String(s);
        
    }
    return(0);
}

bool SetTime(void)
{
    if(hr==0 && min==0 && sec==0)
    {
        hr=12;    	//If Hour is 0 make it 12, as 00:00:00 invalid time
    }
            
    sec+=1;
    hr+=2;
            
    uint8_t sel=0;
	
    bool done=FALSE;
            
    while(!done)
    {
        LCD_Clear();

        LCDWriteStringXY(0,0,"00:00:00    <OK>");
                
        sprintf(s,"%d%d:%d%d:%d%d", hr/10%10, hr%10, min/10%10, min%10, sec/10%10, sec%10);
        LCD_Set_Cursor(0,0);
        LCD_Write_String(s);
        
        LCDWriteStringXY(sel*2,0,"^^");     // Draw Pointer
        
        uint8_t key = KEY_RIGHT;
        
        switch(key)
        {
            case KEY_RIGHT:
                if(sel==0)      //hr selected
                {
                    if (hr == 24)
                    {
                        hr = 1;
                        sel+=1;                        
                    }
                    else
                    {
                        hr+=1;
                        sel+=1;
                    }
                }
                if(sel == 1)    //min selected    
                {
                    if(min == 59)
                    {
                        min = 0;
                        sel+=1;
                    }
                    else
                    {
                        min+=1;
                        sel+=1;
                    }
                }
                if (sel == 2)   //sec selected
                {
                    if (sec == 59)
                    {
                        sec = 0;
                        sel+=1;
                    }
                    else
                    {
                        sec += 1;
                        sel+=1;
                    }
                }
                if (sel == 3)   // we are done (OK selected))
                {
                    done = TRUE;
                }
                break;
        }
                
        

    }
//                LCDWriteIntXY(0,0,hr,2);
  //              LCDWriteIntXY(3,0,min,2);
    //            LCDWriteIntXY(6,0,sec,2);
    return (1);
}