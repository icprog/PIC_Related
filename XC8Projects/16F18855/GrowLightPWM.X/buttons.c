#include "buttons.h"
#include "lcd.h"

#define downButton  RA3
#define upButton    RA4

uint8_t downCount = 0, upCount = 0, toggleCount = 0, b = 0;

void readButtons(void)
{
    while(RA3 == 0 && RA4 == 0)
    {
        downCount = 0;
        upCount = 0;
        toggleCount+=1;
        if(toggleCount >=6)
        {
            b+=1;
            if(b>4)
            {
                b=0;
            }
//            LCDWriteStringXY(0,0,"Setpoint?");
  //          LCDWriteIntXY(1,0,setpoint,3,0,0);
            LCD_Write_Character(0);
            LCD_Write_Character('C');
            LCD_Write_Character(' ');
            __delay_ms(1500);
            toggleCount = 0;
            LCD_Clear();
        }
    }
    
    if(RA3 == 0)
    {
        downCount +=1;
        if(downCount>5)
        {
            downCount = 5;
        }
    }
    else 
    {
        downCount = 0;
    }
    
    if(RA4 == 0)
    {
        upCount +=1;
        if(upCount>5)
        {
            upCount = 5;
        }
    }
    else 
    {
        upCount = 0;
    }
}