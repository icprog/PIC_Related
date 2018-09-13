#include    "system.h"
#include    "tempCalc.h"

#ifndef     LEAD_ACID_H
#define     LEAD_ACID_H

#define     AGM
//define      FLOODED

#define     PRECHARGE_TIME          5

extern      int16_t                 batteryTemp;


#ifdef      AGM

    #define CHARGING_VOLTAGE		1425+(int16_t)((250-batteryTemp)*.24)   // 14.25V @25C + Temperature compensation of 4mV/cell(24mV/monoblock))
	#define	FLOATING_VOLTAGE		1350+(int16_t)((250-batteryTemp)*.24)   // 13.50V @25C + Temperature compensation of 4mV/cell(24mV/monoblock))
	#define	CUTOFF_VOLTAGE			1075                                    // 10.75V

	#define	ILIM_PRECHARGE			10                                      // 1A, Small current set at PRECHARGE stage
	#define	ILIM					35                                      // 3.5A Point where we switch back to MPPT, or Current Mode
	#define IFLOAT					15                                      // 1.5A, Point where we go in and out of FLOAT Mode				

#endif

#ifdef      FLOODED

    #define CHARGING_VOLTAGE		1425+(int16_t)((250-batteryTemp)*.24)   // 14.25V @25C + Temperature compensation of 4mV/cell(24mV/monoblock))
	#define	FLOATING_VOLTAGE		1350+(int16_t)((250-batteryTemp)*.24)   // 13.50V @25C + Temperature compensation of 4mV/cell(24mV/monoblock))
	#define	CUTOFF_VOLTAGE			1075                                    // 10.75V

	#define	ILIM_PRECHARGE			10                                      // 1A, Small current set at PRECHARGE stage
	#define	ILIM					35                                      // 3.5A Point where we switch back to MPPT, or Current Mode
	#define IFLOAT					15                                      // 1.5A, Point where we go in and out of FLOAT Mode				

#endif
    
#endif
