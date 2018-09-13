// To Preserve EEProm Data through a Program Cycle, the Project Configuration needs the PICKit3 Conf Item "Preserve EEPROM Memory" Box checked!!!
#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded.  

void eepromPutData(int offset, int data);

int eepromGetData(int offset);

#endif