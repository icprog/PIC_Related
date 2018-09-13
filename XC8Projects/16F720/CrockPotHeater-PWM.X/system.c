#include "system.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

void ConfigureOscillator(void)
{
    FVRCON = 0xF2;                      // FVREN = 1, TSEN = 1, TSRNG = 1, FVR @ 2.048V
    IRCF1 = 0;                          // These 2 parameters set Clock @ 2 MHz when PLL EN=1, 62.5 KHz when PLLEN = 0 (PLLEN = 0 for this Project)
    IRCF0 = 0;                          // These 2 parameters set Clock @ 2 MHz when PLL EN=1, 62.5 KHz when PLLEN = 0 (PLLEN = 0 for this Project)
//    OSCTUNE = 0x00;                     // Change default oscilator speed (See page 68)

    TMR0 = 0;                           // TMR0 Pre-set
    T0CS = 0;                           // TMR0 Clock source 0 = internal clock (FOSC/4)
//    T0SE = 0;                           // Triggering on Low to High edge 
    PSA = 0;                            // Work with a PreScaler on Timer0
    PS0 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS1 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS2 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
}

// Initialisation routine
void Init()
{
    TRISA =  0x10;                       // RA2 and RA4 as inputs, 0 = output 1 = input
    ANSELA = 0x10;                       // RA2 and RA4 as Analog (0 = Digital, 1 = Analog)
    PORTA =  0x00;                       // Set all port A register to 1, 1 = off, 0 = on, (if sinking)

    TRISB = 0b00000000;                 // 0 = output, 1 = input
    ANSELB = 0b00000000;                // No Analogs (0 = Digital, 1 = Analog)
    PORTB = 0x00;                       // Set all port B register to 0, 1 = off, 0 = on

    TRISC = 0b00000000;                       // 0 = output 1 = input
    ANSELC = 0x00;                      // 0 = Digital, 1 = Analog
//    PORTC = 0xff;                       // Set all port C register to 1, 1 = off, 0 = on



//    TRISCbits.TRISC5 = 1; // Disable RC5 output driver till PWM configured, this is done already above
    // Setup PWM on pin RC5/CCP1/P1
    PR2 = 0xff; // Set PWM period (PR2+1) * 4 * Tosc * TMR2_Prescale_value
    //PR2 = 0x65; // Set PWM period (PR2+1) * 4 * Tosc * TMR2_Prescale_value
    // period = (255 + 1) * 4 * 0.25us * 16 = 4.1ms
    // frequency = 1 / 4.1ms = 244Hz
    CCP1CON = 0x00;                                     // Reset all bits to 0 
    CCP1CONbits.CCP1M = 0xF;                            // Set up for PWM mode, with only P1 active
    CCPR1L = 0xFF;                                      // Setup for 100% duty cycle
    // Setup Timer 2 for PWM
    PIR1bits.TMR2IF = 0;                                // Clear Timer 2 interrupt flag
    T2CONbits.T2CKPS = 0x3;                             // Set Timer 2 prescaler to 1:16
//    T2CONbits.T2CKPS = 0x0;                           // Set Timer 2 prescaler to 1:1
    T2CONbits.TMR2ON = 1;                               // Enable Timer 2
    while(PIR1bits.TMR1IF);                             // Wait for first overflow
    TRISCbits.TRISC5 = 0;                               // Sets pin RC5 to output for PWM

    // Setup Timer 1 for handling PWM duty cycle
    T1CON = 0;
    T1CONbits.T1CKPS0 = 1;                              // T1CKPS = 11 = 1:8 prescaler
    T1CONbits.T1CKPS1 = 1;                              // so timer clock = 1MHz / 8 = 125kHz
    /* Calculating for PWM duty cycle increment every 50ms, so period needs
     * to be 20Hz. Timer 1 clock is 125kHz, so
     * for 20Hz, we divide 125kHz by 20 = 6250. Then we subtract this
     * from the rollover value of 65,535, so 65,535 - 6250 = 59,285
     * which is 0xE795 in hex. Timer 1 has two 8-bit high and low
     * registers, so we put 0xE7 in the high and 0x95 in the low */
    TMR1H = 0xE7;           
    TMR1L = 0x95;
    T1CONbits.TMR1ON = 1;                               // Turn timer on
    INTCONbits.GIE = 1;                                 // Enable global interrupts
    INTCONbits.PEIE = 1;                                // Enable peripheral interrupts
    PIR1bits.TMR1IF = 0;                                // Clear Timer 1 interrupt flag
    PIE1bits.TMR1IE = 1;                                // Enable Timer 1 interrupt
}