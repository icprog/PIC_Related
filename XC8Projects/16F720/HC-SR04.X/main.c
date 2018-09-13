// a 330uf Cap across the power rails smooths the reading substantially

#include <xc.h>
#include "system.h"
#include "interupts.h"
#include "lcd.h"

#define SampleAverage   5

unsigned int Value, OldValue;
unsigned char b = 0;

void main()
{
    Init();
    
    delay_ms(1250);

    LCD_Init();
    LCD_Clear();

    T1CON = 0x10;                                       //Initialize Timer Module

    while(1)
    {
        for (b = 0; b < SampleAverage; b++)
        {
            TMR1H = 0;                                  //Sets the Initial Value of Timer
            TMR1L = 0;                                  //Sets the Initial Value of Timer

            RB5 = 1;                                    //TRIGGER HIGH
    
            delay_us(10);                               //10uS Delay
            RB5 = 0;                                    //TRIGGER LOW 

            delay_ms(100);                              //Waiting for ECHO
            Value = Value + 1;                                  //Error Correction Constant
            
            if(Value >= 3 && Value <= 400)                          //Check whether the result is valid or not
            {
                Value = (Value + OldValue) / 2;
                OldValue = Value;
                LCDWriteStringXY(1,0,"                ");   // Clear Line without clearing screen      
            }
            
            else
            {
                LCD_Clear();
                LCD_Set_Cursor(1,1);
                LCD_Write_String("Out of Range");
                delay_ms(1000);
            }
        }
 

        LCD_Set_Cursor(0,0);
        LCD_Write_String("Distance:");

        LCD_Set_Cursor(0,12);
        LCD_Write_Char(Value%10 + 48);

        Value = Value/10;
        LCD_Set_Cursor(0,11);
        LCD_Write_Char(Value%10 + 48);

        Value = Value/10;
        LCD_Set_Cursor(0,10);
        LCD_Write_Char(Value%10 + 48);

        LCD_Set_Cursor(0,14);
        LCD_Write_String("cm");
    }
}