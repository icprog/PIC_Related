#ifndef SYSTEM_H
#define	SYSTEM_H

#include    <xc.h> // include processor files - each processor file is guarded. 
#include    "pin_manager.h"
#include    <stdint.h>
#include    "interrupt_manager.h"
#include    "traps.h"
#include    "glcd.h"
#include    "pid.h"  



#define _XTAL_FREQ  32000000UL
#define FOSC        32000000UL
#define FCY         FOSC/2

#include <libpic30.h>                   // FOSC & FCY "MUST" be defined before including libPIC30H

void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif
