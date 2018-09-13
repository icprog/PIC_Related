#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        32000L
#define _XTAL_FREQ      32000
#define FCY             SYS_FREQ/4


void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

#endif
