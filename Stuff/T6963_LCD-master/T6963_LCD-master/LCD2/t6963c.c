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
 */

#include "../lib/include/pic24_all.h"
#include "t6963c.h"
#define NULL 0

inline void delay_ns(unsigned short ns) {
/*
    t6963c_startTimer();
    while (t6963c_getTimeNs() < ns);
    t6963c_stopTimer();
*/
    DELAY_US(ns);
}

UCHAR t6963c_StatusRead(void)
{
    UCHAR ret;
    t6963c_cd = 1;
    t6963c_wr = 1;
    t6963c_rd = 0;
    DELAY_MS(20);
    ret = (UCHAR)(t6963c_data & 0x00ff);
    t6963c_ce = 0;
    DELAY_MS(20);
    delay_ns(5);
    t6963c_ce = 1;
    t6963c_rd = 1;
    DELAY_MS(20);
    delay_ns(5);
    
    return ret;
}
    

void t6963c_writeByte(unsigned cd, UCHAR byte) {
    t6963c_cd = cd;
    t6963c_wr = 0;
    t6963c_data &= 0xff00;
    t6963c_data |= 0x00ff & byte;
    t6963c_ce = 0;
    delay_ns(2);
    t6963c_ce = 1;
    t6963c_wr = 1;
    delay_ns(2);
}

void t6963c_writeCmd1(UCHAR cmd, UCHAR data) {
    t6963c_writeByte(0, data);
    t6963c_writeByte(1, cmd);
    delay_ns(600);
}

void t6963c_writeCmd2(UCHAR cmd, UCHAR data1, UCHAR data2) {
    t6963c_writeByte(0, data1);
    t6963c_writeByte(0, data2);
    t6963c_writeByte(1, cmd);
    delay_ns(600);
}

void t6963c_startAutoWrite(void) {
    t6963c_writeByte(1, 0xb0);
    delay_ns(600);
    delay_ns(600);
}

void t6963c_stopAutoWrite(void) {
    t6963c_writeByte(1, 0xb2);
    delay_ns(600);
    delay_ns(600);
}

void t6963c_autoWrite(UCHAR byte) {
    t6963c_cd = 0;
    t6963c_wr = 0;
    t6963c_data &= 0xff00;
    t6963c_data |= 0x00ff & byte;
    t6963c_ce = 0;
    delay_ns(2);
    t6963c_ce = 1;
    t6963c_wr = 1;
    delay_ns(60);
}

inline void t6963c_autoWriteChar(UCHAR byte) {
    t6963c_autoWrite(byte - 0x20);
}

void t6963c_writeString(UCHAR* string) {
    t6963c_startAutoWrite();
    for (;*string;string++)
        t6963c_autoWriteChar((UCHAR)*string);
    t6963c_stopAutoWrite();
}

void t6963c_clear(void) {
    unsigned short i;
    t6963c_set_address(0, 0);
    t6963c_startAutoWrite();
    for (i = 0; i < t6963c_rows * t6963c_columns; i++) {
        t6963c_autoWrite(0x00);
    }
    t6963c_writeCmd2(0x24, 0x00, 0x03);
    for (i = 0; i < t6963c_rows * t6963c_columns; i++) {
        t6963c_autoWrite(t6963c_attr_normal);
    }
    t6963c_stopAutoWrite();
    t6963c_set_cursor_address(0, 0);
}

void t6963c_init(void) {
    unsigned short i;
    
    t6963c_t_rst = 0;
    t6963c_t_cd = 0;
    t6963c_t_ce = 0;
    t6963c_t_rd = 0;
    t6963c_t_wr = 0;
    t6963c_t_data &= 0xff00;
    
    t6963c_wr = 1;
    t6963c_rd = 1;
    t6963c_cd = 1;
    t6963c_ce = 1;
    
    t6963c_rst = 0;
    for (i = 0; i < 10; i++)
        delay_ns(600);
    t6963c_rst = 1;
    
    t6963c_writeCmd2(0x40, 0x00, 0x00);             // text home address
    t6963c_writeCmd2(0x41, t6963c_columns, 0x00);   // text area set
    t6963c_writeCmd2(0x42, 0x00, 0x03);             // graphic home address
    t6963c_writeCmd2(0x43, t6963c_columns, 0x00);   // graphic area set
    
    t6963c_writeByte(1, 0b10000100);    // text attribute, internal ROM
    t6963c_writeByte(1, 0b10011111);    // graphic, text, cursor, blink
    t6963c_writeByte(1, 0xa7);          // 8-line cursor
    t6963c_clear();
    
    t6963c_set_address(0, 0);
    t6963c_set_cursor_address(0, 0);
    
//    t6963c_initTimer();
}

void t6963c_set_address(UCHAR row, UCHAR column) {
    unsigned short address = 
            ((unsigned short) row) * ((unsigned short) t6963c_columns) + column;
    t6963c_writeCmd2(0x24, address & 0xff, ((address >> 8) & 0xff));
}

void t6963c_set_cursor_address(UCHAR row, UCHAR column) {
    t6963c_writeCmd2(0x21, column, row);
}

#if 0
void t6963c_update_terminal(Terminal* term) {
    unsigned int i;
    UCHAR row, column;
    
    while (terminal.lines_needed(term->content, t6963c_columns) > t6963c_rows)
        terminal.discard_first_line(term->content, t6963c_columns);
    
    row = 0;
    column = 0;
    t6963c_set_address(0, 0);
    t6963c_startAutoWrite();
    for (i=0; term->content[i]; i++) {
        if (term->content[i] == '\n') {
            t6963c_autoWriteChar(' ');
            while (column = (column + 1) % t6963c_columns)
                t6963c_autoWriteChar(' ');
            row++;
        } else {
            t6963c_autoWriteChar(term->content[i]);
            column = (column + 1) % t6963c_columns;
            if (column == NULL)
                row++;
        }
    }
    t6963c_stopAutoWrite();
    t6963c_set_cursor_address(row, column);
    t6963c_startAutoWrite();
    while (row != t6963c_rows) {
        t6963c_autoWriteChar(' ');
        column = (column + 1) % t6963c_columns;
        if (column == NULL)
            row++;
    }
    t6963c_stopAutoWrite();
}
#endif
