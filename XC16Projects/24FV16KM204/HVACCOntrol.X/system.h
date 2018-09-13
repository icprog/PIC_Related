/* 
 * File:   system.h
 * Author: DAVE
 *
 * Created on May 16, 2015, 1:28 AM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define _XTAL_FREQ  4000000
#define SYS_FREQ        4000000L
#define FCY             SYS_FREQ/2
//#define _XTAL_FREQ 8000000


//********** Add the following to solve __delay_ms() issues in XC16 ************
#include <libpic30.h>   
//******************************************************************************


/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void);     /* Handles clock switching/osc initialization */

void InitApp(void);                 /* I/O and Peripheral Initialization */



#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

