/* 
 * File:   main.c
 * Author: DAVE
 *
 * Created on April 29, 2015, 10:58 PM
 */
/* 
 * File:   bulb_pwm.c
 * Author: Oli Glaser
 * License: MIT license
 * Created on 13 August 2013
 */

#include <xc.h>
#include "system.h"
#include "user.h"
#include "interupts.h"
// #include "hd44780.h"
#include "lcd.h"
#include <stdio.h>

unsigned char OutCurrent = 69;

void main()
{
//    unsigned char a;
    char s[20];

    Init(); 

    delay_ms(1250);
    
    LCD_Init();
    
    LCD_Clear();

    PORTCbits.RC0 = 1;
 
/*    delay_ms(750);                                                              //Startup delay to allow LCD to Power-Up

    LCDInit(LS_NONE);                                                           // Initialize the LCD Module
    delay_ms(500);

    LCDClear();

    LCDReset(LS_NONE);
    delay_us(100);
    LCDReset(LS_NONE);
    delay_us(100);
    LCDReset(LS_NONE);
    delay_us(100);
*/    
    while(1)                                                                    // Infinite loop
    {
        extern unsigned char OutCurrent;
        unsigned char setpoint, ReadCurrent;
        unsigned char x;
        
        
        for(x = 0; x < 255 ; x++)
        {
            ReadCurrent = (ReadCurrent + ADCRead(3))/2;
        }
        
                
        for(x = 0 ; x < 255 ; x++)
        {
            setpoint = (setpoint + ADCRead(2))/2;
        }
        
        delay_ms(1000);
        
        if(setpoint >= ReadCurrent + 2)
        {
            OutCurrent++;
            
            if(OutCurrent >= 254)
            {
                OutCurrent = 254;
            }
        }
        
        if(setpoint <= ReadCurrent - 2)
        {
            OutCurrent--;
            
            if(OutCurrent <= 1)
            {
                OutCurrent = 1;
            }
        }
        
    LCD_Clear();
    

sprintf(s, "CCPR1L      = %d", CCPR1L );
LCD_Set_Cursor(0,0);
LCD_Write_String(s);

sprintf(s, "OutCurrent  = %d", OutCurrent );
LCD_Set_Cursor(1,0);
LCD_Write_String(s);

sprintf(s, "Setpoint    = %d", setpoint );
LCDWriteStringXY(2,0,s);

sprintf(s, "ReadCurrent = %d", ReadCurrent );
LCDWriteStringXY(3,0,s);

// delay_ms(1000);

                
//        LCDWriteIntXY(0,0,CCPR1L,3);
  //      LCDWriteIntXY(0,1,OutCurrent,3);
    //    LCDWriteIntXY(4,0,setpoint,3);
      //  LCDWriteIntXY(4,1,ReadCurrent,3);
    }
}
