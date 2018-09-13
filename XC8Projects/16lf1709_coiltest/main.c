/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

unsigned char led_bit,spk_bit,spk_enable,spk_enable2;
unsigned int led_counter;

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    led_counter=0;
    spk_bit=0;
    led_bit=0;

    LCDInit();
    LCDClear();
    gotoXY(1,1);
    LCDString("PIC 16LF1709");
    
    while(1)
    {
        /* TODO <INSERT USER APPLICATION CODE HERE> */
	if(spk_bit==1)
	{
	    if((spk_enable==1)&&(spk_enable2==1))
	    RB6=1;
	}else RB6=0;
    }

}

