/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "system.h"
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

       if(INTCONbits.TMR0IF==1)
    {
	INTCONbits.TMR0IF=0;
	if(spk_bit==1)
	{
	    spk_bit=0;
	}else
	{
	    spk_bit=1;
	}

	    if(led_counter>0x115)spk_enable=1;else spk_enable=0;
	    if(led_counter>0x150)
	    {
		if(spk_enable2==1)
		{
		    spk_enable2=0;
		}else
		{
		    spk_enable2=1;
		}
		if(led_bit==1)
		{
		    led_bit=0;
		}else
		{
		    led_bit=1;
		}
		led_counter=0;
	    }

	led_counter++;
    }
}

