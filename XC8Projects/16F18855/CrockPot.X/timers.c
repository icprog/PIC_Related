#include "timers.h"

void TMR0_Initialize(void)
{
    T0CON0  =   0x10;               // Timer0 Disabled, 16 bit Timer, no PostScaler
    T0CON1  =   0x42;               // Source is FOSC/4, Synced to FOSC/4, 1:4 PreScaler
    TMR0H   =   0x24;               // Load Preset to Timer0 of  (at 250KHz, this should produce 1 rollover/second)
    TMR0L   =   0x9F;               // This is the Pre-Set Value, The value the Timer Starts with, then counts to 65535, for rollover
    PIE0bits.TMR0IE = 1;            // Enable Interupts
    PIR0bits.TMR0IF = 0;            // Reset Interupt Flag
    T0CON0bits.T0EN = 1;            // Turn on Timer0
}


void TMR2_Initialize(void)
{
    T2CON = 0x7F;                   // T2CKPS 1:128 Clock PreScaler; T2OUTPS 1:16 Out PostScaler; TMR2ON off;
    T2CLKCON = 0x01;                // Pg 440, T2CS(T2 Clock Source) FOSC/4; 
    T2HLT = 0x00;                   // Pg 442, Hardware Limit Cntrl, T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Ris ing Edge; T2CKSYNC Not Synchronized;
    T2RST = 0x00;                   // Pg 443, External Reset Source, T2RSEL T2CKIPPS pin;
    T2PR = 0xFF;                    // Period register, PR2 255; 
    T2TMR = 0x00;                   // TMR2 0;
    PIR4bits.TMR2IF = 0;            // Clearing IF flag.
    T2CONbits.TMR2ON = 1;           // Start the Timer by writing to TMRxON bit
} 