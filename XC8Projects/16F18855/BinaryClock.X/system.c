//CONFIG1
#pragma config FEXTOSC =    OFF         // External Oscillator mode selection bits->Oscillator not enabled
#pragma config RSTOSC =     HFINT1      // Power-up default value for COSC bits->HFINTOSC (1MHz)
#pragma config CLKOUTEN =   OFF         // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN =      ON          // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN =      ON          // Fail-Safe Clock Monitor Enable bit->FSCM timer enabled

// CONFIG2
#pragma config MCLRE =      ON          // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTE =      ON          // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN =    OFF         // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN =      OFF         // Brown-out reset enable bits->Brown-out reset disabled
#pragma config BORV =       LO          // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD =        OFF         // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY =    ON          // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN =     ON          // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG3
#pragma config WDTCPS =     WDTCPS_31   // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE =       ON          // WDT operating mode->WDT Enabled, SWDTEN is ignored
#pragma config WDTCWS =     WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS =     SC          // WDT input clock selector->Software Control

// CONFIG4
#pragma config WRT =        OFF         // UserNVM self-write protection bits->Write protection off
#pragma config SCANE =      available   // Scanner Enable bit->Scanner module is available for use
#pragma config LVP =        ON          // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.

// CONFIG5
#pragma config CP =         OFF         // UserNVM Program memory code protection bit->Program Memory code protection disabled
#pragma config CPD =        OFF         // DataNVM code protection bit->Data EEPROM code protection disabled

#include "system.h"
#include "stdbool.h"


void PIN_MANAGER_Initialize(void)
{
    LATA = 0xEF;    
    LATB = 0x1F;    
    LATC = 0x1D;                        // Bit RC1 turned on to set Startup Time to 8:00 AM    

    TRISA = 0x10;                       // RA4 as Input for Timer 0 clock source
    TRISB = 0x00;
    TRISC = 0xC0;                       // RC6 & RC7 set as input for Minute & Hour setting 

    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x00;

    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    
    bool state = (unsigned char)GIE;    // Save the State of the Global Interrupt Enable Bit
    GIE = 0;                            // Then, Turn off GIE
    PPSLOCK =               0x55;
    PPSLOCK =               0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

    T0CKIPPSbits.T0CKIPPS = 0x04;       // Assign RA4 pin to TMR0:T0CKI (PPS assignment))

    PPSLOCK =               0x55;
    PPSLOCK =               0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;       // lock PPS

    GIE = state;                        // Return GIE to its former State
}       

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    TMR0_Initialize();                          // Initialize Timer0
    CPUDOZE = 0x46;                     // DOZEN = 1, DOZE = 1:128
}

void OSCILLATOR_Initialize(void)
{
    OSCCON1 = 0x62;                     // NOSC HFINTOSC; NDIV 4; 

    OSCCON3 = 0x00;                     // CSWHOLD may proceed; SOSCPWR Low power; 

    OSCEN = 0x00;                       // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 

    OSCFRQ = 0x00;                      // HFFRQ 1_MHz; 

    OSCTUNE = 0x00;                     // HFTUN 0; 
}