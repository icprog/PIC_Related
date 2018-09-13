/* 
 * File:   feeprom.h
 * Author: David McCurley
 *
 * Created on February 15, 2013, 11:24 AM
 */

#ifndef FEPROM_H
#define	FEPROM_H

#include "system.h"

//#include <GenericTypeDefs.h>

//--------------------Constants--------------------
#if defined(__PIC24F__)
	#define ERASE               0x4042
	#define PROGRAM_ROW         0x4001
	#define PROGRAM_WORD        0x4003
#endif

//--------------------Variables--------------------
extern int EEoptions[];

//--------------------Functions--------------------
extern void EraseEprom(void);
extern void WriteEprom(void);
extern void ReadEprom(void);
extern void SaveEprom(void);

//-------------------Macros-------------------

#endif	/* FEPROM_H */

