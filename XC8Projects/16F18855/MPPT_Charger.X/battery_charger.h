#include "system.h"


#define		SET_CURRENT(x)		{ Iref = x; }               // This is where we set Iref
#define		SET_VOLTAGE(x)		{ Vref = x; }               // This is where Vref gets set
//#define		WARMUP_TIME			64
#define		CONSTANT_VOLTAGE0	(!Imode0)
#define		CONSTANT_VOLTAGE1	(!Imode1)
//#define		I_BAT_DETECT		16 
#define		CURRENT_MODE		10                          // Number of slowLoop cycles Voltage is over Vref before we drop back to "Voltage Mode" from "Current Mode"

#define		VSENSE0             voltage[1]                  // VOut0
#define		ISENSE0             current[1]                  // IOut0
#define		VSENSE1             voltage[3]                  // VOut1
#define		ISENSE1             current[3]                  // IOut1

#define 	IminUpdate			10
//#define		VBAT_DETECTION		1640

//#define		STOP_CONVERTER()	{ TRIS_PWM0Out = 1; TRIS_PWM1Out = 1; }   // NCO is Numerically controller oscillator, will now be PWM to Converter?
//#define		STOP_CONVERTER()	{ increment = 0; set_NCO(); TRIS_CO1 = 1; TRIS_CO2 = 1; }   // NCO is Numerically controller oscillator, will now be PWM to Converter?
//#define  	START_CONVERTER()	{ warmup = WARMUP_TIME; TRIS_PWM0Out = 0; TRIS_PWM1Out = 0; }       // NCO is PWM to Converter?


#ifndef BATTERY_CHARGER_H
	#define BATTERY_CHARGER_H
	enum charge_states { IDLE = 0, FAULT = 1, FINISHED = 2, PRECHARGE = 3, CHARGE = 4, FLOAT = 5 };
#endif
    
    

//#define		BATTERY_SLA
#define     BATTERY_AGM
//#define		BATTERY_LIFEPO
//#define		BATTERY_LICO

#ifdef	BATTERY_AGM
	#include "lead_acid_agm.h"
#endif

#ifdef	BATTERY_LIFEPO
	#include "LiFePo.h"
#endif

#ifdef	BATTERY_LICO
	#include "LiCo.h"
#endif


extern uint8_t  battery_state;

void Init_Battery_State_Machine(void);
void Battery_State_Machine(void);
void cc_cv_mode();