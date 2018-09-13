/* 
 * File:   main.c
 * Author: DAVE
 *
 * Created on February 9, 2015, 11:53 PM
 */
// PIC24FV16KM204 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include <i2c.h>

// FBS
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot program flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Write Protect (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRCDIV           // Oscillator Select (8MHz FRC oscillator With Postscaler (FRCDIV))
#pragma config SOSCSRC = ANA            // SOSC Source Type (Analog Mode for use with crystal)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = ON                // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-speed Start-up enabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = IO            // CLKO Enable Configuration bit (Port I/O enabled (CLKO disabled))
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bits (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR0             // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware, SBOREN bit disabled)
#pragma config RETCFG = OFF             //  (Retention regulator is not available)
#pragma config PWRTEN = OFF             // Power-up Timer Enable bit (PWRT disabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Use Default SCL1/SDA1 Pins For I2C1)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (RA5 input pin disabled, MCLR pin enabled)

// FICD
#pragma config ICS = PGx1               // ICD Pin Placement Select bits (EMUC/EMUD share PGC1/PGD1)

#include <stdio.h>
#include <stdlib.h>



// Configuration bits for PIC18F452 chip with a 10MHz crystal. It sets the following configuration:
// Debug OFF, Oscillator in HS mode with PLL enabled (40Mhz clock), Watchdog timer off, Extended CPU mode off
//#pragma config OSC = HSPLL  //HS with 4 x PLL enabled - clock is speed of crystal x 4
//#pragma config WDT = OFF    //Watchdog timer can be enabled in software with SWDTEN bit
//#pragma config LVP = OFF   	//Low voltage programming disabled

//External functions, and function prototypes
unsigned char lcdPutRomString(unsigned char lcdAdr, const char* s);

//Defines
#define LCD2S_I2C_ADR 80    /* Default LCD I2C address when both switches on back of LCD2S board are set to 0 */

void delay (unsigned long dly)
{
  unsigned long i;
  for (i = 0; i < dly; i++);
}

int main ()
{
//    unsigned char i;

    /////////////////////////////////////////////////
    //Configure SSP Peripheral for I2C Master mode
    //Set port B6 as an output
//    TRISBbits.TRISB6 = 0;

    //RC3 (I2C clock) and RC4 (I2C data) a configured as inputs at this stage
    TRISC |= 0b00011000;

    //Delay at while before writing to LCD display
    delay(200000ul);

    //0xxx xxxx = Slew rate off, for high speed mode (400 kHz)
    //x0xx xxxx = Disable SMBus specific inputs
    SSP1STAT &= 0x3F;        // power on state, and clear bits 6 and 7

    //xx0x xxxx = SSPEN, Disable SSP
    //xxxx 1000 = I2C Master mode, clock = FOSC / (4 * (SSPADD+1))
    SSP1CON1 = 0x08;

    SSP1CON2 = 0x00;         // power on state
    SSP1CON1bits.SSPEN = 1;  //Enable SSP module, and configure port pins as serial port pins
    SSP1ADD = 24;            //Set Baud rate to 400,000. SSPADD = ( ((40,000,000/400,000) / 4) - 1 ) = 24


    /////////////////////////////////////////////////
    //Send "Hello World" string. Sring is contained in ROM memory
    if (lcdPutRomString(LCD2S_I2C_ADR, "\fhello\nworld") == 1) {
        //An error will be returned if there is no LCD display on I2C bus for example
        //...... Handle Error!!!!!
    }

    while (1)
    { 
        /* ....... Main Program ...... */
    }
    return 0;
}

/** Waits until the I2C bus is IDLE, and available to be used. */
#define i2cWaitForIdle()    while ((SSP1CON2 & 0x1F) | (SSP1STATbits.R_W))

/** Generate bus start condition, and waits until it is finished */
#define i2cPutStartAndWait()  {SSP1CON2bits.SEN=1; while ( SSP1CON2bits.SEN );}

/** Generate bus stop condition, and waits until it is finished */
#define i2cPutStopAndWait()  {SSP1CON2bits.PEN=1; while(SSP1CON2bits.PEN);}

/** Tests if an ACK was received from the slave. Returns true if it was, else false. */
#define i2cWasAckReceived() (!SSP1CON2bits.ACKSTAT)

/**
 * This routine writes a single byte to the I2C bus,
 * and waits until the bus is idle before returning.
 *
 * @param data_out  Single data byte for I2C bus
 *
 * @return      Status byte for WCOL detection.  Returns 0 if OK, else 1 if error
 */
unsigned char i2cPutByteAndWait(unsigned char data_out) {
    SSP1BUF = data_out;          // write single byte to SSPBUF
    if ( SSP1CON1bits.WCOL ) {       // test if write collision occurred
        return ( 1 );           // if WCOL bit is set return negative #
    }

    while( SSP1STATbits.BF );        // wait until write cycle is complete

    i2cWaitForIdle();           // wait until bus goes idle

    return ( 0 );               // if WCOL bit is not set return non-negative #
}

unsigned char lcdPutRomString(unsigned char lcdAdr, const char* s) {
//unsigned char lcdPutRomString(unsigned char lcdAdr, const char* s) {


    //    unsigned char i = 0;
    char c;
    char* p;

    i2cWaitForIdle();

    i2cPutStartAndWait();       //Write I2C Start Condition, and wait for it to complete

    //Write module address
    i2cPutByteAndWait(lcdAdr);

    //Only continue if slave sent ACK. If no slave present, no ACK is sent. If no slave with address sent is present, no ACK is sent.
    if(i2cWasAckReceived()==0) {
        i2cPutStopAndWait();    //Reset I2C bus
        return 1;               //Error
    }

    //Write "Write Parsed String" command
    i2cPutByteAndWait(0x80);

    p = s;
    while((c = *p++)) {
        //Write next character to LCD display
        i2cPutByteAndWait(c);
    }

    i2cPutStopAndWait();    //Write I2C Stop condition, and wait for it to complete

    return 0;   //OK
}

