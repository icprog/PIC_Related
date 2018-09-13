#define _XTAL_FREQ 8000000

#include <xc.h>
#include "system.h"
#include "configuration_bits.c"
#include "hd44780.h"


int a;
char x = 0;
/*
void interrupt echo()
{
  if(RABIF == 1)                 //Makes sure that it is PORTB On-Change Interrupt
  {
    RABIE = 0;                   //Disable On-Change Interrupt
    if(RB4 == 1)                  //If ECHO is HIGH
      TMR1ON = 1;                    //Start Timer
    if(RB4 == 0)                  //If ECHO is LOW
    {
      TMR1ON = 0;                    //Stop Timer
      a = (TMR1L | (TMR1H<<8))/5882/100;  //Calculate Distance
    }
  }
  RABIF = 0;                     //Clear PORTB On-Change Interrupt flag
  RABIE = 1;                     //Enable PORTB On-Change Interrupt
}
*/

void main()
{
    ConfigureOscillator();
    
    Init();

    delay_ms(1500);
    LCDInit(0x00);

    LCDWriteStringXY(0,0,"Testing 30%0");
    delay_ms(3000);
    LCDClear();

    T1CON = 0x10;                   //Initialize Timer Module

    while(1)
    {
        TMR1H = 0;                   //Sets the Initial Value of Timer
        TMR1L = 0;                   //Sets the Initial Value of Timer

        RB5 = 1;                     //TRIGGER HIGH
        delay_us(10);                //10uS Delay
        RB5 = 0;                     //TRIGGER LOW

        delay_ms(100);               //Waiting for ECHO
   //     a = a + 1;                   //Error Correction Constant

        if(a>=0 && a<=400)           //Check whether the result is valid or not
        {
//            LCDClear();
            LCDWriteIntXY(0,0,TMR1L,8);
            LCDWriteIntXY(0,1,TMR1H,8);
//            LCDWriteStringXY(0,1,"Distance =");
            LCDWriteIntXY(11,1,a,3);
        }
/*            Lcd_Set_Cursor(1,14);
            Lcd_Write_Char(a%10 + 48);

            a = a/10;
            Lcd_Set_Cursor(1,13);
            Lcd_Write_Char(a%10 + 48);

            a = a/10;
            Lcd_Set_Cursor(1,12);
            Lcd_Write_Char(a%10 + 48);

            Lcd_Set_Cursor(1,15);
            Lcd_Write_String("cm");
        }
*/
        else
        {
            LCDClear();
            LCDWriteStringXY(1,1,"Out of Range");
        }
        
        delay_ms(400);
        ++x;
        
        if(x > 20)
        {
            x = 0;
            LCDReset(0x00);
        }
    }
}