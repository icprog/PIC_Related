#ifndef SYSTEM_H
#define	SYSTEM_H

#include    <xc.h>
#include    "rtcc.h"
#include    "pin_manager.h"
#include    <stdint.h>
#include    <stdbool.h>
#include    "interrupt_manager.h"
#include    "traps.h"
#include    "glcd.h"
#include    "pid.h"  
#include    "adc.h"
#include    "touch.h"
#include    "pwm.h"
#include    "start_stop_timer.h"
#include    "traps.h"
#include    "user.h"


#define _XTAL_FREQ  8000000UL
#define FOSC        8000000UL
#define FCY         FOSC/2

#include <libpic30.h>                   // FOSC & FCY "MUST" be defined before including libPIC30H

void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif
