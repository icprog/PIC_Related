// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef KEYPAD_H
#define	KEYPAD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdio.h>

/********************************************************************

Keypad library for five way navigation, menu, and cancel key.
[MENU] [LEFT] [RIGHT] [UP] [DOWN] [ENTER] [CANCEL]

 * Features:
	Automatic 80 FPS scanning using TIMER0
	3 point major polling for complete noise free operation
	Fully debounced.
	Automatic buffering of commands (no missed key press!)
	Automatic repeat when user presses and hold a key.  
********************************************************************/

/******************************************************************************
Simple HAL (Hardware Abstraction Layer) for a standard 2 direction + 1 center
DPAD (directional key pad).
******************************************************************************/

#define KEY_LEFT	1
#define KEY_RIGHT	2
#define KEY_ENTER	3
#define KEY_CANCEL	4
#define KEY_UP      5
#define KEY_DOWN    6
#define KEY_MENU    7
#define KEY_NONE	99

#define PRESSED		0
#define RELEASED	1

#define KEYPAD_QMAX 32  //Queue

void KeypadInit();

uint8_t GetRawKeyState(uint8_t KeyCode);

uint8_t MajorVote(uint8_t keycode);

uint8_t GetKeypadCmd(char wait);

#endif

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif