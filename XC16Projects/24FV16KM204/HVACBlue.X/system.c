#include "system.h"          /* variables/params used by system.c */

//Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
//compiler installation directory /doc folder for documentation on the
// __builtin functions. 

void ConfigureOscillator(void)
{
 //   _FBS = 0x0f;
//    _FOSCSEL = 0x47;

//    _RTCCLK1 = 0;       // Set RTCC Clock Source to Internal 32kHz RC
//    _RTCCLK0 = 0;

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
    TRISA = 0x0001;                 // RA0 (analog 0) Set as Input, Data Direction 1 = input, 0 = Output
    TRISB = 0xF3EC;                 // RB2,3,5,6,7,8,9,12,13,14,15 as InputsData Direction 1 = input, 0 = Output
    TRISC = 0x0007;                 // RC0,1, and 2 (analog 0, 1, and 13) Set as Inputs, Data Direction 1 = input, 0 = Output
    
    ANSA =  0x0001;                 // AN0 (pin19)is Set as Analog. Analog or Digital 1 = Analog, 0 = Digital
    ANSB =  0xF3EC;                 // AN4,5,17,18,19,20,21,12,11,10,and 9 Set as Analog Analog or Digital 1 = Analog, 0 = Digital
    ANSC =  0x0007;                 // AN6, AN7, and AN8 (pin25,26, and 27)are Set as Analog. Analog or Digital 1 = Analog, 0 = Digital
    
    PORTA = 0x0000;                 // Power up state of the Port Pins(ie as a 1 or a 0)
    PORTB = 0x0000;
    PORTC = 0x0000;
    
    ConfigureOscillator();
    
    ADCInit();

    LCD_Init(NONE);
    
    LCD_Clear();
    
    InitCustomChars();

    RTCC_Initialize();
}
//***************************************************************************************************************************************************************