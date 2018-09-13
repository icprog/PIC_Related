#include "system.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif


//******************************************************************************
//              O S C I L L A T O R   C O N F I G U R A T I O N
//******************************************************************************

void ConfigureOscillator(void)
{
    IRCF1 = 0;                          // These 2 parameters set Clock @ 2 MHz
    IRCF0 = 0;                          // These 2 parameters set Clock @ 2 MHz
    
    // Change default oscilator speed (See page 68)
    OSCTUNE = 0b00111110;               // 16 Seconds slow in 3 hours (5.3 sec/hr)        
//  OSCTUNE = 0b00111111;               // 373 seconds fars in 20 Hr 1 Min (18.65 sec/hr))
    
    TMR0 = 0;                           // TMR0 Pre-set

    OPTION_REG = 0x47;                  // Replaces all the following commented out bits

//    nRABPU = 0;                         // Enables Weak Pull-ups on A & B Ports
//    T0CS = 0;                           // TMR0 Clock source 0 = internal clock (FOSC/4)
//    T0SE = 0;                           // Triggering on Low to High edge
//    PSA = 0;                            // Work with a PreScaler
//    PS0 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
//    PS1 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
//    PS2 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)

    FVRCON = 0xf3;

//    TSEN = 1;
  //  TSRNG = 1;
}

//******************************************************************************
//        E N D   o f   O S C I L L A T O R   C O N F I G U R A T I O N
//******************************************************************************


//******************************************************************************
//              P R O G R A M   C O N F I G U R A T I O N
//******************************************************************************

void Init()                             // Initialization Function
{

    TRISA =  0x14;                      // RA2 and RA4 as Input, All others as output 0 = output 1 = input
    ANSELA = 0x10;                      // RA4 Set as Analog, (SetPoint Pot) (0 = Digital, 1 = Analog)
    PORTA =  0x00;                      // Set all port A register to 0, 1 = off, 0 = on, (if sinking)
    WPUA =   0x04;                      // Set Weak Pull-up on RA2 (MenuButton)

    TRISB =  0x30;                      // 0 = output, 1 = input
    ANSELB = 0x30;                      // RB4 and RB5 as Analog (0 = Digital, 1 = Analog)
    PORTB =  0x40;                      // Set all port B register to 0, Except RB6, 1 = off, 0 = on
    WPUB =   0x00;                      // All Port B Weak Pull-ups Disabled

    TRISC =  0x80;                      // 0 = output 1 = input
    ANSELC = 0x80;                      // 0 = Digital, 1 = Analog (RC7 as Analog, all others as Digital)
    PORTC =  0x00;                      // Set all port C register to 1, 1 = off, 0 = on

}

//******************************************************************************
//     E N D  o f   P R O G R A M   C O N F I G U R A T I O N
//******************************************************************************
