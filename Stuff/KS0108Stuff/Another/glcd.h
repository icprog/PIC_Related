//The functions that start _lcd* are intended to be for internal use by the library, whereas lcd* are for your use. Of course, that doesn't limit you in what you do at all.

glcd.h

#include <p18cxxx.h>
#include <delays.h>

#define LCD_TRIS      TRISB
#define LCD_DATA      PORTB
#define ENABLE        PORTDbits.RD7
#define RW            PORTDbits.RD6
#define DI            PORTDbits.RD5
#define RESET         PORTDbits.RD4

#define CS1           PORTDbits.RD2

#define CS2           PORTDbits.RD3

 

#define LEFT          0b01

#define RIGHT         0b10

#define BOTH          0b11

#define NONE          0b00

// internal function prototypes

// 

// you would not normally call these directly. but you can 

// if you like.

void _lcd_enable(void);

unsigned char _lcd_status(void);

void _lcd_reset(void);

void _lcd_waitbusy(void);

// public function prototypes

//

// call these all you want !

void lcd_screenon(unsigned char on);

void lcd_cls(void);

void lcd_setpage(unsigned char page);

void lcd_setyaddr(unsigned char y);

void lcd_selectside(unsigned char sides);

void lcd_write (unsigned char data);

unsigned char lcd_read (void);

void lcd_plotpixel(unsigned char rx, unsigned char ry);

void lcd_putchar(char c);

void lcd_puts(char *string);

void lcd_putrs(const rom char *string);