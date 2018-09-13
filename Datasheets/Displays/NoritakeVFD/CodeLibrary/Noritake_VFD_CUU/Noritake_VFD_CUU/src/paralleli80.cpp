#include "config.h"

#if NORITAKE_VFD_INTERFACE==1 && NORITAKE_VFD_PARALLEL==1

#include <avr/io.h>
#include <util/delay.h>
#include "interface.h"

static void dataDirection(bool dir) {
    DIRECTION(D4, dir);
    DIRECTION(D5, dir);
    DIRECTION(D6, dir);
    DIRECTION(D7, dir);
    #if NORITAKE_VFD_4BIT != 1
        DIRECTION(D0, dir);
        DIRECTION(D1, dir);
        DIRECTION(D2, dir);
        DIRECTION(D3, dir);
    #endif
}

void
initPort() {
    _delay_ms(NORITAKE_VFD_RESET_DELAY);

    RAISE(RD);
    RAISE(WR);
    DIRECTION(RS, 1);
    DIRECTION(WR, 1);
    DIRECTION(RD, 1);
    dataDirection(true);

    #if NORITAKE_VFD_4BIT==1
        writePort(0x33, false); // 8-bit function set, 8-bit function set
        writePort(0x32, false); // 8-bit function set, 4-bit function set
    #else
        writePort(0x38, false); // 8-bit function set
        writePort(0x38, false); // 8-bit function set
    #endif
    writePort(0x00, true);  // 100% brightness
    writePort(0x08, false); // display off
    writePort(0x01, false); // display clear
    _delay_ms(2.3);         // wait for clear
    writePort(0x0c, false); // display on, cursor off
    writePort(0x06, false); // left-to-right entry mode
}

void
writePort(uint8_t data, bool rs) {
    SETPIN(RS, rs);
    #if NORITAKE_VFD_4BIT==1
        // High nybble
        SETPIN(D4, data & 0x10);
        SETPIN(D5, data & 0x20);
        SETPIN(D6, data & 0x40);
        SETPIN(D7, data & 0x80);
        LOWER(WR);
        _delay_us(.450);
        RAISE(WR);
        _delay_us(.450);
    
        // Low nybble
        SETPIN(D4, data & 0x01);
        SETPIN(D5, data & 0x02);
        SETPIN(D6, data & 0x04);
        SETPIN(D7, data & 0x08);
        LOWER(WR);
        _delay_us(.450);
        RAISE(WR);
        _delay_us(.450);
    #else
        SETPIN(D0, data & 0x01);
        SETPIN(D1, data & 0x02);
        SETPIN(D2, data & 0x04);
        SETPIN(D3, data & 0x08);
        SETPIN(D4, data & 0x10);
        SETPIN(D5, data & 0x20);
        SETPIN(D6, data & 0x40);
        SETPIN(D7, data & 0x80);
        LOWER(WR);
        _delay_us(.450);
        RAISE(WR);
        _delay_us(.450);
    #endif
}

uint8_t
readPort(bool rs) {
    uint8_t data;
    SETPIN(RS, rs);
    dataDirection(false);
    
    #if NORITAKE_VFD_4BIT==1
        // High nybble
        LOWER(RD);
        _delay_us(.160);
        data = (CHECK(D7)? 0x80: 0) +
            (CHECK(D6)? 0x40: 0) +
            (CHECK(D5)? 0x20: 0) +
            (CHECK(D4)? 0x10: 0);
        RAISE(RD);
        _delay_us(.450);
        
        // Low nybble
        LOWER(RD);
        _delay_us(.160);
        data += (CHECK(D7)? 0x08: 0) +
            (CHECK(D6)? 0x04: 0) +
            (CHECK(D5)? 0x02: 0) +
            (CHECK(D4)? 0x01: 0);
        RAISE(RD);
        dataDirection(true);
        return data;
    #else
        LOWER(RD);
        _delay_us(.160);
        RAISE(RD);
        data = (CHECK(D7)? 0x80: 0) +
            (CHECK(D6)? 0x40: 0) +
            (CHECK(D5)? 0x20: 0) +
            (CHECK(D4)? 0x10: 0) +
            (CHECK(D3)? 0x08: 0) +
            (CHECK(D2)? 0x04: 0) +
            (CHECK(D1)? 0x02: 0) +
            (CHECK(D0)? 0x01: 0);
        dataDirection(true);
        return data;
    #endif
}

#endif
