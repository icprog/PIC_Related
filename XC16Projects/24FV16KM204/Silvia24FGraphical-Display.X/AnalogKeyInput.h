
// This is a guard condition so that contents of this file are not included
// more than once.  

#ifndef ANALOGKEYINPUT_H
#define	ANALOGKEYINPUT_H

#include <xc.h>                     // include processor files - each processor file is guarded.  
//***************************************************************************************************************************************************************

#define SWITCH_NONE             0
#define SWITCH_STEAM_SWITCH     1
#define SWITCH_BREW_SWITCH      2
#define SWITCH_WATER_SWITCH     3

//***************************************************************************************************************************************************************

char switchStateRead(void);
//***************************************************************************************************************************************************************


#endif