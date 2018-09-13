/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include <stdint.h>          /* For uint32_t definition */
#include <stdbool.h>         /* For true/false definition */

#include "system.h"          /* variables/params used by system.c */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c                                           */
/*                                                                            */
/******************************************************************************/

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions. */

/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void)
{
 //   _FBS = 0x0f;
//    _FOSCSEL = 0x47;

    _RTCCLK1 = 0;       // Set RTCC Clock Source to Internal 32kHz RC
    _RTCCLK0 = 0;

#if 0

        /* Disable Watch Dog Timer */
//        RCONbits.SWDTEN = 0;

        /* When clock switch occurs switch to Prim Osc (HS, XT, EC)with PLL */
//        __builtin_write_OSCCONH(0x03);  /* Set OSCCONH for clock switch */
//        __builtin_write_OSCCONL(0x01);  /* Start clock switching */
//        while(OSCCONbits.COSC != 0b011);

        /* Wait for Clock switch to occur */
        /* Wait for PLL to lock, if PLL is used */
        /* while(OSCCONbits.LOCK != 1); */

#endif
        
}
//***************************************************************************************************************************************************************

void InitApp(void)                  // Setup analog functionality and port direction
{
    TRISA = 0x0007;                 // RA0,1, and 2 (analog 0, 1, and 13) Set as Inputs, Data Direction 1 = input, 0 = Output
    TRISB = 0xf3ec;                 // RB2,3,5,6,7,8,9,12,13,14,15 as InputsData Direction 1 = input, 0 = Output
    TRISC = 0x0000;                 // Data Direction 1 = input, 0 = Output
    
    ANSA =  0x0007;                 // AN0, AN1, and AN13 (pin19,20)are Set as Analog. Analog or Digital 1 = Analog, 0 = Digital
    ANSB =  0xf3ec;                 // AN4,5,17,18,19,20,21,12,11,10,and 9 Set as Analog Analog or Digital 1 = Analog, 0 = Digital
    ANSC =  0x0000;                 // Analog or Digital 1 = Analog, 0 = Digital
    
    PORTA = 0x0000;                 // Power up state of the Port Pins(ie as a 1 or a 0)
    PORTB = 0x0000;
    PORTC = 0x0000;
}
//***************************************************************************************************************************************************************