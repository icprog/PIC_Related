#ifndef SYSTEM_H
#define	SYSTEM_H

#include    <xc.h>
#include    <stdint.h>                  // Must be included before lcd.h, so lcd.h can use functionality by including system.h
#include    <stdbool.h>
#include    <time.h>
#include    "pin_manager.h"
//#include    "adc.h"
//#include    "buttons.h"
#include    "lcd.h"
//#include    "pid.h"  
//#include    "pwm.h"
//#include    "rtcc.h"
//#include    "start_stop_timer.h"
//#include    "user.h"
//#include    "interrupt_manager.h"
//#include    "traps.h"


#define _XTAL_FREQ  8000000UL
#define FOSC        8000000UL
#define FCY         FOSC/2

#include <libpic30.h>                       // FOSC & FCY "MUST" be defined before including libPIC30H

void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

void InitializeTimers(void);

void Initialize_PWM(void);

void setDutyCycle(unsigned int dutyCycle);

#endif
