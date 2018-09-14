#include "buttons.h"
#include "lcd.h"

#define downButton  RA3
#define upButton    RA4

uint8_t downCount = 0, upCount = 0, oldSetpoint, toggleCount = 0, x = 0;
extern uint8_t setpoint;
extern uint8_t presets[];


void tempSetpoint(void)
{
    uint8_t counter = 0;
    
    oldSetpoint = setpoint;
    
    while(downCount >= 5)
    {
        counter+=1;
        if(counter<=1)
        {
            LCD_Clear();
        }
        setpoint-=1;
        LCDWriteStringXY(0,0,"Setpoint?");
        LCDWriteIntXY(1,0,setpoint,3,0,0);
        LCD_Write_Char(0);
        LCD_Write_Char('C');
        LCD_Write_Char(' ');
        __delay_ms(350);
        readButtons();
    }
    
    while(upCount >= 5)
    {
        counter+=1;
        if(counter<=1)
        {
            LCD_Clear();
        }
        setpoint+=1;
        LCDWriteStringXY(0,0,"Setpoint?");
        LCDWriteIntXY(1,0,setpoint,3,0,0);
        LCD_Write_Char(0);
        LCD_Write_Char('C');
        LCD_Write_Char(' ');
        __delay_ms(350);
        readButtons();
    }
    
    counter = 0;
    
    if(oldSetpoint!=setpoint)
    {
        __delay_ms(2000);
        LCD_Clear();
    }
}
    

void readButtons(void)
{
    while(RA3 == 0 && RA4 == 0)
    {
        downCount = 0;
        upCount = 0;
        toggleCount+=1;
        if(toggleCount >=6)
        {
            x+=1;
            if(x>4)
            {
                x=0;
            }
            setpoint = presets[x];
            LCDWriteStringXY(0,0,"Setpoint?");
            LCDWriteIntXY(1,0,setpoint,3,0,0);
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCD_Write_Char(' ');
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