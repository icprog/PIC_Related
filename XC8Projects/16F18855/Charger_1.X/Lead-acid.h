/*****************************************************************************
*                           Lead-acid.h
*
* Description: Lead-acid specific parameters
*
* Hardware:  Synchronous Inverse SEPIC (Zeta) Converter + Battery Charging Library
*
* Resources: PICC 9.83 / MPLAB 8.80
*
******************************************************************************/

//Lead-acid battery specific parameters

#define PRESET1
//define PRESET2


//	1.75V per cell cutoff voltage
// 	2.10V per cell charged OCV voltage
//	2.25V per cell floating voltage
//	2.40V per cell charging voltage

#ifdef PRESET1
	#define LA_3CELL
	#define CAPACITY 				4000
	#define CHARGING_VOLTAGE		1474	//7.20V
	#define	FLOATING_VOLTAGE		1382	//6.75V
	#define TOPPING_VOLTAGE			1290	//6.30V
	#define	CUTOFF_VOLTAGE			1075	//5.25V

	#define	ILIM_PRECHARGE			173		//50mA, C/10
	#define	ILIM					347		//800mA, C/5
	#define IFLOAT					35		//80mA, C/50 (2%) minimum charging current				

#endif

#define		BATTERY_STANDBY_MODE
	

#define	PRECHARGE_TIME		600

#define FLOAT_TIME			43200

#define	FLOAT_RELAX_TIME	(FLOAT_TIME - 10)

#define IFLAT_COUNT		600

