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
 * File:   t6963c_specific.h
 * Author: Camil Staps
 *
 * Example of what you could put in a t6963c_specific.h.
 */

#ifndef T6963C_SPECIFIC_H
#define T6963C_SPECIFIC_H

#include "../lib/include/pic24_all.h"

#define t6963c_wr LATCbits.LATC1       // WR line
#define t6963c_t_wr TRISCbits.TRISC1   // TRIS bit of WR pin
#define t6963c_ce LATCbits.LATC2        // CE line
#define t6963c_t_ce TRISCbits.TRISC2    // TRIS bit of CE pin
#define t6963c_rst LATCbits.LATC3      // RESET line
#define t6963c_t_rst TRISCbits.TRISC3  // TRIS bit of RESET pin
#define t6963c_cd LATAbits.LATA14        // C/D line
#define t6963c_t_cd TRISAbits.TRISA14    // TRIS bit of C/D pin
#define t6963c_rd LATAbits.LATA15       // RD line
#define t6963c_t_rd TRISAbits.TRISA15   // TRIS bit of RD pin
#define t6963c_data LATA                // Data port (the lowest 8 bits are assumed)
#define t6963c_t_data TRISA             // TRIS register of data port
    
#define t6963c_rows 16                  // Number of rows of the LCD
#define t6963c_columns 40               // Number of columns of the LCD

#ifdef  __cplusplus
extern "C" {
#endif

#define t6963c_nspertick 25
    
/**
 * Define the project-specific timer functions here
 * @see t6963c.h
 */
inline void t6963c_initTimer(void);
inline void t6963c_startTimer(void);
inline unsigned short t6963c_getTimeNs(void);
inline void t6963c_stopTimer(void);

#ifdef  __cplusplus
}
#endif

#endif  /* T6963C_SPECIFIC_H */

