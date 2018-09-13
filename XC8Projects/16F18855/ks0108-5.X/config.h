#ifndef CONFIG_H
#define	CONFIG_H

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits (HFINTOSC (1MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = OFF      // Clock Switch Enable bit (The NOSC and NDIV bits cannot be changed by user software)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (FSCM timer disabled)

// CONFIG2
#pragma config MCLRE = OFF      // Master Clear Enable bit (MCLR pin function is port defined function)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out reset enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled, SWDTEN is ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config WRT = OFF        // UserNVM self-write protection bits (Write protection off)
#pragma config SCANE = available// Scanner Enable bit (Scanner module is available for use)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)

// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (Program Memory code protection disabled)
#pragma config CPD = OFF        // DataNVM code protection bit (Data EEPROM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "micro.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



/* Project Related MACROS*/
#define _XTAL_FREQ              1000000UL  /**< Micro Operating Frequency.*/
#define enable_global_int()     (GIE=1)     /**< Enable Global Interrupt.*/
#define disable_global_int()    (GIE=0)     /**< Disable Global Interrupt.*/

/**
 * @brief Software Version.
 *
 * Software Version Structure, to keep track of the Software Version.
 */
typedef struct _Version_s
{
  u8_t  major;    /**< Major Software Vesrion, not incremented generally.*/
  u8_t  minor;    /**< Minor Software Vesrion, incremented after release.*/
  u8_t  fix;      /**< Incremented after Minor Bug Fixing.*/
  u16_t build;    /**< Increase after every build.*/
} Version_s;

extern Version_s SoftVer;   /**< Software Versioning.*/
extern u8_t lcd_line[16];   /**< LCD Display Buffer.*/

/* Function Prototypes */
u32_t millis(void);
void Timer0_Init(void);
void Copy_RAM(u8_t *pSrc, u8_t *pDest, u8_t size);
#endif