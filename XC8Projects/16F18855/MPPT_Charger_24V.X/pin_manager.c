#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x20;                        // LATA5 Must be turned on to provide power to Current Sensors, all other Port A pins set Low                  
    LATB = 0x00;                        // all Port B Outputs set to Low
    LATC = 0x00;                        // all Port C Outputs set to Low

    WPUA = 0x00;                        // All Port A Weak Pull-Ups disabled
    WPUB = 0x00;                        // All Port B Weak Pull-Ups disabled
    WPUC = 0x00;                        // All Port C Weak Pull-Ups disabled
    WPUE = 0x8;

    TRISA = 0x00;                       // All Port A Set as Outputs
    TRISB = 0x0E;                       // RB1, 2, and 3 as Input, RB0, 4, 5, 6, & 7 as Output
    TRISC = 0xFF;                       // All Port C as Input

    ANSELA = 0x00;                      // All Port A analog Inputs disabled
    ANSELB = 0x0A;                      // RB1 and RB3 as Analog Input
    ANSELC = 0xFF;                      // All Port C as Analog Input
    

    PIE0bits.IOCIE = 0;                 // interrupts-on-change are globally disabled
    int8_t state = GIE;                 // Record the value of GIE(Global Interrupt Enable) to state
    GIE = 0;                            // Disable Global Interrupts
    PPSLOCK = 0x55;                     
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

    RA6PPS = 0x0E;                      // Pin RA6 mapped to PWM6 Output
    RA7PPS = 0x0F;                      // Pin RA7->PWM7 Output
    RB0PPS = 0x09;                      // Pin RB0->CCP1/PWM1 Output
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;       // lock PPS
    GIE = state;                        // Set Global Interrupts back to as found state
}