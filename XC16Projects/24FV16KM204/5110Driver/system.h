#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        500000L
#define FCY             SYS_FREQ/4

//extern unsigned char spk_bit;
//extern unsigned char led_bit;
//extern unsigned char spk_enable,spk_enable2;
//extern unsigned int led_counter;

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

#endif
