/*
 * File:   main.c
 * Author: DAVE
 *
 * Created on November 25, 2015, 12:17 PM
 */


#include "xc.h"
#include "mcc.h"
#include "lcd.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "interrupt_manager.h"
#include "rtcc.h"
#include "pin_manager.h"
#include "system.h"

int main(void)
{
    char s [20];
    char n;
    n = 0;

    struct tm  currentTime;

    RTCC_Initialize();
        
    
    __delay_ms(1000);
    
    LCD_Init();
    
    LCD_Clear();
    

//    while(!RTCC_TimeGet(&currentTime))
    while (1)
        {
        
        tm = RTCC_TimeGet();
//        if (n > 3)
  //      {
    //    setRTCTime(0x0011, 0x0001, 0x0010, 0x0011, 0x0001, 0x0011, 0x0011);
      //  n+=1;
        //}
        

        
/*    RTCTime time; // declare the type of the time object
    time = getRTCTime(); // get the time
 *  
 *         
        
    unsigned char d_year;
    unsigned char d_month;
    unsigned char d_day;
    unsigned char d_weekday; // Monday is 0, Sunday is 6
    unsigned char d_hour;
    unsigned char d_minute;
    unsigned char d_second;

    d_year = time.year;
    d_month = time.month;
    d_day = time.day;
    d_weekday = time.weekday;
    d_hour = time.hour;
    d_minute = time.minute;
    d_second = time.second;
*/    
    _RC8 = 1;
    __delay_ms(500);
    _RC8 = 0;
    __delay_ms(400);
    
//      LCD_Set_Cursor(0,0); 
        sprintf(s, "Seconds=%f", tm.tm_sec);
        LCD_Set_Cursor(0,0);
        LCD_Write_String(s);
        
        sprintf(s, "%d,%d", tm.tm_wday,tm.tm_min);
        LCD_Set_Cursor(0,11);
        LCD_Write_String(s);
        

        LCDWriteStringXY(1,0,"second=");
        LCD_Set_Cursor(1,8);
        LCD_Write_Char(tm.tm_sec%10 + 48);
        tm.tm_sec = tm.tm_sec/10;
        LCD_Set_Cursor(1,7);
        LCD_Write_Char(tm.tm_sec%10 + 48);
        
        
        
//        LCD_Set_Cursor(2,0); 
        sprintf(s, "Minutes = %d", tm.tm_min);
        LCD_Set_Cursor(2,0);
        LCD_Write_String(s);
        
        sprintf(s, "Day = %d", tm.tm_mday);
        LCD_Set_Cursor(3,0);
        LCD_Write_String(s);
        
        sprintf(s, "Year = %d", tm.tm_year);
        LCD_Set_Cursor(3,10);
        LCD_Write_String(s);
            // Do something
  
  
        }

    
    return 0;
}
