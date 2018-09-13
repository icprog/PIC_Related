#ifndef TOUCH_H
#define TOUCH_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "adc.h"                   // Included to use ADC functionality
//***************************************************************************************************************************************************************
#define KEY_RESET       0
#define KEY_RIGHT   	1
#define KEY_LEFT        2
#define KEY_ENTER       3
#define KEY_UP          4
#define KEY_DOWN        5
#define KEY_MENU        6
#define KEY_SET_TIME    7
#define KEY_START_STOP  8
#define KEY_NONE        9

char menuRead(void);

#endif