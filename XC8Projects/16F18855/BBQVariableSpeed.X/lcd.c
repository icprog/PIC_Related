#include "lcd.h"
//#include <stdint.h>

// ***************************************************************************************************************************************************************
uint8_t __cgram[] =                                     // YOU CAN USE LCD_Write_Char(48 + Ascii code) for any char in the Display Rom!!!
{
    0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00,     // Char0 Degree symbol, Use LCD_Write_Char(0); to display this char
//	0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00, 0x00,     // Char2 Open Heart
//	0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00, 0x00,     // Char3 Solid Heart
    0x08, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x08, 0x00      // Char1 Right Arrow  
/*  	
    0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00,     // Degree symbol, char num #0 Use LCD_Write_Char(0); to display this char
    0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00,     // Battery Empty, char num #1 Use LCD_Write_Char(1); to display this char      
    0x0E, 0x1B, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x00,     // Battery 1/4,   char num #2 Use LCD_Write_Char(2); to display this char      
    0x0E, 0x1B, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x00,     // Battery 1/2,   char num #3 Use LCD_Write_Char(3); to display this char
    0x0E, 0x1B, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00,     // Battery 3/4,   char num #4 Use LCD_Write_Char(4); to display this char
    0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00,     // Battery Full,  char num #5 Use LCD_Write_Char(5); to display this char
    0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00,     // Arrow Right    char num #6 Use LCD_Write_Char(6); to display this char
    0x00, 0x00, 0x0E, 0x11, 0x11, 0x0A, 0x1B, 0x00      // Ohm symbol,    char num #7 Use LCD_Write_Char(7); to display this char 
	0x0E, 0x11, 0x1B, 0x15, 0x11, 0x1F, 0x11, 0x0E,     //
	0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04, 0x00,     //
	0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00, 0x00,     // Open Heart
	0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00, 0x00,     // Solid Heart
	0x0E, 0x11, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00,     // Face
	0x0E, 0x11, 0x1B, 0x15, 0x11, 0x1F, 0x11, 0x0E,     //Char6
	0x00, 0x04, 0x0E, 0x1F, 0x0E, 0x04, 0x00, 0x00,     //Char7   */
};
// ***************************************************************************************************************************************************************
void InitCustomChars()
{
  uint8_t i;
  LCD_Cmd(0x04);                        // Set CGRAM Address (in LCD))
  LCD_Cmd(0x00);                        // Set Starting Point in CGRAM Address (I think?))
  for (i = 0; i < sizeof(__cgram) ; i++)
    LCD_Write_Char(__cgram[i]);
  LCD_Cmd(0);                           // Return to Home
  LCD_Cmd(2);                           // .. return to Home
}

// ***************************************************************************************************************************************************************
void LCD_Port(uint8_t a)
{
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}

// ***************************************************************************************************************************************************************
void LCD_Cmd(uint8_t a)
{
	RS = 0;             // => RS = 0
	LCD_Port(a);
	EN  = 1;             // => E = 1
    EN  = 0;             // => E = 0
    __delay_ms(4);
}

// ***************************************************************************************************************************************************************
void LCD_Clear()
{
	LCD_Cmd(0);
	LCD_Cmd(1);
}

