// FBS  Search the p24FV16KM204.h file for options for the config bits
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot program flash segment)

// FGS  
#pragma config GWRP = OFF               // General Segment Write Protect (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC Oscillator (FRC))
#pragma config SOSCSRC = ANA            // SOSC Source Type (Analog Mode for use with crystal)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = ON      
// Internal External Switch Over bit (Internal External Switchover mode enabled (Two-speed Start-up enabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = IO            // CLKO Enable Configuration bit (Port I/O enabled (CLKO disabled))
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)


#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:16384) resets in 65.536 seconds, time setting takes 60
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bits (WDT enabled in hardware)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware, SBOREN bit disabled)
#pragma config RETCFG = OFF             //  (Retention regulator is not available)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Use Default SCL1/SDA1 Pins For I2C1)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (RA5 input pin disabled, MCLR pin enabled)

// FICD
#pragma config ICS = PGx1               // ICD Pin Placement Select bits (EMUC/EMUD share PGC1/PGD1)


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