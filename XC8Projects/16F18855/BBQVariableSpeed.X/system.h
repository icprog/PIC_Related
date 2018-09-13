#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include "pin_manager.h"
#include <stdint.h>
#include "tmr2.h"
#include "menu.h"
#include "pwm.h"
#include "pid.h"
#include "lcd.h"
#include "adc.h"
#include "tempCalc.h"


#define _XTAL_FREQ  32000000         // Define clock freq for __delay_ms();


void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif