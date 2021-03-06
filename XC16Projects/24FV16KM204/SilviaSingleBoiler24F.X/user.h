#ifndef     USER_H
#define     USER_H

#include    <xc.h>                          // include processor files - each processor file is guarded.  
#include    "stdint.h"                      // Includes uint16_t definition
//#include <stdbool.h>                      // Includes true/false definition
//#include <stdlib.h>
#include    "system.h"                      // Needed to calculate __delay_() Functions
#include    "touch.h"
#include    "lcd.h"
#include    "adc.h"

// ***************************************************************************************************************************************************************
void heartBeat(void);
//***************************************************************************************************************************************************************
//void levelCalc(void);
//***************************************************************************************************************************************************************
int TempCalc(int a);
//***************************************************************************************************************************************************************
int TempSetpoint(int b);
//***************************************************************************************************************************************************************
unsigned char SetDeadband(unsigned char b);
//***************************************************************************************************************************************************************
int SetGain(int b);
//***************************************************************************************************************************************************************
int SetIntegral(int b);
//***************************************************************************************************************************************************************
char SetDerivative(char b);
//***************************************************************************************************************************************************************

#endif
