// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINT1    // Power-up default value for COSC bits->HFINTOSC (1MHz)
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->FSCM timer enabled

// CONFIG2
#pragma config MCLRE = ON    // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTE = OFF    // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN = OFF    // Brown-out reset enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD = OFF    // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY = ON    // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset
//#pragma config DEBUG = OFF    // Background Debugger->Background Debugger disabled

// CONFIG3
#pragma config WDTCPS = WDTCPS_31    // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF    // WDT operating mode->WDT Disabled, SWDTEN is ignored
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT input clock selector->Software Control

// CONFIG4
#pragma config WRT = OFF    // UserNVM self-write protection bits->Write protection off
#pragma config SCANE = available    // Scanner Enable bit->Scanner module is available for use
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.

// CONFIG5
#pragma config CP = OFF    // UserNVM Program memory code protection bit->Program Memory code protection disabled
#pragma config CPD = OFF    // DataNVM code protection bit->Data EEPROM code protection disabled

#include <xc.h>
//#include "system.h"
#include <stdint.h>
#include <stdbool.h>
#include "tmr0.h"

#define _XTAL_FREQ  1000000



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


//#define _XTAL_FREQ 1000000      //1 MHz default after reset

//    INTCON = 0;
//    T0EN = 1;
  //  T0ASYNC = 1;

//        T0CS = 1;               //Set Timer 0 as 8 bit counter
  //      T0XCS = 0;              //Set Timer clock source to T0CKI Pin
//        PSA = 1;                //PreScaler assigned to WDT, so 1:1 PreScaler for Timer0
  //      PS2 = 1;
    //    PS1 = 0;                // 101 = 1:32 for WDT
      //  PS0 = 1;
        //ADCON1 = 0x70;     // conversion speed for ADC

void main(void)
{
    SYSTEM_Initialize;
    
//    int x, v, SEC_COUNT, MIN_COUNT, HOUR_COUNT, DEBOUNCE;
  //  long int CORRECTION_COUNTER;
    //static bit T0_PULSE, INCREMENT;
//    x = 0;
  //  v = 0;
    //SEC_COUNT = 0;
//    MIN_COUNT = 0;
  //  HOUR_COUNT = 0;
    //DEBOUNCE = 0;
//    CORRECTION_COUNTER = 0;
    
    while(1)
    {
        RB4 = 0;
        __delay_ms(1000);
        RB4 = 1;
        __delay_ms(1000);
        
/*        if (TMR0IF == 1)
        {
            TMR0IF = 0;
            x++;
            T0_PULSE = 1;
        }

        if (x == 0x0080 && v == 0)
        {
            x = 0;
            v = 1;
        }
        
        if (x == 0x0080 && v == 1)
        {
            x = 0;
        }
 */
 
 
/*        if (v == 1 && RB4 == 1){
            RB4 = 0;
            v = 0;
        }
        if (v == 1 && RB4 == 0){
            RB4 = 1;
            v = 0;
        }
*/

/*        if (v == 1)
        {
            SEC_COUNT++;
            CORRECTION_COUNTER++;
            
            if (CORRECTION_COUNTER >= 172800)
            {
                if (SEC_COUNT > 0)
                {
                    SEC_COUNT--;
                    CORRECTION_COUNTER = 0;
                }
            }
            
            v = 0;
            
            if (SEC_COUNT == 60)
            {
                SEC_COUNT = 0;
                INCREMENT = 1;
            }
            
            RB4 = !(SEC_COUNT & 0x01);
            RB3 = !((SEC_COUNT & 0x02) >> 1);
            RB2 = !((SEC_COUNT & 0x04) >> 2);
            RB1 = !((SEC_COUNT & 0x08) >> 3);
            RB0 = !((SEC_COUNT & 0x10) >> 4);
            RA7 = !((SEC_COUNT & 0x20) >> 5);

        }
        
        if (INCREMENT == 1)
        {
            INCREMENT = 0;
            MIN_COUNT++;
            
            if (MIN_COUNT == 60)
            {
                INCREMENT = 1;
                MIN_COUNT = 0;
            }
            
            RA6 = !(MIN_COUNT & 0x01);
            RA5 = !((MIN_COUNT & 0x02) >> 1);
            RA3 = !((MIN_COUNT & 0x04) >> 2);
            RA2 = !((MIN_COUNT & 0x08) >> 3);
            RA1 = !((MIN_COUNT & 0x10) >> 4);
            RA0 = !((MIN_COUNT & 0x20) >> 5);
        }
        
        if (INCREMENT == 1)
        {
            INCREMENT = 0;
            HOUR_COUNT++;
            if (HOUR_COUNT == 24)
            {
                HOUR_COUNT = 0;
            }
            
            RC4 = !(HOUR_COUNT & 0x01);
            RC3 = !((HOUR_COUNT & 0x02) >> 1);
            RC2 = !((HOUR_COUNT & 0x04) >> 2);
            RC1 = !((HOUR_COUNT & 0x08) >> 3);
            RC0 = !((HOUR_COUNT & 0x10) >> 4);
        }
        
        if (RC6 == 1 && DEBOUNCE ==0)
        {
            if (DEBOUNCE == 0)
            {
                MIN_COUNT++;
                SEC_COUNT = 0;
                RB4 = !(SEC_COUNT & 0x01);
                RA6 = !(MIN_COUNT & 0x01);
                RA5 = !((MIN_COUNT & 0x02) >> 1);
                RA3 = !((MIN_COUNT & 0x04) >> 2);
                RA2 = !((MIN_COUNT & 0x08) >> 3);
                RA1 = !((MIN_COUNT & 0x10) >> 4);
                RA0 = !((MIN_COUNT & 0x20) >> 5);
                DEBOUNCE = 1;
            }
        }
        
        if (RC7 == 1 && DEBOUNCE ==0)
        {
            if (DEBOUNCE == 0)
            {
            HOUR_COUNT++;
            LATC4 = !(HOUR_COUNT & 0x01);
            LATC3 = !((HOUR_COUNT & 0x02) >> 1);
            RC2 = !((HOUR_COUNT & 0x04) >> 2);
            RC1 = !((HOUR_COUNT & 0x08) >> 3);
            RC0 = !((HOUR_COUNT & 0x10) >> 4);
            DEBOUNCE = 1;
            }
        }
        
        if (T0_PULSE == 1 && DEBOUNCE > 0)
        {
            DEBOUNCE++;
            T0_PULSE = 0;
        }
        
        if (DEBOUNCE >= 30)
        {
            DEBOUNCE =0;
        }
*/    
    }

}
