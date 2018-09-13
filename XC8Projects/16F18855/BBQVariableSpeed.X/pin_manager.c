#include <xc.h>
#include "pin_manager.h"
#include <stdbool.h>

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    WPUA = 0x00;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUE = 0x8;

    TRISA = 0x0A;                       // RA1 & 3 as Input
    TRISB = 0x07;                       // RB0,1,& 2 as Input                    
    TRISC = 0x00;

    ANSELA = 0x0A;                      // RA1 & 3 as Analog inputs
    ANSELB = 0x00;                      
    ANSELC = 0x00;
    
    PIE0bits.IOCIE = 0;                 // interrupts-on-change are globally disabled
    int8_t state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

    RC2PPS = 0x0E;                      // RC2->PWM6:PWM6OUT;
    RC3PPS = 0X0F;                      // PWM7Out Re-mapped to RC3

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}