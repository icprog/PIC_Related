//----------------------------------------------------------
// File:		feprom.c
// Author:		David McCurley
// Company:		Microframe Corp www.microframecorp.com
// Created:		2013 Feb 15
// Rev:			1.0
// IDE:			MPLAB X v1.41
// Compiler:	XC16
// Processor:	PIC24FJ128GA010 (likely any PIC24F)
// Hardware:	Explorer 16 Demo board
//
// Summary: Emulates an EEPROM in program flash for saving
//  basic settings.
// Additional reading:
//  AN1095 (Enhanced EEPROM emulator)
//  PIC24FJ128GA010 Family Data Sheet,
//    section 4.0(Flash Program Memory)
//----------------------------------------------------------
// 2013 Feb 19 David McCurley r1.0
//	Tested and finalized module.
//  Improvements: make a struct/union to map strings to save
//  to EEoptions.
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <p24Fxxxx.h>
#include "feprom.h"

//--------------------ROM Allocation------------------------
//*Alignment*
//Flash blocks consist of 512 instructions.  Each instruction consists of 3 bytes, for a total of 1536 bytes.
//Addressing is done by WORD, so each instruction takes two words (high byte is ignored).
//0x400 Instruction 1 WORD
//0x401 Instruction 1 BYTE (high byte does not exist)
//0x402 Instruction 2 WORD
//0x403 Instruction 2 BYTE
//0x800 Instruction 513 WORD (New block boundary)
//Thus each block covers an address space of 1024 (2048 theoretical bytes)

//Attributes:
//  space(psv) = Alloc var in prog space, in a section designated for program space visibility window access
//  aligned(1024) = align memory position to a flash block
//  noload = do not init space (see fillupper)
//  section = name the section rather than a random compiler name
//  address = position the EEPROM in a section of ROM that will be consistent.
//            This is not critical unless a bootloader is used.
//#if defined(__PIC24FJ128GA010__)
//unsigned char emulationPages[1024]
  //  __attribute__ ((space(psv), aligned(1024), noload, section(".FlashEeprom"), address(0x15000)));//128K dev
//#elif defined(__PIC24FJ256GA110__)
unsigned char emulationPages[1024]
__attribute__ ((space(psv), aligned(1024), noload, section(".FlashEprom"), address(0x2A400)));//256K dev
//#endif
//--------------------ROM Allocation------------------------

//-------------------Global Variables-----------------------
int EEoptions[8*64*3];			//RAM copy of our options. 3 bytes per inst, 64 inst per row, 8 rows per block.
//-------------------Global Variables-----------------------

//------------------Function Prototype----------------------
void EraseEprom(void);
void WriteEprom(void);
void ReadEprom(void);
void SaveEprom(void);
//------------------Function Prototype----------------------

void EraseEprom(void)
{
	unsigned int savedTBLPAG;
	unsigned int pOffset;

	savedTBLPAG = TBLPAG;									//Save the table page

	TBLPAG = __builtin_tblpage(&emulationPages);
	pOffset = __builtin_tbloffset(&emulationPages);

	NVMCON = ERASE;	//Set up for a block erase - the entire block will be erased! 1024 addr (1024 /2 *3 = 1536 bytes)
	__builtin_tblwtl(pOffset, 0x0000);						//Set base address of erase block with dummy latch write

	asm("DISI #5");//Block all ints with priority<7 for next 5 instructions (call below is 7 instructions)
	__builtin_write_NVM();									//Perform write sequence requested in NVMCON

	//Clean up
	NVMCON = 0x0000;										//Clear flash control register
	TBLPAG = savedTBLPAG;									//Restore the table page
}

void WriteEprom(void)
{
	unsigned int savedTBLPAG;
	unsigned int pOffset;
	unsigned int i, j;
	unsigned int uiData;
	unsigned int uiIdx;

	savedTBLPAG = TBLPAG;									//Save the table page

	TBLPAG = __builtin_tblpage(&emulationPages);
	pOffset = __builtin_tbloffset(&emulationPages);

	//We will program one row at a time (64instr * 3 = 192 bytes)
	NVMCON = PROGRAM_ROW;

	//Load holding latches
	//Note: make sure all unused latches are written with 0xFFFFFF, otherwise they may write to the wrong row
	// What this means: when writing a row using tblwth/tblwtl, you must write to all 64 addresses
	//For easier coding, just make EEoptions a multiple of the row size (64*3=192bytes)
	//Failing this, use the code commented below
	for(j=0;j<8;j++)
	{
		for(i=0;i<(3*64);i+=3)
		{
			uiIdx = (192*j)+i;
			
			uiData = EEoptions[uiIdx];						//Read byte from array
			__builtin_tblwth(pOffset, uiData);				//Write to upper byte
			
			uiData = (EEoptions[uiIdx+1]<<8) + EEoptions[uiIdx+2];//Read int from byte array
			__builtin_tblwtl(pOffset, uiData);				//Write to address low word
			
			pOffset = pOffset + 2;							//Increment address
		}
/*
		if(unused blocks in row)
		{
			__builtin_tblwth(pOffset,0xFF);
			__builtin_tblwtl(pOffset,0xFFFF);
		}
 */

		//Write data
		asm("DISI #5");//Block all ints with priority<7 for next 5 instructions (call below is 7 instructions)
		__builtin_write_NVM();									//Perform write sequence requested in NVMCON
	}

	//Clean up
	NVMCON = 0x0000;										//Clear flash control register
	TBLPAG = savedTBLPAG;									//Restore the table page
}

void ReadEprom(void)
{
	unsigned int savedTBLPAG;
	unsigned int pOffset;
	unsigned int i,j;
	unsigned int uiData;
	unsigned int uiIdx;

	savedTBLPAG = TBLPAG;									//Save the table page

	TBLPAG = __builtin_tblpage(&emulationPages);
	pOffset = __builtin_tbloffset(&emulationPages);

	//We will program one row at a time (64instr * 3 = 192 bytes)
	NVMCON = PROGRAM_ROW;

	//Load holding latches
	//Note: make sure all unused latches are written with 0xFFFFFF, otherwise they may write to the wrong row
	//For easier programming, just make EEoptions a multiple of the row size (64*3=192bytes)
	for(j=0;j<8;j++)
	{
		for(i=0;i<(3*64);i+=3)
		{
			uiIdx = (192*j)+i;

			uiData = __builtin_tblrdh(pOffset);				//Read upper byte
			EEoptions[uiIdx] = (char)uiData;				//Byte 3

			uiData = __builtin_tblrdl(pOffset);				//Read address low word
			EEoptions[uiIdx+1] = uiData >> 8;					//Byte 2
			EEoptions[uiIdx+2] = (char)uiData;				//Byte 1

			pOffset = pOffset + 2;							// Increment address
		}
	}

	//Clean up
	TBLPAG = savedTBLPAG;									//Restore the table page
}

//Writes our options to flash.  Note flash block must be erased first.
void SaveEprom(void)
{
	EraseEprom();
	WriteEprom();
}