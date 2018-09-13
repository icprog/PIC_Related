#include <xc.h>
#include "system.h"
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x20;                        // LATA5 Must be turned on to provide power to Current Sensors                  
    LATB = 0x00;                       
    LATC = 0x00;                    

    WPUA = 0x00;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUE = 0x8;

    TRISA = 0x00;
    TRISB = 0x0E;                       // RB1, 2, and 3 as Input, RB0, 4, 5, 6, & 7 as Output
    TRISC = 0xFF;                       // Port C as Input

    ANSELA = 0x00;
    ANSELB = 0x0A;                      // RB1 and 3 as Analog Input
    ANSELC = 0xFF;                      // Port C as Analog Input
    

    PIE0bits.IOCIE = 0;                 // interrupts-on-change are globally disabled
    int8_t state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

    RA6PPS = 0x0E;                      // RA6->PWM6:PWM6 OUT;
    RA7PPS = 0x0F;                      // RA7->PWM7:PWM7 OUT;
    RB0PPS = 0x09;                      // RB0->CCP1:PWM1 Output
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;       // lock PPS
    GIE = state;
}