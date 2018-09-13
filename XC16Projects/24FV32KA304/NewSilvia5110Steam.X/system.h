#ifndef SYSTEM_H
#define	SYSTEM_H

#define SYS_FREQ        8000000L    // Not sure why, actual clock is 2MHz    
#define FCY             SYS_FREQ/2  // Microcontroller MIPs (FCY)

#include <xc.h>
#include <stdint.h>          
#include <stdbool.h>        

#include "lcd.h"                                // Graphical LCD Driver functionality
#include "user.h"                               // User Functions (Setting Setpoints, DeadBands, etc...)
#include "buttons.h"
#include "rtcc.h"                               // Real Time clock & Calendar Functions
#include "eeprom.h"
#include "adc.h"
#include "pid.h"
#include "level.h"
#include "pwm.h"
#include "tempcalc.h"
#include "usermenu.h"


//********** Add the following to solve __delay_ms() issues in XC16 ************
#include <libpic30.h>   
//******************************************************************************

//void ConfigureOscillator(void);    
//***************************************************************************************************************************************************************
void InitApp(void);                
//***************************************************************************************************************************************************************
#endif