#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include "tmr0.h"

#define _XTAL_FREQ  250000

void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

void PIN_MANAGER_Initialize (void);

#endif