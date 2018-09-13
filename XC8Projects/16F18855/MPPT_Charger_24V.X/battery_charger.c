#include "battery_charger.h"

uint8_t             batteryState[2];
uint8_t             cc_cv[2]        =   0;
int16_t             current[4]      =   {0};                // Store Calculated Current Values
int16_t             Imin[2];
uint16_t            IminCount[2];
int8_t              Imode[2]        =   0;
int16_t             Iout;
int16_t             Iref[2];                                // setpoint for current output
int16_t             stateCounter[2];
int8_t              VHoldMode[2]    =   0;
int16_t             voltage[4]      =   {0};                // Store calculated Voltage values
int16_t             Vref[2];                                // setpoint for voltage output
uint8_t             x               =   0;                  // Counter for lowering Charge Voltage


void Init_Battery_State_Machine(uint8_t z)
{
	batteryState[z] =PRECHARGE;                             // Set to PRECHARGE on a system Reset
	stateCounter[z] =PRECHARGE_TIME;                        // Set counter to PRECHARGE_TIME
	Iref[z]         =ILIM_PRECHARGE;                        // SET_CURRENT to ILIM_PRECHARGE (ILIM_PRECHARGE is in lead-acid_agm.h)
	Vref[z]         =CHARGING_VOLTAGE;                      // SET_VOLTAGE to CHARGING_VOLTAGE (CHARGING_VOLTAGE is in lead-acid_agm.h) SET_VOLTAGE sets Vref value
	Imin[z]         =IFLOAT;                                // Set Imin to the IFLOAT Current Limit (found in lead_acid_agm.h)
	IminCount[z]    = IminUpdate;                           // IminUpdate is is battery_Charger.h
}

void Battery_State_Machine(uint8_t z)
{
	if(batteryState[z]==PRECHARGE)
	{
		if(voltage[z]<CUTOFF_VOLTAGE)                       // If Battery Voltage is below CUTOFF_VOLTAGE
		{
			if(stateCounter[z]>0)                           // If stateCounter > 0
            {
                stateCounter[z]-=1;                         // decrement it
            }
            else
            {
                batteryState[z]=FAULT;                      // else, Set FAULT mode
			}
		} 
        else                                                // VSENSE is >= CUTOFF_VOLTAGE
		{
			batteryState[z]=CHARGE;                         // Set CHARGE mode
			Iref[z]=ILIM;                                   // Set IRef value
		}
	}
    else if(batteryState[z]==CHARGE)
	{
        Vref[z]=CHARGING_VOLTAGE;
		if(!(Imode[z]))                                     // Mode is "Voltage Mode", not "Current Mode", So we are applying Topping current
		{
			if(current[z] < Imin[z])                        // if Current is less than min current
			{
                IminCount[z]-=2;                            // decrement IminCount by 2
                if(IminCount[z]<10)                         // Current has been low for at least IminCount cycles (600 cycles, or about 10 minutes)
                {
                    batteryState[z] = FLOAT;                // Switch to Float Charging Mode  
                    IminCount[z]=10;
                }
			}
            else
			{
				if(IminCount[z]<IminUpdate)IminCount[z]+=1; // Keep us from going into Float because of sporadic sun
			}
		}
        else if(IminCount[z]<IminUpdate)IminCount[z]+=1;    // Keep us from going into Float because of sporadic sun
	} 
    else if(batteryState[z] == FLOAT)
	{
        Vref[z]=FLOATING_VOLTAGE;
    	Iref[z]=IFLOAT;                                     // Set Current sets IRef value
        Imode[z]=0;
    }
	else
	if(batteryState[z] == FAULT)
	{
        batteryState[z]=PRECHARGE;
	}
}

void cc_cv_mode(uint8_t z)                                  // Function determines Charge mode (Voltage or Current))
{
	if(voltage[z]>=Vref[z])                                 // voltage Out is >= Reference voltage
	{
        if(VHoldMode[z]<CURRENT_MODE)VHoldMode[z]+=1;       // VHoldMode switches us between Current or Voltage mode (Voltage mode at +VHoldMode)
        if(VHoldMode[z]<CURRENT_MODE)VHoldMode[z]+=1;       // Help hold us in Voltage mode, unless we can not make V reference
        
		if(cc_cv[z])                                        // cc_cv is the number of slowLoop cycles to complete before switching to Voltage Mode
        {
            cc_cv[z]-=1;                                    // Decrement cc_cv[z] by 1,
        }
        else
		{
			if(Imode[z])                                    // until cc_cv[z] is zero, 
            {
                Imode[z]=0;                                 // then, switch to "Voltage Mode"
            }
		}
	}
    else                                                    // if(voltage[z]<Vref[z])
    {
        VHoldMode[z]-=1;                                    // VHoldMode switches us between Current or Voltage mode (Current mode at -VHoldMode)
        if(VHoldMode[z]<(CURRENT_MODE*-1))
        {
            Imode[z]=1;                                     // switch to "Current Mode"
            cc_cv[z]=(CURRENT_MODE*2);                      // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
            VHoldMode[z]=(CURRENT_MODE*-1);
        }
    }
    
    if(current[z]>Iref[z])                                  // Iref is set by "SET_CURRENT(some Value here)" Use this to come back out of FLOAT Mode
	{
		if(!(Imode[z]))                                     // If not "CURRENT Mode",
        {
            if(batteryState[z]==FLOAT)                      // If batteryState is FLOAT Mode
            {
                if(voltage[z]<FLOATING_VOLTAGE-70)          // If voltage is lower that FLOATING_VOLTAGE by .7V
                {
                    batteryState[z]=CHARGE;                 // Set CHARGE mode
                    Vref[z]=CHARGING_VOLTAGE;               // Set Vref back to CHARGING_VOLTAGE
                    Iref[z]=ILIM;                           // Set Iref back to ILIM
//                    Imode[z]=1;                             // switch to "Current Mode"
//                    cc_cv[z]=CURRENT_MODE;                  // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
                }
            }
        }
	}
}