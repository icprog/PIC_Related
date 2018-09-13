#ifndef USER_H
#define	USER_H
/******************************************************************************/
#include <xc.h>
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>

void LCDWrite(unsigned char data_or_command, unsigned char data);
void gotoXY(int x, int y);
void LCDBitmap(char my_array[]);
void LCDCharacter(char character);
void LCDString(char *characters);
void LCDClear(void);
void LCDInit(void) ;

void InitApp(void);         /* I/O and Peripheral Initialization */

#endif
