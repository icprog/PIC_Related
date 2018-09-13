/**
  @Generated MPLAB(c) Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FV32KA304
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

// Configuration bits: selected in the GUI

// FBS
#pragma config BWRP = OFF    // Boot Segment Write Protect->Disabled
#pragma config BSS = OFF    // Boot segment Protect->No boot program flash segment

// FGS
#pragma config GWRP = OFF    // General Segment Write Protect->General segment may be written
#pragma config GSS0 = OFF    // General Segment Code Protect->No Protection

// FOSCSEL
#pragma config FNOSC = FRCDIV    // Oscillator Select->8MHz FRC oscillator With Postscaler (FRCDIV)
#pragma config SOSCSRC = ANA    // SOSC Source Type->Analog Mode for use with crystal
#pragma config LPRCSEL = HP    // LPRC Oscillator Power and Accuracy->High Power, High Accuracy Mode
#pragma config IESO = ON    // Internal External Switch Over bit->Internal External Switchover mode enabled (Two-speed Start-up enabled)

// FOSC
#pragma config POSCMOD = NONE    // Primary Oscillator Configuration bits->Primary oscillator disabled
#pragma config OSCIOFNC = OFF    // CLKO Enable Configuration bit->CLKO output disabled
#pragma config POSCFREQ = HS    // Primary Oscillator Frequency Range Configuration bits->Primary oscillator/external clock input frequency greater than 8MHz
#pragma config SOSCSEL = SOSCHP    // SOSC Power Selection Configuration bits->Secondary Oscillator configured for high-power operation
#pragma config FCKSM = CSECMD    // Clock Switching and Monitor Selection->Clock Switching is enabled, Fail-safe Clock Monitor is disabled

// FWDT
#pragma config WDTPS = PS8192    // Watchdog Timer Postscale Select bits->1:8192
#pragma config FWPSA = PR128    // WDT Prescaler bit->WDT prescaler ratio of 1:128
#pragma config FWDTEN = ON    // Watchdog Timer Enable bits->WDT enabled in hardware
#pragma config WINDIS = OFF    // Windowed Watchdog Timer Disable bit->Standard WDT selected(windowed WDT disabled)

// FPOR
#pragma config BOREN = BOR3    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware, SBOREN bit disabled
#pragma config LVRCFG = OFF    // Low Voltage Regulator Configuration bit->Low Voltage regulator is not available
#pragma config PWRTEN = ON    // Power-up Timer Enable bit->PWRT enabled
#pragma config I2C1SEL = PRI    // Alternate I2C1 Pin Mapping bit->Use Default SCL1/SDA1 Pins For I2C1
#pragma config BORV = V20    // Brown-out Reset Voltage bits->Brown-out Reset set to lowest voltage (2.0V)
#pragma config MCLRE = ON    // MCLR Pin Enable bit->RA5 input pin disabled,MCLR pin enabled

// FICD
#pragma config ICS = PGx1    // ICD Pin Placement Select bits->EMUC/EMUD share PGC1/PGD1

// FDS
#pragma config DSWDTPS = DSWDTPSF    // Deep Sleep Watchdog Timer Postscale Select bits->1:2,147,483,648 (25.7 Days)
#pragma config DSWDTOSC = LPRC    // DSWDT Reference Clock Select bit->DSWDT uses Low Power RC Oscillator (LPRC)
#pragma config DSBOREN = ON    // Deep Sleep Zero-Power BOR Enable bit->Deep Sleep BOR enabled in Deep Sleep
#pragma config DSWDTEN = ON    // Deep Sleep Watchdog Timer Enable bit->DSWDT enabled

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    OSCILLATOR_Initialize();
    OC3_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // CF no clock failure; NOSC FRCDIV; SOSCEN enabled; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONL((uint8_t) (0x0702 & 0x00FF));
    // RCDIV FRC/2; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3100;
    // TUN Center frequency; 
    OSCTUN = 0x0000;
    // WDTO disabled; TRAPR disabled; SLEEP disabled; BOR disabled; DPSLP disabled; CM disabled; SWR disabled; SWDTEN disabled; EXTR disabled; POR disabled; SBOREN disabled; IDLE disabled; IOPUWR disabled; VREGS disabled; 
    RCON = 0x0000;
}

/**
 End of File
*/