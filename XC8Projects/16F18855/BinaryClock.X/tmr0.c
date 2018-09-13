#include <xc.h>
#include "tmr0.h"

void TMR0_Initialize(void)
{
    T0CON0 = 0x00;              // T0OUTPS 1:1; T0EN disabled; 8-bit Timer; 

    T0CON1 = 0x17;              // T0CS T0CKI_PIN; T0CKPS 1:128; T0ASYNC not_synchronised; 

    TMR0H = 0xFF;               // TMR0H 255;  Count 0 to 255 (256 counts) x PreScaller of 128 = 32768/second (32.768 KHz Osc on Timer0 Input)

    TMR0L = 0x00;               // TMR0L 0;    Setup as 8 bit Timer, so, these bits not used 

    PIR0bits.TMR0IF = 0;        // Clear IF flag
    
    T0CON0bits.T0EN = 1;        // Start Timer 0
}