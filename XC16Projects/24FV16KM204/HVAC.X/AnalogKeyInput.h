
// This is a guard condition so that contents of this file are not included
// more than once.  

#ifndef ANALOGKEYINPUT_H
#define	ANALOGKEYINPUT_H

#include <xc.h>                     // include processor files - each processor file is guarded.  
#include "user.h"                   // Included to use ADC functionality
//***************************************************************************************************************************************************************

#define KEY_RIGHT	1
#define KEY_LEFT	2
#define KEY_ENTER	3
#define KEY_UP      4
#define KEY_DOWN    5
#define KEY_MENU    6
//#define KEY_CANCEL	7
#define KEY_NONE	9

//#define TRUE        1
//#define FALSE       0
//***************************************************************************************************************************************************************

char MenuRead(void);
//***************************************************************************************************************************************************************

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif