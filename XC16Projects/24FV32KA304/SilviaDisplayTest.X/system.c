// FBS
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot program flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Write Protect (General segment may be written)
#pragma config GSS0 = OFF               // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Select (8MHz FRC oscillator With PLL)
//#pragma config FNOSC = FRCDIV           // Oscillator Select (8MHz FRC oscillator With Postscaler (FRCDIV))
#pragma config SOSCSRC = ANA            // SOSC Source Type (Analog Mode for use with crystal)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = ON                // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-speed Start-up enabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = OFF           // CLKO Enable Configuration bit (CLKO output disabled)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bits (WDT enabled in hardware)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware, SBOREN bit disabled)
#pragma config LVRCFG = OFF             // Low Voltage Regulator Configuration bit (Low Voltage regulator is not available)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Use Default SCL1/SDA1 Pins For I2C1)
#pragma config BORV = V20               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (2.0V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (RA5 input pin disabled,MCLR pin enabled)

// FICD
#pragma config ICS = PGx1               // ICD Pin Placement Select bits (EMUC/EMUD share PGC1/PGD1)

// FDS
#pragma config DSWDTPS = DSWDTPSF       // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses Low Power RC Oscillator (LPRC))
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)

#if defined(__XC16__)
    #include <xc.h>
#endif

#include "system.h"          /* variables/params used by system.c */
/* TODO Add clock switching code if appropriate.  An example stub is below.   */
//void ConfigureOscillator(void)
//{
//    CLKDIVbits.RCDIV = 0x4;                         // Set RCDIV to 100 (Clock Divider bits to 500 KHz)
 //   _FBS = 0x0f;
//    _FOSCSEL = 0x47;

//    _RTCCLK1 = 0;       // Set RTCC Clock Source to Internal 32kHz RC
//    _RTCCLK0 = 0;

//#if 0

        /* Disable Watch Dog Timer */
//        RCONbits.SWDTEN = 0;

        /* When clock switch occurs switch to Prim Osc (HS, XT, EC)with PLL */
//        __builtin_write_OSCCONH(0x03);  /* Set OSCCONH for clock switch */
//        __builtin_write_OSCCONL(0x01);  /* Start clock switching */
//        while(OSCCONbits.COSC != 0b011);

        /* Wait for Clock switch to occur */
        /* Wait for PLL to lock, if PLL is used */
        /* while(OSCCONbits.LOCK != 1); */

//#endif
        
//}
//***************************************************************************************************************************************************************

void InitApp(void)                  // Setup analog functionality and port direction
{
    TRISA = 0x0081;                 // RA0 & RA7 Set as Input, Data Direction 1 = input, 0 = Output
    TRISB = 0x8C04;                 // RB2, 10, 11, and 15 as Input, Data Direction 1 = input, 0 = Output
    TRISC = 0x0203;                 // RC0, 1, and 9 as Inputs, Data Direction 1 = input, 0 = Output
    
    ANSA =  0x0001;                 // RA0(AN0,Pin 19) as Analog, 1 = Analog, 0 = Digital
    ANSB =  0x8004;                 // RB2(AN4,Pin23), and RB15(AN9,Pin15) as Analog, Analog or Digital 1 = Analog, 0 = Digital
    ANSC =  0x0003;                 // RC0(AN6,Pin25) and 1(AN7,Pin26) as Analog, Analog or Digital 1 = Analog, 0 = Digital
    
    PORTA = 0x0000;                 // Power up state of the Port Pins(ie as a 1 or a 0)
    PORTB = 0x0000;
    PORTC = 0x0000;                 // Make sure Pin 13 always initialized low, is reset pin for LCD
    
    CNPU1 = 0x0200;                 // Enable Weak Pull-ups on CN9 (Pin 6)
    CNPU2 = 0x0009;                 // Enable Weak Pull-ups on CN16 & 19 (Pin 8 & 5)
    

//    ConfigureOscillator();
    LCDInit();
    ADCInit();
//    __delay_ms(100);
    LCDClear();
    RTCC_Initialize();
}
//***************************************************************************************************************************************************************