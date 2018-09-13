#ifndef SYSTEM_H
#define	SYSTEM_H

#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/2  // Microcontroller MIPs (FCY)
#define _XTAL_FREQ      8000000

#include <xc.h>
//********** Add the following to solve __delay_ms() issues in XC16 ************
#include <libpic30.h>   
//******************************************************************************
#include <stdint.h>          /* For uint32_t definition */
//#include <stdbool.h>         /* For true/false definition */
    

void ConfigureOscillator(void);     /* Handles clock switching/osc initialization */
//***************************************************************************************************************************************************************
void InitApp(void);                 /* I/O and Peripheral Initialization */
//***************************************************************************************************************************************************************
#endif