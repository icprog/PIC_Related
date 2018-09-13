#include    "system.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <xc.h> /* XC8 General Include File */
//#include <stdint.h> /* For uint8_t definition */
//#include <stdbool.h> /* For true/false definition */
//#include "lcd.h"
#include "coffee.h"


int main(void)
{
    Init();
    uint16_t count = 0;
    char b = 0; 
    
    
    LCDInit(); //Init the LCD
    
    LCD_Clear();
    LCDBitmap(coffee);
    __delay_ms(3000);
    LCD_Clear();
    drawBox();
    
//    gotoXY(30,1);
    
    LCDWriteStringXY(30,1,"A N D ,");
    __delay_ms(1000);
    gotoXY(8,3);
    
    LCD_Write_String("Layne Sucks COCK!!");
    gotoXY(8,4);
    LCD_Write_String("and Likes it!!");
    
    __delay_ms(2000);
    
    LCD_Clear();
    while(1)
    {
//        count +=1;
//        gotoXY(0,0);
//        LCDString("Count = ");
        LCDWriteIntXY(0,0,count,-1,0,0);
        LCD_Write_String("     ");
    //    __delay_ms(2000);
        count = ADC_Read(0);
        
        b = readButton();
        
        if(b == Enter)
        {
        LCDWriteIntXY(1,1,b,5,0,0);
        }
        else
        {
        LCDWriteIntXY(1,2,readButton(),5,0,0);
        }
    }
    return (1);
}