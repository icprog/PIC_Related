
#include <p18cxxx.h>

#include "glcd.h"

const rom char font[]= { 

 /* add your own font data

    each char is 3x8 pixels. 3 bytes per char. left column, middle column, right column

 */

};

void _lcd_enable(void)

{

    Delay10TCYx(1);

    ENABLE=1;

    Delay10TCYx(1);

    ENABLE=0;

    Delay10TCYx(1);

}

unsigned char _lcd_status(void)

{

    // returns the lcd status & maintains the TRIS state of the

    // lcd data port

    unsigned char _lcd_tris, _status;

    // save the tris value

    _lcd_tris = LCD_TRIS;

    // read the status
    LCD_TRIS=0xFF; // all inputs

    DI=0; RW=1; // command/read

    _lcd_enable();

    _status = LCD_DATA;

    // restore the tris value
    LCD_TRIS = _lcd_tris;

    

    return _status;

}

void _lcd_reset(void)

{

    // reset the lcd module
    // datasheet says reset must be low for minimum of 1us

    // after Vdd clears 4.5v. 

    // from experimentation, this is bullshit. this seems to
    // work though.

    Delay10TCYx(250); // actually .5 ms

    RESET=1;
    Delay10TCYx(250); // actually .5 ms

    RESET=0;

    // check status, and wait if necessary

    while (_lcd_status() & 0b00010000)

    {
        Delay10TCYx(250); // .5 ms

    }

}

void lcd_screenon(unsigned char on)

{

    // turn the display on or off

    LCD_TRIS=0; // all outputs

    RW=0; DI=0;

    LATB = 0b00111110 | (on & 0b00000001); // main screen turn on!
    _lcd_enable();

}

void lcd_cls(void)

{

    unsigned char x,y;

    for (x=0; x<8; x++)

    {

        // set the page (x)

        lcd_setpage(x);

        // set the y address to 0

        lcd_setyaddr(0);

        // setup for data

        LCD_DATA=0; RW=0; DI=1;

        // clear the row

        for (y=0; y<64; y++)

        {

            _lcd_enable(); 

            //Delay10TCYx(1);

        }

    }

}

void lcd_setpage(unsigned char page)

{

    _lcd_waitbusy();

    DI=0; RW=0; 

    LCD_DATA = 0b10111000 | page;

    _lcd_enable();

}

void lcd_setyaddr(unsigned char y)

{
    _lcd_waitbusy();

    DI=0; RW=0;

    LCD_DATA = 0b01000000 | (y & 0b00111111);

    _lcd_enable();

}

void _lcd_waitbusy(void)

{
    while (_lcd_status() & 0b10000000)

    {

        Delay10TCYx(250); // .5 ms

    }

}

void lcd_write (unsigned char data)

{

    _lcd_waitbusy();

    DI=1; RW=0;

    LCD_TRIS=0; 

    LCD_DATA = data;

    _lcd_enable();

}

void lcd_selectside(unsigned char sides)

{

    // set a CS pin low to enable it

    if (sides & LEFT)

        CS1 = 0;

    else

        CS1 = 1;

    if (sides & RIGHT)

        CS2 = 0;

    else

        CS2 = 1;

}

unsigned char lcd_read (void)

{

    unsigned char _data;

    

    LCD_TRIS=0xFF;

    RW = 1; DI=1;

    _lcd_enable();

    _data = LCD_DATA;

    LCD_TRIS=0x00;

    return _data;

}

void lcd_plotpixel(unsigned char rx, unsigned char ry)

{

    unsigned char data;

    //lcd_waitbusy();

    // select the correct side

    if (rx & 64)

        lcd_selectside(RIGHT);

    else

        lcd_selectside(LEFT);

 

    lcd_setpage( ry >> 3);
    lcd_setyaddr( rx & 0b00111111);

    data = lcd_read(); // dummy read needed here

    data = lcd_read();

    lcd_setyaddr( rx & 0b00111111); 

    lcd_write (data | (1 << (ry & 0b111)));

}

 

void lcd_putchar(char c)

{

    int base;

    base = c - 32;

    base *= 3;

    lcd_write(font[base]);

    lcd_write(font[base + 1]);

    lcd_write(font[base + 2]);

    lcd_write(0);

}

void lcd_putrs(const rom char *string)

{

    char i=0;

    while (string[i] != 0)

        lcd_putchar(string[i++]);

} 

void lcd_puts(char *string)

{

    char i=0;

    while (string[i] != 0)

        lcd_putchar(string[i++]);

} 
