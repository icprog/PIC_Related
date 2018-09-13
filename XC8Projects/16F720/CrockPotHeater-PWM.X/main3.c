
#include <xc.h>
#include "lcd.h"
#include "system.h"
#include "user.h"
#include <stdio.h>


void main()
{
    unsigned char a;
    
unsigned int f = 1414;
int d = 56;
char s[20];


    Init();
  
    LCD_Init();
    
    while(1)
    {
/*    LCD_Clear();
    LCD_Set_Cursor(0,0);
    LCD_Write_String("LCD Library for  ME!");
    LCD_Set_Cursor(1,0);
    LCD_Write_String("MPLAB XC8  YAAAAAAAA");
    LCD_Set_Cursor(2,0);
    LCD_Write_String("Hello Dickhead!!!!");
    delay_ms(2000);
    LCD_Clear();
    LCD_Set_Cursor(2,0);
    LCD_Write_String("Developed Special By");
    LCD_Set_Cursor(3,0);
    LCD_Write_String("electroSome & Dave Z");
    delay_ms(4000);
    LCD_Clear();
    LCD_Set_Cursor(0,0);
    LCD_Write_String("www.electroSome.com");

    LCD_Clear();
    LCDWriteStringXY(0,0,"LCD Library for  ME!");
    LCDWriteStringXY(1,0,"MPLAB XC8  YAAAAAAAA");
    LCDWriteStringXY(2,0,"Hello Dickhead!!!!");
    delay_ms(2000);
    LCD_Clear();
    LCDWriteStringXY(2,0,"Developed Special By");
    LCDWriteStringXY(3,0,"electroSome & Dave Z");
    delay_ms(4000);
 */
    LCD_Clear();
    

sprintf(s, "Float = %4.0f", f);
LCD_Set_Cursor(1,1);
//LCD_Write_String(s);
sprintf(s, "Integer = %d", d);
LCD_Set_Cursor(2,1);
LCD_Write_String(s);

delay_ms(2000);

    LCD_Clear();
    
    LCDWriteStringXY(0,0,"HELLO TIM!!");

    for(a=0;a<25;a++)

    {
        delay_ms(500);
        LCD_Shift_Left();
    }

    for(a=0;a<20;a++)
    {
        delay_ms(600);
        LCD_Shift_Right();
    }

    }
}