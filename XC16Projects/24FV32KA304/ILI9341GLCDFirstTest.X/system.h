#ifndef SYSTEM_H
#define	SYSTEM_H


#define SYS_FREQ        8000000L    // Not sure why, actual clock is 2MHz    
#define FCY             SYS_FREQ/2  // Microcontroller MIPs (FCY)
//#define _XTAL_FREQ      8000000   // Only required with XC8 Compilers

#include <xc.h>

//********** Add the following to solve __delay_ms() issues in XC16 ************
#include <libpic30.h>   
//******************************************************************************
    


void Init(void);

#endif