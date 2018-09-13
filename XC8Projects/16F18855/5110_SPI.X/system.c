
// CONFIG1
#pragma config FEXTOSC = OFF        // External Oscillator mode selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINT1      // Power-up default value for COSC bits->HFINTOSC
#pragma config CLKOUTEN = OFF       // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = ON           // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON           // Fail-Safe Clock Monitor Enable bit->FSCM timer enabled

// CONFIG2
#pragma config MCLRE = ON           // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTE = OFF          // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN = OFF        // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN = OFF          // Brown-out reset enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO            // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD = OFF            // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY = ON         // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN = ON          // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG3
#pragma config WDTCPS = WDTCPS_31   // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF           // WDT operating mode->WDT Disabled, SWDTEN is ignored
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC          // WDT input clock selector->Software Control

// CONFIG4
#pragma config WRT = OFF            // UserNVM self-write protection bits->Write protection off
#pragma config SCANE = available    // Scanner Enable bit->Scanner module is available for use
#pragma config LVP = ON             // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.

// CONFIG5
#pragma config CP = OFF             // UserNVM Program memory code protection bit->UserNVM code protection disabled
#pragma config CPD = OFF            // DataNVM code protection bit->DataNVM code protection disabled

#include <xc.h>
#include "system.h"

void SYSTEM_Initialize(void)
{
    TRISA = 0x30;                   // All PortA set to Outputs, except RA4 & RA5
    TRISB = 0x00;                   // All PortB set to Outputs
    TRISC = 0x08;                   // All PortC set to Outputs Except RC7

    ANSELA = 0x10;                  // All PortA set to Digital Except RA4
    ANSELB = 0x00;                  // All PortB set to Digital
    ANSELC = 0x00;                  // All PortC set to Digital

    LATA = 0x00;                    // LATA all set to low Output
    LATB = 0x20;                    // LATB5 needs to be 1 (high), to provide + Supply V for LCD Power    
    LATC = 0x00;                    // LATC all set to low Output

    WPUA = 0x00;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUE = 0x8;

    OSCILLATOR_Initialize();
    FVRCON = 0x00;                  // Set Fixed Voltage reference
//    TMR2_Initialize();
  //  PWM_Initialize();
    //ADC_Initialize();
    SPI_Init();
    LCDInit();
    __delay_ms(200);
    LCDClear();
    __delay_ms(100);
    
    PIE0bits.IOCIE = 0;                 // interrupts-on-change are globally disabled
    signed char state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

    SSP1DATPPS = 0x14;                      //PPS for RC4 to be SDI
    RC5PPS = 0x15;                          //PPS for RC5 points at SDO1
    RC3PPS = 0x14;                          //PPS for RC3 points at SCK

//    T2AINPPSbits.T2AINPPS = 0x0013;   //RC3->TMR2:T2IN; RC3 as hardware input pin to timer 2???
//    RC2PPS = 0x0E;                      //RC2->PWM6:PWM6OUT;
//    RC3PPS = 0X0F;                      // PWM7Out Re-mapped to RC3
//    RA2PPS = 0x000E;   //RA2->PWM6:PWM6OUT;
//    RA3PPS = 0x000E;                    //RA3->PWM6:PWM6OUT;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}
    
void OSCILLATOR_Initialize(void)
{
    OSCCON1 = 0x60;                 // NOSC HFINTOSC; NDIV 1; 
    OSCCON3 = 0x00;                 // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCEN = 0x00;                   // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCFRQ = 0x00;                  // HFFRQ 1_MHz; 
    OSCTUNE = 0x00;                 // HFTUN 0; 
}