#include "pwm.h"

void InitializeTimers(void)
{
    T2CONbits.TON   =   0;                          // Turn Timer2 OFF
    T2CONbits.TCS   =   1;                          // Timer Clock source selected by TECS
    T2CONbits.TECS  =   0x0;                        // Timer 2 Extended Clock Selection bits (00 = Secondary Oscillator)
    T2CONbits.TCKPS =   0x0;                        // Timer 2 input clock pre-scale bits 00 = 1:1 
    PR2             =   0x1000;                     // Timer2 Pre-Set
    T2CONbits.TON =     1;                          // Turn Timer 2 ON
}
// *****************************************************************************

void Initialize_PWM(void)
{
    OC4CON1                 = 0;
    OC4CON2                 = 0;
    OC4CON1bits.OCTSEL      = 0X0;                  // Set Timer 2 as clock source
    OC4R                    = 0X0;                  // Set On time (Duty Cycle)
    OC4RS                   = 0X1000;               // Set Period for Edge aligned PWM
    OC4CON2bits.SYNCSEL     = 0X1F;                 // Set OC4RS as Sync source, so, the OC4 is it's own sync source
    OC4CON1bits.OCM         = 6;                    // Set OC4 Mode to Edge aligned PWM

    OC5CON1                 = 0;
    OC5CON2                 = 0;
    OC5CON1bits.OCTSEL      = 0X07;                 // Set Peripheral Clock as clock source
    OC5R                    = 0X01F4;               // Set On time (Duty Cycle)
    OC5RS                   = 0X1000;               // Set Period for Edge aligned PWM
    OC5CON2bits.SYNCSEL     = 0X1F;                 // Set OC5RS as Sync source, so, the OC5 is it's own sync source
    OC5CON1bits.OCM         = 6;                    // Set OC5 Mode to Edge aligned PWM
}
