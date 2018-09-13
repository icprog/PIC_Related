#include "pwm.h"

// PWM Setup    Timer 1 is set to use Secondary Oscillator (32768 Hz), with the Pre-Scaler set at 1:8, giving us 4096 Hz (32768/8)
// We then set PR1 to 0x3FF (1023, which gives us 1024 counts, 0 - 1023), so the timer will roll over 4 times in one second.
// We then can set our dutyCycle anywhere between 0 (OFF) and 2047 (ON 100%)

void InitializeTimers(void)
{
    T1CONbits.TON =     0;                          // Timer1 is used for generating PWM frequency
    T1CONbits.TCS =     1;                          // Timer Clock source selected by T1ECS
    T1CONbits.T1ECS =   0x0;                        // Timer 1 Extended Clock Selection bits (00 = Secondary Oscillator)
    T1CONbits.TCKPS =   0x1;                        // Timer 1 input clock pre-scale bits 01 = 1:8 
    TMR1 =              0x0000;                     // Timer 1 preset value??
    PR1 =               0x03FF;                     // Timer 1 Period value of .25 Seconds for a Frequency of 4Hz
    T1CONbits.TON =     1;                          // TIMER 1 ON
    T2CONbits.TON =     0;                          // Turn Timer OFF
    PR2 =               0x4D30;                     // Period value set in Timer 2, to make it so Timer 2 rolls over every 1/100th seconds
    T2CONbits.TON =     1;                          // Turn Timer 2 ON
}
// *****************************************************************************

void Initialize_PWM(void)
{
    OC3R =                  0x0000;                 // Set On time (Duty Clcle))
//    OC3RS =                 0x0000;                 // Set Period for Edge aligned PWM
    OC3CON2bits.SYNCSEL =   0X1F;                   // Set Timer 1 as Sync source
    OC3CON2bits.OCTRIG =    0;                      // Set OC3 as Sync source
    OC3CON1bits.OCTSEL =    0X7;                    // Set Timer 1 as clock source
    OC3TMR =                0x0000;                 // Set OC3 timer to zero
    OC3CON1bits.OCM =       0x6;                    // Set OC3 Mode to Edge aligned PWM (Center aligned works as well, except it is on until OCxR, turns off until OCxRS, so, 
}                                                   // dutyCycle of zero turns ON OC, until it hits OCxRS (works fine down to dC of 1, then goes to pulsing mode)
// *****************************************************************************
void setDutyCycle(unsigned int dutyCycle)
{
    OC3R = dutyCycle;                              
}
// *****************************************************************************

