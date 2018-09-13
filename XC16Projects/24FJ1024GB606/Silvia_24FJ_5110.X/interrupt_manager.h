#ifndef _INTERRUPT_MANAGER_H
#define _INTERRUPT_MANAGER_H

#include    "system.h"

void INTERRUPT_Initialize(void);

void __attribute__((__interrupt__,no_auto_psv)) _OC6Interrupt(void);

#endif