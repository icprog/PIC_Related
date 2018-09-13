/**
 * C library for interfacing a T6963C display with a PIC microcontroller
 * Copyright (C) 2015 Camil Staps <info@camilstaps.nl>

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *******************************************************************************
 *
 * File:   t6963c.h
 * Author: Camil Staps <info@camilstaps.nl>
 *
 * C library for interfacing a T6963C LCD display. This library was written with
 * the help of the application note "Writing Software for T6963C based Graphic
 * LCDs", https://www.sparkfun.com/datasheets/LCD/Monochrome/T6963C-AppNote.pdf
 * 
 * This is the generic library. In t6963c_specific.h, you should define which 
 * pins you are using for what function. Also, timer functions should be written
 * in a t6963c_specific.c. The rationale is to separate the generic and the 
 * project-specific code.
 */

#include "t6963c_specific.h"
#include "terminal.h"

#ifndef T6963C_H
#define T6963C_H

#ifdef  __cplusplus
extern "C" {
#endif
        
/**
 * To be written by someone implementing this library.
 * Initialise the timer for the delay functions
 */
extern inline void t6963c_initTimer(void);
   
/**
 * To be written by someone implementing this library.
 * Start the timer for the delay functions
 */
extern inline void t6963c_startTimer(void);
   
/**
 * To be written by someone implementing this library.
 * Get the amount of ns (nano seconds) elapsed since starting the timer with
 * t6963c_startTimer().
 */
extern inline unsigned short t6963c_getTimeNs(void);
   
/**
 * To be written by someone implementing this library.
 * Stop the timer for the delay functions
 */
extern inline void t6963c_stopTimer(void);

// Text attribute mode definitions
#define t6963c_attr_normal 0x00
#define t6963c_attr_invert 0x05
#define t6963c_attr_inhibit 0x03
#define t6963c_attr_blink 0x08
#define t6963c_attr_bl_invert 0x0d
#define t6963c_attr_bl_inhibit 0x0b

UCHAR t6963c_StatusRead(void);
        
/**
 * Write a single byte to the LCD
 * @param cd whether this is a command (1) or data (0)
 * @param byte the byte to send
 */
void t6963c_writeByte(unsigned cd, unsigned char byte);

/**
 * Write a command with one data byte to the LCD
 * @param cmd the command byte
 * @param data the data byte
 */
void t6963c_writeCmd1(unsigned char cmd, unsigned char data);

/**
 * Write a command with two data bytes to the LCD
 * @param cmd the command byte
 * @param data1 the first data byte
 * @param data2 the second data byte
 */
void t6963c_writeCmd2(unsigned char cmd, unsigned char data1, unsigned char data2);

/**
 * Start "auto write mode". After this, characters may be written with 
 * t6963c_autoWrite or t6963c_autoWriteChar. No commands can be executed until
 * calling t6963c_stopAutoWrite().
 */
void t6963c_startAutoWrite(void);

/**
 * Finish an "auto write" session.
 * @see t6963c_startAutoWrite
 */
void t6963c_stopAutoWrite(void);

/**
 * Auto write a raw byte to the LCD
 * @param byte the byte
 * @see t6963c_startAutoWrite
 */
void t6963c_autoWrite(unsigned char byte);

/**
 * Auto write an ASCII byte to the LCD
 * @param character the character
 * @see t6963c_startAutoWrite
 */
inline void t6963c_autoWriteChar(unsigned char character);

/**
 * Write an ASCII string to the LCD
 * @param string
 */
void t6963c_writeString(unsigned char* string);

/**
 * Clear the LCD, and set the data address to the top left
 */
void t6963c_clear(void);

/**
 * Initialise the LCD for text attribute mode
 */
void t6963c_init(void);

/**
 * Set the data write address
 * @param row
 * @param column
 */
void t6963c_set_address(unsigned char row, unsigned char column);

/**
 * Set the cursor address
 * @param row
 * @param column
 */
void t6963c_set_cursor_address(unsigned char row, unsigned char column);

/**
 * This function may be used as a callback from a Terminal.update.
 */
void t6963c_update_terminal(Terminal*);

#ifdef  __cplusplus
}
#endif

#endif  /* T6963C_H */

