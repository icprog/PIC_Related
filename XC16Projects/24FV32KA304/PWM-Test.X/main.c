/* 
 * File:   main.c
 * Author: IBRAHIM LABS
 *
 * Created on July 5, 2013, 10:37 AM
 */

// FBS
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot program flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Write Protect (General segment may be written)
#pragma config GSS0 = OFF               // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRCDIV           // Oscillator Select (8MHz FRC oscillator With Postscaler (FRCDIV))
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define CRYSTAL_FREQUENCY   16000000         // Crystal of 16MHz
#define FCY CRYSTAL_FREQUENCY/2UL            // Instruction Cycle Clock must be defined
//#include <p24F16KA102.h>
#include <libpic30.h>
#include "PWM.h"

/******************************************************************************/
//OC3 is on Pin 12 RA10

/*  *** Configuration Bits Setting  *** */

//_FGS(GWRP_OFF & GCP_OFF)
//_FOSCSEL(FNOSC_PRI & IESO_OFF)
//_FOSC(POSCMOD_HS & OSCIOFNC_ON & POSCFREQ_HS & FCKSM_CSDCMD)
//_FWDT(WINDIS_OFF & FWDTEN_OFF)
//_FPOR(BOREN_BOR2 & PWRTEN_OFF  & MCLRE_ON)
//_FDS(DSBOREN_OFF & DSWDTEN_OFF)

/******************************************************************************/
/*
 *
 */



int main(void)
{
    unsigned int DutyCycle = 10;
    
    InitializeTimer2For_PWM();
    Initialize_PWM();

    /*  Internal Pullups enabled    */
    CNPU3bits.CN33PUE = 1;                  // Weak Pull up on RA8   
    CNPU1bits.CN9PUE = 1;                   // Weak Pull-up on RA7

    UP_DIRECTION = Input;
    DOWN_DIRECTION = Input;


    while(1)
    {

        if (!UP)
        {
            __delay_us(100);
            if (DutyCycle < 0x7FFA)     
                SetDutyCycle_PWM(DutyCycle++);
        }
        else if (!DOWN)
        {
            __delay_us(100);
            if (DutyCycle > 0x0F)
                SetDutyCycle_PWM(DutyCycle--);
        }
    
    }
    return 0;
}
