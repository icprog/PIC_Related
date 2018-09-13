#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "pin_manager.h"
#include "pwm.h"
#include "tmr2.h"
#include "lcd.h"
#include "adc.h"


#define _XTAL_FREQ  1000000         // Define clock freq for __delay_ms();


void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif