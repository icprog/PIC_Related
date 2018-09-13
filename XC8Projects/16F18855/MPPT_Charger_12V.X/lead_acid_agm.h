//Lead-acid battery specific parameters

#include    "tempCalc.h"

#ifndef     LEAD_ACID_AGM_H
#define     LEAD_ACID_AGM_H
#define     PRESET1
//define      PRESET2


//	1.75V per cell cutoff voltage
// 	2.10V per cell charged OCV voltage
//	2.25V per cell floating voltage
//	2.40V per cell charging voltage

#ifdef PRESET1
    extern  int16_t                 batteryTemp;

    #define CHARGING_VOLTAGE		1425+(int16_t)((250-batteryTemp)*.24)   // 14.45V @25C + Temperature compensation of 4mV/cell(24mV/monoblock))
//    #define CHARGING_VOLTAGE		1440	// 14.40V
	#define	FLOATING_VOLTAGE		1350+(int16_t)((250-batteryTemp)*.24)   // 13.50V @25C + Temperature compensation of 4mV/cell(24mV/monoblock))
	#define	CUTOFF_VOLTAGE			1075                                    // 10.75V

	#define	ILIM_PRECHARGE			10                                      // 1A, Small current set at PRECHARGE stage
	#define	ILIM					35                                      // 3.5A Point where we switch back to MPPT, or Current Mode
	#define IFLOAT					15                                      // 1.5A, Point where we go in and out of FLOAT Mode				

#endif

#define	PRECHARGE_TIME              5

#endif
