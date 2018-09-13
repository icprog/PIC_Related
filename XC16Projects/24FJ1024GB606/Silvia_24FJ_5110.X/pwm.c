#include "pwm.h"



void InitializeTimers(void)
{
 //   T1CONbits.TON =     0;                          // Turn Timer1 OFF
   // T1CONbits.TCS =     1;                          // Timer Clock source selected by T1ECS
//    T1CONbits.T1ECS =   0x0;                        // Timer 1 Extended Clock Selection bits (00 = Secondary Oscillator)
  //  T1CONbits.TCKPS =   0x1;                        // Timer 1 input clock pre-scale bits 01 = 1:8 
    //PR1 =               0x03FF;                     // Timer 1 Period value of .25 Seconds for a Frequency of 4Hz
//    T1CONbits.TON =     1;                          // TIMER 1 ON

    T2CONbits.TON   =   0;                          // Turn Timer2 OFF
    T2CONbits.TCS   =   1;                          // Timer Clock source selected by TECS
    T2CONbits.TECS  =   0x0;                        // Timer 2 Extended Clock Selection bits (00 = Secondary Oscillator)
    T2CONbits.TCKPS =   0x0;                        // Timer 2 input clock pre-scale bits 00 = 1:1 
    PR2             =   0x2000;
    T2CONbits.TON =     1;                          // Turn Timer 2 ON
}
// *****************************************************************************

void Initialize_PWM(void)
{
    OC5R =                  0x0000;                 // Set On time (Duty Cycle))
    OC5RS =                 0x2000;                 // Set Period for Edge aligned PWM
    OC5CON2bits.SYNCSEL =   0X1F;                   // Set OC5RS as Sync source, so, the OC5 is it's own sync source
    OC5CON2bits.OCTRIG =    0;                      // Synchronized with OC5 (Synchronized with itself)
    OC5CON1bits.OCTSEL =    0;                      // Set Timer 2 as clock source
    OC5CON1bits.OCM =       0x6;                    // Set OC3 Mode to Edge aligned PWM

    OC4R =                  0x2000;                 // Set On time (Duty Cycle) OC4 Pin will output high on compare, when timer hits OC4RS, pin is set low
    OC4RS =                 0x0000;                 // Set Duty Cycle for center aligned PWM, turns off OC4 when timer reaches OC4RS
    OC4CON2bits.SYNCSEL =   0X03;                   // Set Set OC5RS as Sync source
    OC4CON2bits.OCTRIG =    0;                      // Set Synchronous operation (with OC5)
    OC4CON1bits.OCTSEL =    0;                      // Set Timer 2 as clock source (Timer2 is the default))
    OC4CON1bits.OCM =       0x7;                    // Set OC4 Mode to Center aligned PWM 

    OC6R =                  0x2000;                 // Set On time (Duty Cycle) OC6 Pin will output high on compare, when timer hits OC6RS, pin is set low
    OC6RS =                 0x0000;                 // Set Duty Cycle for center aligned PWM, turns off OC6 when timer reaches OC6RS
    OC6CON2bits.SYNCSEL =   0X03;                   // Set Set OC5RS as Sync source
    OC6CON2bits.OCTRIG =    0;                      // Set Synchronous operation (with OC5)
    OC6CON1bits.OCTSEL =    0;                      // Set Timer 2 as clock source (Timer2 is the default))
    OC6CON1bits.OCM =       0x7;                    // Set OC6 Mode to Center aligned PWM 
}