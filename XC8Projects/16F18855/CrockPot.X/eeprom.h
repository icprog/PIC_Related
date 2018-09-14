#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded.  

void eepromPutData(unsigned int offset, unsigned int data);

unsigned int eepromGetData(unsigned int offset);

#endif