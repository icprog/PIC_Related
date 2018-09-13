/* 
 * File:   main.c
 * Author: DAVE
 *
 * Created on May 16, 2015, 1:25 AM
 */
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

//#define average 2
//#define Heat    _RC8
#define TRUE	1
#define FALSE	0



int16_t main(void)
{
    char s [20];

    unsigned char n = 1;
    
    ConfigureOscillator();

    InitApp();
    
    ADCInit();

    __delay_ms(1000);
    
    LCD_Init();
    
    LCD_Clear();


    while(1)
    {
        _RC8 = 1;
        __delay_ms(50);
        _RC8 = 0;
        __delay_ms(40);
    
/*
        sprintf(s, "20%d/%d/%d %d:%d:%d", time.year, time.month, time.day ,time.hour, time.minute, time.second);
        LCD_Set_Cursor(3,0);
        LCD_Write_String(s);
*/
    
        sprintf(s,"Hello World, %d",n );
        LCD_Set_Cursor(3,0);
        LCD_Write_String(s);

        sprintf(s, "n = %d", n);
        LCD_Set_Cursor(0,0);
        LCD_Write_String(s);

        sprintf(s,"Hello World1, %d",n );
        LCD_Set_Cursor(2,0);
        LCD_Write_String(s);

        sprintf(s, "n2 = %d", n);
        LCD_Set_Cursor(1,0);
        LCD_Write_String(s);


    }
    return(0);
}
