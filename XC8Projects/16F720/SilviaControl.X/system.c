#include "system.h"

#if defined(__XC)
    #include <xc.h>         // XC8 General Include File
#elif defined(HI_TECH_C)
    #include <htc.h>        // HiTech General Include File
#endif


//******************************************************************************
//***           O S C I L L A T O R   C O N F I G U R A T I O N              ***
//******************************************************************************

void ConfigureOscillator(void)
{
    IRCF1 = 0;                          // These 2 parameters set Clock @ 2 MHz
    IRCF0 = 0;                          // These 2 parameters set Clock @ 2 MHz
    OSCTUNE = 0b00111110;               // Change default oscilator speed (See page 68)

    TMR0 = 0;                           // TMR0 Pre-set

    OPTION_REG = 0xc7;                  // Replaces all the following commented out bits See Pg 91

//    nRABPU = 1;                         // Disable Weak Pull-ups on A & B Ports
//    T0CS = 0;                           // TMR0 Clock source 0 = internal clock (FOSC/4)
//    T0SE = 0;                           // Triggering on Low to High edge
//    PSA = 0;                            // Work with a PreScaler
//    PS0 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
//    PS1 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
//    PS2 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)

    FVRCON = 0xd3;                        // Fixed Voltage Reference See Pg 86
}
//******************************************************************************
//        E N D   o f   O S C I L L A T O R   C O N F I G U R A T I O N
//******************************************************************************


//******************************************************************************
//              P R O G R A M   C O N F I G U R A T I O N
//******************************************************************************

void Init(void)                                     // Initialization Function
{
    TRISA = 0xff;                               // Unused inputs, 0 = output 1 = input
    ANSELA = 0x00;                              // all digital, no analog, 0 = Digital, 1 = Analog
    PORTA = 0xff;                               // Set all port A register to 1, 1 = off, 0 = on

    TRISB = 0xff;                               // 0 = output, 1 = input
    ANSELB = 0x00;                              // digital, no analog
    PORTB = 0xff;                               // Set all port B register to 0, 1 = Vh, 0 = Vl

    TRISC = 0x03;                               // Set RC0 and RC1 to Inputs, all others to Output, 0 = output, 1 = input
    ANSELC = 0x00;                              // digital, no analog
    PORTC = 0xfc;                               // RC0 and RC1 as zero (Vl), all others as 1 (Vh)

}

//******************************************************************************
//     E N D  o f   P R O G R A M   C O N F I G U R A T I O N
//******************************************************************************
