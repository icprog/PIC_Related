#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include "pin_manager.h"
#include <stdint.h>
#include "pwm6.h"
#include "timers.h"
#include "lcd.h"
#include "adcc.h"
#include "pid.h"
#include "buttons.h"


#define _XTAL_FREQ  1000000         // Define clock freq for __delay_ms();


void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif