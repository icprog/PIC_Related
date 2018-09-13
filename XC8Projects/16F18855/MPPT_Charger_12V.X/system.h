#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include "adc.h"
#include "battery_charger.h"
#include "buttons.h"
#include "lcd.h"
#include "lead_acid_agm.h"
#include "pin_manager.h"
#include "pwm.h"
#include <stdint.h>
#include "tempCalc.h"
#include "tmr.h"

#define _XTAL_FREQ  32000000         // Define clock freq for __delay_ms();


void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif