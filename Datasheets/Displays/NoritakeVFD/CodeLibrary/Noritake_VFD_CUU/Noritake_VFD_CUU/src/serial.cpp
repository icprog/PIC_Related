#include "config.h"

#if NORITAKE_VFD_INTERFACE==0

#include <avr/io.h>
#include <util/delay.h>
#include "interface.h"

void
initPort() {
    _delay_ms(NORITAKE_VFD_RESET_DELAY);
    
    RAISE(STB);
    RAISE(SCK);
    DIRECTION(SIO, 1);
    DIRECTION(SCK, 1);
    DIRECTION(STB, 1);

    #if NORITAKE_VFD_BC == 1
        writePort(0x30, false); // 8-bit function set 100% brightness
        writePort(0x30, false); // 8-bit function set 100% brightness
        writePort(0x08, false); // display off
        writePort(0x01, false); // display clear
        _delay_ms(2.3);         // wait for clear
        writePort(0x0c, false); // display on, cursor off
        writePort(0x06, false); // left-to-right entry mode
    #else
        writePort(0x38, false); // 8-bit function set
        writePort(0x38, false); // 8-bit function set
        writePort(0x00, true);  // 100% brightness
        writePort(0x08, false); // display off
        writePort(0x01, false); // display clear
        _delay_ms(2.3);         // wait for clear
        writePort(0x0c, false); // display on, cursor off
        writePort(0x06, false); // left-to-right entry mode
    #endif
}

static void
innerWrite(uint8_t x) {
    for (uint8_t i=0x80; i; i>>=1) {
        LOWER(SCK);
        SETPIN(SIO, x & i);
        RAISE(SCK);
    }
}

void
writePort(uint8_t data, bool rs) {
    LOWER(STB);
    innerWrite(rs? 0xfa: 0xf8);
    innerWrite(data);
    RAISE(STB);
}

uint8_t
readPort(bool rs) {
    LOWER(STB);
    innerWrite(rs? 0xfe: 0xfc);
    DIRECTION(SIO, 0);
    uint8_t data = 0;
    for (uint8_t i=0; i<8; i++) {
        LOWER(SCK);
        data <<= 1;
        RAISE(SCK);
        if (CHECK(SIO))
            data |= 1;
    }
    DIRECTION(SIO, 1);
    RAISE(STB);
    return data;
}

#endif
