/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
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
//#pragma _XTAL_FREQ 8000000
#define _XTAL_FREQ 2000000
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/



//////////////////////////////////////////////////////////////////////////////
// This is the simple CCS program for I2C (PCF8574T) lcd module
// Auther: Pumrin S.
// Pin map:
// PCF8574T > 20x4 LCD
//   P0     >   RS
//   P1     >   R/W
//   P2     >   E
//   P3     >   NC
//   P4     >   D4
//   P5     >   D5
//   P6     >   D6
//   P7     >   D7
// Note: The SCL and SDA pins should be pull-up resister allway.
//////////////////////////////////////////////////////////////////////////////

//#include <18f4520.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd20x4.h"
#include <i2c.h>

//#fuses XT,NOWDT,NOPROTECT,NOLVP
//#use delay(clock=4000000)
//#use I2C (master, sda = PIN_C4, scl = PIN_C3)

#define LCDADDR        0x70 // default slave address
#define ON            0x08
#define OFF            0x00

#define LCD_SET_BIT(x)    fetch_data(x)


int LCD_ADDR=0x4e; //I2C slave address for Funduino LCD module

//Transmittion data
void transceiver(unsigned char data)
   {

        i2c_start();
        i2c_write(LCD_ADDR); //the slave addresse
        i2c_write(data);
        i2c_stop();
   }

//Clocking the LCD's enable pin during transmit data
void fetch_data(unsigned char data)
   {
        data=data|0b00000100;//set pin E is a 1
        transceiver(data);
        __delay_ms(1);
        data=data-4;//toggle E back to 0
        transceiver(data);
        __delay_ms(1);

   }

void lcd_init()
{

   //Request works on the command by set the RS = 0 R/W = 0 write
        LCD_SET_BIT(0x00);
        LCD_SET_BIT(0x10);
        LCD_SET_BIT(0x00);
        LCD_SET_BIT(0x00);
        LCD_SET_BIT(0x10);
           //First state in 8 bit mode
        LCD_SET_BIT(0x30);
        LCD_SET_BIT(0x30);
           //Then set to 4-bit mode
        LCD_SET_BIT(0x30);
        LCD_SET_BIT(0x20);
           //mode 4 bits, 2 lines, characters 5 x 7 (28 h)
        LCD_SET_BIT(0x20);
        LCD_SET_BIT(0x80);
           //no need cursor on (0Ch)
        LCD_SET_BIT(0x00);
        LCD_SET_BIT(0xC0);
           //the cursor moves to the left (06 h)
        LCD_SET_BIT(0x00);
        LCD_SET_BIT(0x60);
           //clears the display
        LCD_SET_BIT(0x00);
        LCD_SET_BIT(0x10);
}

void lcd_clear()
{
    LCD_SET_BIT(0x00);
    LCD_SET_BIT(0x10);
}

// Need the backlight lid.
void lcd_backlight(int state)
{
  LCD_SET_BIT(0x00);
  LCD_SET_BIT(state);
}

//Display the character on LCD screen.
void display(char in_data)
{
        char data;
        data=in_data&0xF0;
        data=data+1; //set RS pin to 1
        fetch_data(data);
        data=in_data&0x0F;
        data=data<<4;
        data=data+1; //set RS pin to 1
        fetch_data(data);

}

//Make the x/y pointer
void lcd_goto_xy(int x, int y)
{
  int ptr1, ptr2;

  fetch_data(0x10);
  fetch_data(0x00);

  switch(y)
  {
   case 1:
          ptr1=line_1[x]&0xF0;// stamp the high bit
          ptr2=line_1[x]&0x0F;// stamp the low bit

     break;

   case 2:
           ptr1=line_2[x]&0xF0;
          ptr2=line_2[x]&0x0F;

     break;

   case 3:
          ptr1=line_3[x]&0xF0;
          ptr2=line_3[x]&0x0F;

     break;

   case 4:
           ptr1=line_4[x]&0xF0;
          ptr2=line_4[x]&0x0F;

     break;

   default:
          fetch_data(0x80);
          fetch_data(0x00);
     break;

  }
          ptr2=ptr2<<4;
          fetch_data(ptr1);
          fetch_data(ptr2);
}

void main()
{
  char led=0;
  __delay_ms(20);
  lcd_init();

        lcd_goto_xy(0,1);
        display("ABCDEFGHIJKLMNOPQRST");
        lcd_goto_xy(0,2);
        display("12345678901234567890");
        lcd_goto_xy(0,3);
        display("AAAAAAAAAAAAAAAAAAAA");
        lcd_goto_xy(6,4);
        display("It's Work.!!!");
        lcd_backlight(ON);
     while(1);

}



/*
int16_t main(void)
{

    // Configure the oscillator for the device
    ConfigureOscillator();

    // Initialize IO ports and peripherals
    InitApp();

    // TODO <INSERT USER APPLICATION CODE HERE>

    while(1)
    {

    }
}
*/