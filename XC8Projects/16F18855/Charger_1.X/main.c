/*****************************************************************************
*                           main.c
*
* Description: Main program loop
*
* Hardware:  Synchronous Inverse SEPIC (Zeta) Converter + Battery Charging Library
*
* Resources: PICC 9.83 / MPLAB 8.80
*
******************************************************************************/

#include "BatteryCharger.h"

__CONFIG(0x39A4);
__CONFIG(0x1FFF);

void main()
{

	Init_Registers();

	Initialize_Hardware();

	Delay_ms(500);

	while(1)
	{
		if(TMR0IF)
		{

			TMR0IF = 0;
			if(but_cnt) but_cnt--;
			if(second) second--;
			
			read_ADC();

			if(battery_state > DONE)
		
			{
				cc_cv_mode();

				if(!cmode) pid(vout, vref); else
				pid(iout, iref);
			}
		}
		if(!but_cnt)
		{
			but_cnt = BUTTON_COUNT;

			if(!BUTTON & lbut)
			{
				if(battery_state == IDLE) Init_State_Machine(); else
				{
					battery_state = IDLE;
					SET_LED_BLINK(LED_OFF);
				}
			}
			lbut = BUTTON;

			led_blink();
		}
		if(!second)
		{
			second = SECOND_COUNT;

			Battery_State_Machine();
			
		}		
	}
}
