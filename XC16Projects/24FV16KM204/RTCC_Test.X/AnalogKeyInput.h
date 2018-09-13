
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ANALOGKEYINPUT_H
#define	ANALOGKEYINPUT_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define KEY_LEFT	1
#define KEY_RIGHT	2
#define KEY_ENTER	3
#define KEY_UP      4
#define KEY_DOWN    5
#define KEY_CANCEL	6
#define KEY_MENU    7
#define KEY_NONE	99

#define PRESSED		0
#define RELEASED	1


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif