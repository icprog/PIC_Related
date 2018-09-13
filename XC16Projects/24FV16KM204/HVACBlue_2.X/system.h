#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include "adc.h"
#include "eeprom.h"
#include "lcd.h"
#include "rtcc.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "touch.h"
#include "user.h"

#define SYS_FREQ        4000000L
#define FCY             SYS_FREQ/2
#define _XTAL_FREQ      4000000


//********** Add the following to solve __delay_ms() issues in XC16 ************
#include <libpic30.h>   
//******************************************************************************


void ConfigureOscillator(void);     /* Handles clock switching/osc initialization */
//***************************************************************************************************************************************************************

void InitApp(void);                 /* I/O and Peripheral Initialization */
//***************************************************************************************************************************************************************

#endif