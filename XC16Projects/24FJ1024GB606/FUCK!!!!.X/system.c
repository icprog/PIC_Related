
// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Boot Segment Flash page address  limit)

// FSIGN

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Source Selection (Internal Fast RC (FRC))
#pragma config PLLMODE = DISABLED       // PLL Mode Selection (No PLL used; PLLEN bit is not available)
#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFCN = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config SOSCSEL = ON             // SOSC Power Selection Configuration bits (SOSC is used in crystal (SOSCI/SOSCO) mode)
#pragma config PLLSS = PLL_PRI          // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration bit (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler bits (1:32,768)
#pragma config FWPSA = PR128            // Watchdog Timer Prescaler bit (1:128)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bits (WDT Enabled)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config WDTCMX = WDTCLK          // WDT MUX Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)

// FPOR
#pragma config BOREN = ON               // Brown Out Enable bit (Brown Out Enable Bit)
#pragma config LPCFG = OFF              // Low power regulator control (No Retention Sleep)
#pragma config DNVPEN = ENABLE          // Downside Voltage Protection Enable bit (Downside protection enabled using ZPBOR when BOR is inactive)

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config BTSWP = OFF              // BOOTSWP Disable (BOOTSWP instruction disabled)

// FDEVOPT1
#pragma config ALTCMPI = DISABLE        // Alternate Comparator Input Enable bit (C1INC, C2INC, and C3INC are on their standard pin locations)
#pragma config TMPRPIN = OFF            // Tamper Pin Enable bit (TMPRN pin function is disabled)
#pragma config SOSCHP = OFF             // SOSC High Power Enable bit (valid only when SOSCSEL = 1 (Enable SOSC low power mode)
#pragma config ALTVREF = ALTVREFDIS     // Alternate Voltage Reference Location Enable bit (VREF+ and CVREF+ on RB0, VREF- and CVREF- on RB1)
/*
// FSEC
#pragma config BWRP =       OFF             // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS =        DISABLED        // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN =       OFF             // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP =       OFF             // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS =        DISABLED        // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP =       OFF             // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS =        DISABLED        // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS =    OFF             // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM =      0x1FFF          // Boot Segment Flash Page Address Limit bits (Boot Segment Flash page address  limit)

// FSIGN

// FOSCSEL
#pragma config FNOSC =      FRCPLL          // Oscillator Source Selection (Fast RC Oscillator with divide-by-N with PLL module (FRCPLL) )
#pragma config PLLMODE =    DISABLED        // PLL Mode Selection (No PLL used; PLLEN bit is not available)
#pragma config IESO =       ON              // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMOD =    NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFCN =   OFF             // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config SOSCSEL =    ON              // SOSC Power Selection Configuration bits (SOSC is used in crystal (SOSCI/SOSCO) mode)
#pragma config PLLSS =      PLL_PRI         // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config IOL1WAY =    ON              // Peripheral pin select configuration bit (Allow only one reconfiguration)
#pragma config FCKSM =      CSDCMD          // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS =      PS32768         // Watchdog Timer Postscaler bits (1:32,768)
#pragma config FWPSA =      PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config FWDTEN =     OFF             // Watchdog Timer Enable bits (WDT and SWDTEN disabled)
#pragma config WINDIS =     OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config WDTWIN =     PS25_0          // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config WDTCMX =     WDTCLK          // WDT MUX Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config WDTCLK =     LPRC            // WDT Clock Source Select bits (WDT uses LPRC)

// FPOR
#pragma config BOREN =      ON              // Brown Out Enable bit (Brown Out Enable Bit)
#pragma config LPCFG =      OFF             // Low power regulator control (No Retention Sleep)
#pragma config DNVPEN =     ENABLE          // Downside Voltage Protection Enable bit (Downside protection enabled using ZPBOR when BOR is inactive)

// FICD
#pragma config ICS =        PGD1            // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN =     OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config BTSWP =      OFF             // BOOTSWP Disable (BOOTSWP instruction disabled)

// FDEVOPT1
#pragma config ALTCMPI =    DISABLE         // Alternate Comparator Input Enable bit (C1INC, C2INC, and C3INC are on their standard pin locations)
#pragma config TMPRPIN =    OFF             // Tamper Pin Enable bit (TMPRN pin function is disabled)
#pragma config SOSCHP =     ON              // SOSC High Power Enable bit (valid only when SOSCSEL = 1 (Enable SOSC high power mode (default))
#pragma config ALTVREF =    ALTVREFDIS      // Alternate Voltage Reference Location Enable bit (VREF+ and CVREF+ on RA10, VREF- and CVREF- on RA9)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
*/


