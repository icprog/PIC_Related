#include "interupts.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

// Interrupt Service Routine (keyword "interrupt" tells the compiler it's an ISR)
void interrupt int_routine(void)
{
    extern unsigned char OutCurrent;
    
    // Check it's the timer that has interrupted
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;    // Clear interrupt flag
        T1CONbits.TMR1ON = 0;   // Turn timer off to reset count register

        TMR1H = 0xE7;   // Reset timer count - 0xE795 = 20Hz
        TMR1L = 0x95;   //

        T1CONbits.TMR1ON = 1;   // Turn timer back on
//        CCPR1L--; // Increment duty cycle
//        CCPR1L++; // Increment duty cycle
        CCPR1L = OutCurrent; // Set Duty cyle to "Current" Setpoint
    }

    // process other interrupt sources here, if required
}
