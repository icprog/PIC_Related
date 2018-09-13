#include "system.h"


void SYSTEM_Initialize(void)
{
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    

    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0xC0;

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
    
    bool state = (unsigned char)GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    T0CKIPPSbits.T0CKIPPS = 0x04;   //RA4->TMR0:T0CKI;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;

    OSCILLATOR_Initialize();
    TMR0_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // NOSC HFINTOSC; NDIV 4; 
    OSCCON1 = 0x62;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 4_MHz; 
    OSCFRQ = 0x02;
    // HFTUN 0; 
    OSCTUNE = 0x00;
}