#include "system.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
//    ADCInit();
//    INTERRUPT_Initialize();
  //  RTCC_Initialize();
    void InitializeTimers(void);
    void Initialize_PWM(void);
    LCDInit();
    __delay_ms(100);
    LCDClear();
}

void OSCILLATOR_Initialize(void)
{
    __builtin_write_OSCCONL((uint8_t) (0x0102 & 0x00FF)); // CF no clock failure; NOSC FRCPLL; SOSCEN enabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 

    CLKDIV      = 0x3020;   // CPDIV 1:1; PLLEN enabled; DOZE 1:8; RCDIV FRC; DOZEN disabled; ROI disabled; 

    OSCTUN      = 0x0000;   // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 

    REFOCONL    = 0x0000;   // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 

    REFOCONH    = 0x0000;   // RODIV 0; 

    REFOTRIML   = 0x0000;   // ROTRIM 0; 

    DCOTUN      = 0x0000;   // DCOTUN 0; 

    DCOCON      = 0x0700;   // DCOFSEL 8; DCOEN disabled; 

    OSCDIV      = 0x0000;   // DIV 0; 

    OSCFDIV     = 0x0000;   // TRIM 0; 
}

    void InitializeTimers(void)
    {
        T1CONbits.TON =     0;                          // Timer1 is used for generating PWM frequency
        T1CONbits.TCS =     1;                          // Timer Clock source selected by T1ECS
        T1CONbits.T1ECS =   0x0;                        // Timer 1 Extended Clock Selection bits (00 = Secondary Oscillator)
        T1CONbits.TCKPS =   0x1;                        // Timer 1 input clock pre-scale bits 01 = 1:8 
        TMR1 =              0x0000;                     // Timer 1 preset value??
        PR1 =               0x03FF;                     // Timer 1 Period value of .25 Seconds for a Frequency of 4Hz
        T1CONbits.TON =     1;                          // TIMER 1 ON
        T2CONbits.TON =     0;                          // Turn Timer OFF
        PR2 =               0x2000;                     // Period value set in Timer 2, to make it so Timer 2 rolls over every 1/100th seconds
        T2CONbits.TON =     1;                          // Turn Timer 2 ON
    }
// *****************************************************************************

void Initialize_PWM(void)
{
//    OC5CON2bits.OCTRIS  =   0;
    OC5R =                  0x0000;                 // Set On time (Duty Clcle))
    OC5RS =                 0x2000;                 // Set Period for Edge aligned PWM
    OC5CON2bits.SYNCSEL =   0X1F;                   // Set Timer 1 as Sync source
    OC5CON2bits.OCTRIG =    0;                      // Set OC3 as Sync source
    OC5CON1bits.OCTSEL =    0;                    // Set Timer 2 as clock source
//    OC5TMR =                0x0000;                 // Set OC3 timer to zero
    OC5CON1bits.OCM =       0x6;                    // Set OC3 Mode to Edge aligned PWM (Center aligned works as well, except it is on until OCxR, turns off until OCxRS, so, 
}                                                   // dutyCycle of zero turns ON OC, until it hits OCxRS (works fine down to dC of 1, then goes to pulsing mode)
// *****************************************************************************
void setDutyCycle(unsigned int dutyCycle)
{
    OC5R = dutyCycle;                              
}

/*void InitializeTimers(void)
{
    T1CONbits.TON =     0;                          // Timer1 is used for generating PWM frequency
    T1CONbits.TCS =     1;                          // Timer Clock source selected by T1ECS
    T1CONbits.T1ECS =   0x0;                        // Timer 1 Extended Clock Selection bits (00 = Secondary Oscillator)
    T1CONbits.TCKPS =   0x1;                        // Timer 1 input clock pre-scale bits 01 = 1:8 
    TMR1 =              0x0000;                     // Timer 1 preset value??
    PR1 =               0x03FF;                     // Timer 1 Period value of .25 Seconds for a Frequency of 4Hz

    T2CON   =           0x0000;
    T2CONbits.TON =     0;                          // Turn Timer OFF
    PR2 =               0x4D30;                     // Period value set in Timer 2, to make it so Timer 2 rolls over every 1/100th seconds

    IFS0bits.T1IF =     0; 
    IFS0bits.T2IF =     0;
    IEC0bits.T1IE =     1;
    IEC0bits.T2IE =     1;

    T1CONbits.TON =     1;                          // TIMER 1 ON
    T2CONbits.TON =     1;                          // Turn Timer 2 ON
}
// *****************************************************************************
*/