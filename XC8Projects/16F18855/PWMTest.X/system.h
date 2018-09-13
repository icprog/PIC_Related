#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include "pwm6.h"
#include "tmr2.h"
#include "lcd.h"
#include "adcc.h"

#define _XTAL_FREQ      1000000
#define SYS_FREQ        1000000L
#define FCY             SYS_FREQ/4

//#define _XTAL_FREQ  7750
//#define SYS_FREQ        7750
//#define FCY             SYS_FREQ/4

// Add the following to solve __delay_ms() issues in XC8

//#define delay_us(x) _delay((unsigned long)((x)*(SYS_FREQ/1000000.0)))
//#define delay_ms(x) _delay((unsigned long)((x)*(SYS_FREQ/1000.0)))


/* @Description
    Initializes the device to the default states configured in the MCC GUI
 * @Example
    SYSTEM_Initialize(void);
 */
void SYSTEM_Initialize(void);

/* @Description
    Initializes the oscillator to the default states configured in the MCC GUI
 * @Example
    OSCILLATOR_Initialize(void);
 */
void OSCILLATOR_Initialize(void);


#endif