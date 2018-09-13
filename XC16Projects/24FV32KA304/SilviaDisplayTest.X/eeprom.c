
// To Preserve EEProm Data through a Program Cycle, the Project Configuration needs the PICKit3 Conf Item "Preserve EEPROM Memory" Box checked!!!

#include "eeprom.h"

extern int __attribute__ ((space(eedata))) Settings[43];                        // Global variable located in EEPROM (created by the space()attribute

void eepromPutData(int offset, int data)                      //Used to Write a single 16 bit word to EEProm
{
    NVMCON = 0x4004;
    TBLPAG = __builtin_tblpage(&Settings);
    offset = __builtin_tbloffset(&Settings)+offset;
    
    __builtin_tblwtl(offset, data);
    
    asm volatile ("disi #5");
    
    __builtin_write_NVM();
    
    while(NVMCONbits.WR);    
}

int eepromGetData(int offset)                                 //Used to Read a single 16 bit word from EEProm
{
    TBLPAG = __builtin_tblpage(&Settings);
    offset = __builtin_tbloffset(&Settings) + offset;

    return __builtin_tblrdl(offset);
}