// ***************************************************************************************************************************************************************
void LCD_Set_Cursor(uint8_t x, uint8_t y)
{
#ifdef LCD_TYPE_2_LINE

    uint8_t temp;
    uint8_t z,w;
    
	if(y == 0)
	{                
        temp = (uint8_t)(0x80 + x);
		z = (uint8_t)(temp>>4);
		w = (uint8_t)(temp & 0x0F);
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

	else if(y == 1)
	{
		temp = (uint8_t)(0xC0 + x);
		z = (uint8_t)(temp>>4);
		w = (uint8_t)(temp & 0x0F);
		LCD_Cmd(z);
		LCD_Cmd(w);
	}
#endif
        
#ifdef LCD_TYPE_4_LINE	
        
    char temp,z,w;
    
	if(y == 0)
	{                
        temp = 0x80 + x;
//        temp = 0x00 + x;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

	else if(y == 1)
	{
		temp = 0xC0 + x;
//		temp = 0x40 + x;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}


	else if(y == 2)
	{
        temp = 0x94 + x;
//        temp = 0x14 + x;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

    else if(y == 3)
	{
	    temp = 0xD4 + x;
//	    temp = 0x54 + x;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}
#endif
}
// ***************************************************************************************************************************************************************
void LCD_Init(char style)
{
    LCD_Port(0x00);
    
    __delay_ms(100);
    
    LCD_Cmd(0x03);              //Reset Instruction (3 times), as recommended by Hitachi
    
    __delay_ms(10);             // the first reset takes a while
    
    LCD_Cmd(0x03);
    
    __delay_us(120);            // the second and third reset, not so long
    
    LCD_Cmd(0x03);
    
    __delay_us(120);
    
    LCD_Cmd(0x02);              //Switch to 4 bit mode 
    
    __delay_us(120);
    
    LCD_Cmd(0x2);               //Sending 0x2 followed by 0x8 is the same as sending
    
    LCD_Cmd(0x8);               // 0x28, because we are now in 4 bit mode, 2 lines, 5x7 font 
    
    __delay_us(120);            // 0x28 is 4 bit,2 lines, 5x7 font
    
    LCD_Cmd(0x0);               //Display ON (0x0 followed by 0x8 = 0x08)
    
    LCD_Cmd(0x8);
    
    __delay_us(120);
    
    LCD_Cmd(0x0);               //0x0 + 0x1 = 0x01 (Clear Display))
    
    LCD_Cmd(0x1);               // This command writes to all 80 DRAM addresses, so takes more time
    
    __delay_ms(5);              // So, 5 milli seconds
    
    LCD_Cmd(0x0);               //0x0 + 0x6 = 0x06 (Entry Set Mode) We normally want the cursor to increment (move 
    
    LCD_Cmd(0x6);               //from left to right), and the display to not shift so we set I/D=1 and S=0.
    
    __delay_us(120);
    
    LCD_Cmd(0x0);               //Enable Display ON with style selected (BLINK, ULINE, BLUL, or NONE)
    
    LCD_Cmd((uint8_t)(0xc|style));         //We are sending 0x0c|style, usually NONE (or 0),which hides the cursor
    
    __delay_us(120);
/*
  LCD_Port(0x00);
   __delay_ms(20);
  LCD_Cmd(0x03);
	__delay_ms(5);
  LCD_Cmd(0x03);
	__delay_ms(11);
  LCD_Cmd(0x03);
  /////////////////////////////////////////////////////
  LCD_Cmd(0x02);
  LCD_Cmd(0x02);
  LCD_Cmd(0x08);
  LCD_Cmd(0x00);
  LCD_Cmd(0x0C|style);      //Enable Display ON with style selected (BLINK, ULINE, BLUL, or NONE))
  LCD_Cmd(0x00);
  LCD_Cmd(0x06); */
}
// ***************************************************************************************************************************************************************
void LCD_Write_Char(const char a)
{
   uint8_t temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;                  // => RS = 1
   LCD_Port((uint8_t)(y>>4));          //Data transfer
   EN = 1;
   EN = 0;
   __delay_us(40);
   LCD_Port(temp);
   EN = 1;
   EN = 0;
__delay_us(40);
   }
// ***************************************************************************************************************************************************************
void LCD_Write_String(const char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_Write_Char(a[i]);
}
// ***************************************************************************************************************************************************************
void LCD_Write_Int(int16_t value,int8_t fieldLength, uint8_t numPlaces, uint8_t sign)     //writes a integer type value to LCD module
{
	uint8_t str[5]={0,0,0,0,0};          // Integer can be up to 5 characters long
	uint8_t i=4,j=0;

    if(value<0)                         // Handle negative integers
    {
        LCD_Write_Char('-');            // Write Negative sign to the LCD
        value=value*-1;                 // convert negative value to a positive value
    }
    
    else
    {
        if(sign == 1)
        {
            LCD_Write_Char('+');
        }
    }

	while(value)
	{
            str[i]=value%10;
            value=value/10;
            i--;
	}
	if(fieldLength==-1)                 // if fieldLength is -1, the field length is # of digits in the value
    {
		while(str[j]==0)
        {
            j++;
        }
    }
	else
    {
		j=5-fieldLength;                // fieldLength must be between 1 and 5
    }

	for(i=j;i<(5-numPlaces);i++)
	{
        LCD_Write_Char(48+str[i]);            // Write out Integer value to the screen as characters
	}

    if(numPlaces == 1)
    {
        LCD_Write_Char(46);                   //A decimal period!
        LCD_Write_Char(48+str[4]);
    }

    if(numPlaces == 2)
    {
        LCD_Write_Char(46);                   //A decimal period!
        LCD_Write_Char(48+str[3]);
        LCD_Write_Char(48+str[4]);
    }
}
/*
// ***************************************************************************************************************************************************************
void LCD_Shift_Right()
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x0C);
}
// ***************************************************************************************************************************************************************
void LCD_Shift_Left()
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x08);
}
*/