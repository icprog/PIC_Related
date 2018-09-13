/*****************************************************************************
*                           BatteryCharger.h
*
* Description: Main program loop
*
* Hardware:  Synchronous Inverse SEPIC (Zeta) Converter + Battery Charging Library
*
* Resources: PICC 9.83 / MPLAB 8.80
*
******************************************************************************/

#include "Hardware.h"

#ifndef BATTERYCHARGER_H
	#define BATTERYCHARGER_H
	enum charge_states { IDLE = 0, FAULT = 1, DONE = 2, PRECHARGE = 3, CHARGE = 4, FLOAT = 5 };
#endif

#define		BATTERY_SLA
//#define		BATTERY_LIFEPO
//#define		BATTERY_LICO

#ifdef	BATTERY_SLA
	#include "Lead-acid.h"
	#define 	ISTOP	IFLOAT
#endif

#ifdef	BATTERY_LIFEPO
	#include "LiFePo.h"
#endif

#ifdef	BATTERY_LICO
	#include "LiCo.h"
#endif

#define 	IMIN_UPDATE			5
#define		VBAT_DETECTION		1640

extern unsigned char battery_state;

void Init_State_Machine(void);
void Battery_State_Machine(void);