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
#include <stdbool.h>                  // Includes true/false definition
#include <stdio.h>
#include "system.h"                     // System funct/params, like osc/peripheral config
#include "lcd.h"                        // 4 Bit LCD Library
#include "user.h"                       // User Functions (ADC Conversion))

int16_t main(void)
{
    ConfigureOscillator();

    InitApp();

    __delay_ms(1000);
    
    LCD_Init();
    
    LCD_Clear();
    
    ADCInit();
    
    while(1)
    {
        int D_ADCValue, ADCValue, D_ADCValue2, ADCValue2;
        
        ADCValue = ADCRead(0);
        D_ADCValue = ADCValue;
        
        ADCValue2 = ADCRead(1);
        D_ADCValue2 = ADCValue2;
        
//        D_ADCValue = ADCValue * 0.001220703125;
        
        LCDWriteStringXY(0,0,"1=");
        LCD_Set_Cursor(0,8);
        LCD_Write_Char(D_ADCValue%10 + 48);
        D_ADCValue = D_ADCValue/10;
        LCD_Set_Cursor(0,7);
        LCD_Write_Char(D_ADCValue%10 + 48);
        D_ADCValue = D_ADCValue/10;
        LCD_Set_Cursor(0,6);
        LCD_Write_Char(D_ADCValue%10 + 48);
        D_ADCValue = D_ADCValue/10;
        LCD_Set_Cursor(0,5);
        LCD_Write_Char(D_ADCValue%10 + 48);

        LCDWriteStringXY(1,0,"2=");
        LCD_Set_Cursor(1,8);
        LCD_Write_Char(D_ADCValue2%10 + 48);
        D_ADCValue2 = D_ADCValue2/10;
        LCD_Set_Cursor(1,7);
        LCD_Write_Char(D_ADCValue2%10 + 48);
        D_ADCValue2 = D_ADCValue2/10;
        LCD_Set_Cursor(1,6);
        LCD_Write_Char(D_ADCValue2%10 + 48);
        D_ADCValue2 = D_ADCValue2/10;
        LCD_Set_Cursor(1,5);
        LCD_Write_Char(D_ADCValue2%10 + 48);
    }
    return(0);
}
