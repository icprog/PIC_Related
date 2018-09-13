
// FBS
#pragma config BSS = OFF    // Boot segment Protect->No boot program flash segment
#pragma config BWRP = OFF    // Boot Segment Write Protect->Disabled

// FGS
#pragma config GWRP = OFF    // General Segment Write Protect->General segment may be written
#pragma config GCP = OFF    // General Segment Code Protect->No Protection

// FOSCSEL
#pragma config LPRCSEL = HP    // LPRC Oscillator Power and Accuracy->High Power, High Accuracy Mode
#pragma config IESO = ON    // Internal External Switch Over bit->Internal External Switchover mode enabled (Two-speed Start-up enabled)
#pragma config FNOSC = FRCDIV    // Oscillator Select->8MHz FRC oscillator With Postscaler (FRCDIV)
#pragma config SOSCSRC = ANA    // SOSC Source Type->Analog Mode for use with crystal

// FOSC
#pragma config POSCFREQ = HS    // Primary Oscillator Frequency Range Configuration bits->Primary oscillator/external clock input frequency greater than 8MHz
#pragma config POSCMOD = NONE    // Primary Oscillator Configuration bits->Primary oscillator disabled
#pragma config SOSCSEL = SOSCHP    // SOSC Power Selection Configuration bits->Secondary Oscillator configured for high-power operation
#pragma config OSCIOFNC = IO    // CLKO Enable Configuration bit->Port I/O enabled (CLKO disabled)
#pragma config FCKSM = CSECMD    // Clock Switching and Monitor Selection->Clock Switching is enabled, Fail-safe Clock Monitor is disabled

// FWDT
#pragma config WDTPS = PS32768    // Watchdog Timer Postscale Select bits->1:32768
#pragma config FWPSA = PR128    // WDT Prescaler bit->WDT prescaler ratio of 1:128
#pragma config WINDIS = OFF    // Windowed Watchdog Timer Disable bit->Standard WDT selected(windowed WDT disabled)
#pragma config FWDTEN = OFF    // Watchdog Timer Enable bits->WDT disabled in hardware; SWDTEN bit disabled

// FPOR
#pragma config I2C1SEL = PRI    // Alternate I2C1 Pin Mapping bit->Use Default SCL1/SDA1 Pins For I2C1
#pragma config BOREN = BOR3    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware, SBOREN bit disabled
#pragma config RETCFG = OFF    // ->Retention regulator is not available
#pragma config MCLRE = ON    // MCLR Pin Enable bit->RA5 input pin disabled, MCLR pin enabled
#pragma config BORV = V18    // Brown-out Reset Voltage bits->Brown-out Reset set to lowest voltage (1.8V)
#pragma config PWRTEN = ON    // Power-up Timer Enable bit->PWRT enabled

// FICD
#pragma config ICS = PGx1    // ICD Pin Placement Select bits->EMUC/EMUD share PGC1/PGD1
