
#include <xc.h>
#include "glcd.h"
#include "system.h" 
#include <stdlib.h>

void main (void)
{
    Init();
    unsigned char i;
	Init_GLCD(); 
	// ascii 22 (0x16) is set position followed by x,y
	PutMessage((unsigned char* const)"\x16\x20\x08DannyZee's\x16\x20\x10 Electronics\n Title:\n Author:\n Date:\n Hardware:");
	PutMessage((unsigned char* const)"\x16\x38\x18 Graphic demo.");
	PutMessage((unsigned char* const)"\x16\x38\x20 Dave Ziegl.");
	PutMessage((unsigned char* const)"\x16\x38\x28 Apr 19 2017.");
	PutMessage((unsigned char* const)"\x16\x38\x30 16F18855.");
	box(1,1,126,62);
	SetPos(3,3);
	PutLogo((const unsigned char*)Logo);
	SetPos(127-3-20,3);
	PutLogo((const unsigned char*)Logo);
	while (1)
    {
    //    ClearScreen();
//        int count;
  //      char buf[10];
    //    itoa(buf, count, 16);
      //  PutMessage(*buf);
        //count+=1;
       // __delay_ms(1000);
        
    }
}

