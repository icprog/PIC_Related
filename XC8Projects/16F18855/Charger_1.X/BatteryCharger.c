/*****************************************************************************
*                           BatteryCharger.c
*
* Description: Battery Charging Functions
*
* Hardware:  Synchronous Inverse SEPIC (Zeta) Converter + Battery Charging Library
*
* Resources: PICC 9.83 / MPLAB 8.80
*

******************************************************************************/

#include "BatteryCharger.h"

unsigned char battery_state;
unsigned char imin_db;
unsigned int iflat_db;
unsigned int state_counter;
unsigned int imin;

void Init_State_Machine()
{
	battery_state = PRECHARGE;	
	state_counter = PRECHARGE_TIME;
	SET_LED_BLINK(BLINK_05HZ);

	SET_CURRENT(ILIM_PRECHARGE);
	SET_VOLTAGE(CHARGING_VOLTAGE);

	imin = ILIM;
	imin_db = IMIN_UPDATE;
	iflat_db = IFLAT_COUNT;

	START_CONVERTER();
}

void Battery_State_Machine()
{
	if(battery_state == PRECHARGE)
	{
		SET_LED_BLINK(BLINK_05HZ);
		if(VSENSE < CUTOFF_VOLTAGE)
		{
			if(state_counter) state_counter--; else
				{
					battery_state = FAULT;
					SET_LED_BLINK(BLINK_05HZ);
				}
		} else
		{
			battery_state = CHARGE;
			SET_CURRENT(ILIM);
		}
	} else
	if(battery_state == CHARGE)
	{
		SET_LED_BLINK(BLINK_05HZ);
		if(CONSTANT_VOLTAGE)
		{
			if(ISENSE < imin)
			{
				if(imin_db) imin_db--; else
				{
					imin = ISENSE;
					imin_db = IMIN_UPDATE;
					iflat_db = IFLAT_COUNT;
				}
			} else
			{
				imin_db = IMIN_UPDATE;
				if(iflat_db) iflat_db--;
			}
		} else
		{
			imin_db = IMIN_UPDATE;
			iflat_db = IFLAT_COUNT;
			imin = ILIM;
		}
		if(imin < ISTOP || !iflat_db)
		{
			#ifdef	BATTERY_SLA
				battery_state = FLOAT;
				state_counter = FLOAT_TIME;

				SET_VOLTAGE(FLOATING_VOLTAGE);
			#else
				battery_state = DONE;
				if(imin < I_BAT_DETECT) battery_state = IDLE;
			#endif
		}
	} else
	if(battery_state == FLOAT)
	{
		SET_LED_BLINK(LED_ON);
		if(state_counter) state_counter--; else
		{
			battery_state = DONE;
		}
		#ifdef BATTERY_SLA
			if(state_counter < FLOAT_RELAX_TIME && ISENSE < I_BAT_DETECT)
			battery_state = IDLE;
		#endif
	} else
	if(battery_state == IDLE)
	{
		SET_LED_BLINK(LED_OFF);
		SET_VOLTAGE(0);
		SET_CURRENT(0);
		STOP_CONVERTER();
	} else
	if(battery_state == FAULT)
	{
		SET_LED_BLINK(BLINK_2HZ);
		SET_VOLTAGE(0);
		SET_CURRENT(0);
		STOP_CONVERTER();	
	} else
	if(battery_state == DONE)
	{
		SET_LED_BLINK(LED_ON);
		#ifdef BATTERY_STANDBY_MODE
			if(VSENSE < TOPPING_VOLTAGE && VSENSE > VBAT_DETECTION)
			{
				battery_state = CHARGE;

				SET_CURRENT(ILIM);
				SET_VOLTAGE(CHARGING_VOLTAGE);

				imin = ILIM;
				imin_db = IMIN_UPDATE;
				iflat_db = IFLAT_COUNT;

				START_CONVERTER();
			} else
			{
				SET_VOLTAGE(0);
				SET_CURRENT(0);
				STOP_CONVERTER();	
				if(VSENSE < VBAT_DETECTION) battery_state = IDLE;
			}
		#else
			battery_state = IDLE;	
		#endif
	}
}