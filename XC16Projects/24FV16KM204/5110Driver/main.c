#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

int main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

//    led_counter=0;
  //  spk_bit=0;
    //led_bit=0;

    LCDInit();
    LCDClear();
    gotoXY(1,1);
    LCDString("PIC 16LF1709");
    
    while(1)
    {
        /* TODO <INSERT USER APPLICATION CODE HERE> */
//	if(spk_bit==1)
//	{
//	    if((spk_enable==1)&&(spk_enable2==1))
//	    TRISBbits.TRISB6 = 1;
//	}else TRISBbits.TRISB6=0;
    }
    return(1);

}

