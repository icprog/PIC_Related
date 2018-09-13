#include "pwm.h"

void InitializeTimers(void)
{
    T1CONbits.TON       =   0;                          // Timer1 is used for generating PWM frequency for Pump
    T1CONbits.TCS       =   1;                          // Timer Clock source selected by T1ECS
    T1CONbits.T1ECS     =   0x0;                        // Timer 1 Extended Clock Selection bits (00 = Secondary Oscillator)
    T1CONbits.TCKPS     =   0x2;                        // Timer 1 input clock pre-scale bits (TCKPS) 11 = 1:64
    T1CONbits.TON       =   1;                          // TIMER 1 ON

    T2CONbits.TON       =   0;                          // Turn Timer OFF
    T2CONbits.TCKPS     =   0x3;                        // T2 PreScaler = 1:256
    PR2                 =   0x0C38;                     // Period set to 3128, generates an Interrupt every 1/10 seconds 
//    PR2                 =   0x030E;                     // Period set to 782, generates an Interrupt every 1/10 seconds 
    T2CONbits.TON       =   1;                          // Turn Timer 2 ON
    
    T3CONbits.TON       =   0;                          // T3 runs the PWM (center-aligned) to Split power between Water & Steam Boilers)
    T3CONbits.TCKPS     =   0x3;                        // T3 PreScaler = 1:256
    PR3                 =   0x7A10;                     // 31248 counts for 2 second period @ 32MHz
//    PR3                 =   0x1E84;                     // 7812 counts for 2 second period @ 8 MHz
    T3CONbits.TON       =   1;                          // T3 On
}
// *****************************************************************************
void InitializePWM(void)
{
    OC1R                =   0x0000;                 // set WaterPump DutyCycle to 0
    OC1RS               =   0x0100;                 // 0x100 = 256 counts x 1:64 Prescaler on Timer1, = .25 Second period
    OC1CON2bits.SYNCSEL =   0X1F;                   // Set Self Sync as source
    OC1CON2bits.OCTRIG =    0;                      // Set OC1 as Sync source
    OC1CON1bits.OCTSEL =    0X4;                    // Set Timer 1 as clock source
    OC1TMR =                0x0000;                 // Set OC1 timer to zero
    OC1CON1bits.OCM =       0x6;                    // Set OC1 Mode to Edge aligned PWM

    OC3R                =   0x0000;                 // set Steam Boiler DutyCycle to 0
    OC3RS               =   0x7A10;                 // Set Period = 1 second (8MHz/256 = 31248 = 7A10 Hex)
//    OC3RS               =   0x1E84;                 // Set Period = 1 second (2MHz/256 = 7812 = 1E84 Hex)
    OC3CON2bits.SYNCSEL =   0X1F;                   // Set Self Sync as source
    OC3CON2bits.OCTRIG =    0;                      // Set OC3 as Sync source
    OC3CON1bits.OCTSEL =    0X1;                    // Set Timer 3 as clock source
    OC3CON1bits.OCM =       0x6;                    // Set OC3 Mode to Edge aligned PWM  FIX(Change to Center aligned)
    
    OC2R =                  0x0000;                 // set Water Boiler DutyCycle to 0
    OC2RS =                 0x7A10;                 // Set Period = 1 second (8MHz/256 = 31248 = 7A10 Hex)
//    OC2RS =                 0x1E84;                 // Set Period = 1 second (2MHz/256 = 7812 = 1E84 Hex)
    OC2CON2bits.SYNCSEL =   0X02;                   // Set OC3 as Sync source
    OC2CON2bits.OCTRIG =    0;                      // Set OC3 as Sync source(rather than trigger source)
    OC2CON1bits.OCTSEL =    0X1;                    // Set Timer 3 as clock source
    OC2CON1bits.OCM =       0x7;                    // Set OC2 Mode to Edge aligned PWM  FIX(Change to CenterAligned)
}