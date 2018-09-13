#ifndef SYSTEM_H
#define	SYSTEM_H

#include    <xc.h>

#include    <stdint.h>        /* For uint8_t definition */
#include    <stdbool.h>       /* For true/false definition */
#include    "adcc.h"
#include    "buttons.h"
#include    "lcd.h"


/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        1000000L
#define _XTAL_FREQ      1000000L
#define FCY             SYS_FREQ/4

void Init(void);

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

#endif
