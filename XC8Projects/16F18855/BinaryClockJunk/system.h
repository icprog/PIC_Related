#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "tmr0.h"

#define _XTAL_FREQ  1000000

void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif


