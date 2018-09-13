// To Preserve EEProm Data through a Program Cycle, the Project Configuration needs the PICKit3 Conf Item "Preserve EEPROM Memory" Box checked!!!
#ifndef EEPROM_H
#define	EEPROM_H

#include    "system.h"

void eepromPutData(int offset, int data);

int eepromGetData(int offset);

#endif