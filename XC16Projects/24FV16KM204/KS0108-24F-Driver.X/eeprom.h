// To Preserve EEProm Data through a Program Cycle, the Project Configuration needs the PICKit3 Conf Item "Preserve EEPROM Memory" Box checked!!!
#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded.  

void eepromPutData(unsigned int offset, unsigned int data);

unsigned int eepromGetData(unsigned int offset);

#endif