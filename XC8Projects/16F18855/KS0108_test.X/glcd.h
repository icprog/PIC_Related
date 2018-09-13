#ifndef GLCD_H
#define	GLCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "system.h"    
    
#define LCD_TRIS      TRISC
#define LCD_DATA      PORTC
#define ENABLE        PORTBbits.RB4
#define RW            PORTBbits.RB3
#define DI            PORTBbits.RB2
#define LCD_RESET     PORTBbits.RB5

#define CS1           PORTBbits.RB0

#define CS2           PORTBbits.RB1

 

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

void lcd_putrs(const char *string);




#ifdef	__cplusplus
}
#endif

#endif	/* GLCD_H */

