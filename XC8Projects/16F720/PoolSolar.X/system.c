#include "system.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

void ConfigureOscillator(void)
{
    IRCF1 = 0;                          // These 2 parameters set Clock @ 2 MHz
    IRCF0 = 0;                          // These 2 parameters set Clock @ 2 MHz
    OSCTUNE = 0x00;                     // Change default oscilator speed (See page 68)

    TMR0 = 0;                           // TMR0 Pre-set
    T0CS = 0;                           // TMR0 Clock source 0 = internal clock (FOSC/4)
    T0SE = 0;                           // Triggering on Low to High edge
    PSA = 0;                            // Work with a PreScaler
    PS0 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS1 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS2 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
}