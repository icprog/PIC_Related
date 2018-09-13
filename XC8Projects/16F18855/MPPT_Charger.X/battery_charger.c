#include "battery_charger.h"

uint8_t             battery_state;
uint16_t            IminCount;
//uint16_t            Iflat_db;
uint16_t            state_counter;
int16_t             Imin;
int16_t             Iref;                                       // setpoint for current output
int16_t             Vref;                                       // setpoint for voltage output
int16_t             Iout;
int8_t              Imode0          =   0;
int8_t              Imode1          =   0;
uint8_t             cc_cv;
int8_t              VHoldMode       =   0;
int16_t             voltage[4]      =   {0};                    // Store calculated Voltage values
int16_t             current[4]      =   {0};                    // Store Calculated Current Values
uint8_t             x               =   0;




void Init_Battery_State_Machine()
{
	battery_state = PRECHARGE;                          // Set to PRECHARGE on a system Reset
	state_counter = PRECHARGE_TIME;                     // Set counter to PRECHARGE_TIME

	SET_CURRENT(ILIM_PRECHARGE);                        // SET_CURRENT to ILIM_PRECHARGE (ILIM_PRECHARGE is in lead-acid_agm.h)
	SET_VOLTAGE(CHARGING_VOLTAGE);                      // SET_VOLTAGE to CHARGING_VOLTAGE (CHARGING_VOLTAGE is in lead-acid_agm.h) SET_VOLTAGE sets Vref value

	Imin = IFLOAT;                                      // Set Imin to the IFLOAT Current Limit (found in lead_acid_agm.h)
	IminCount = IminUpdate;
}

void Battery_State_Machine()
{
	if(battery_state == PRECHARGE)
	{
		if(VSENSE0 < CUTOFF_VOLTAGE)                     // If Battery Voltage is below CUTOFF_VOLTAGE
		{
			if(state_counter)                           // If state_counter > 0
            {
                state_counter-=1;                       // decrement it
            }
            else
            {
                battery_state = FAULT;                  // else, Set FAULT mode
			}
		} 
        else                                            // VSENSE is >= CUTOFF_VOLTAGE
		{
			battery_state = CHARGE;                     // Set CHARGE mode
			SET_CURRENT(ILIM);                          // Set Current sets IRef value
		}
	}
    else if(battery_state == CHARGE)
	{
		if(CONSTANT_VOLTAGE0)                           // Mode is "Voltage Mode", not "Current Mode", So we are applying Topping current
		{
			if(ISENSE0 < Imin)      // || ISENSE1 < Imin)
			{
                IminCount-=2;
                if(IminCount<2)                          // Current has been low for at least IminCount cycles (600 cycles, or about 10 minutes)
                {
                    battery_state = FLOAT;              // Switch to Float Charging Mode    
                }
			}
            else
			{
                x+=1;
                if(x>25)
                {
                    if(Vref>FLOATING_VOLTAGE)Vref-=1;
                    x=0;
                }
				if(IminCount<IminUpdate)IminCount+=1; // Keep us from going into Float because of sporadic sun
			}
		}
	} 
    else if(battery_state == FLOAT)
	{
        SET_VOLTAGE(FLOATING_VOLTAGE);
    	SET_CURRENT(IFLOAT);                            // Set Current sets IRef value
        Imode0=0;
    }
	else
	if(battery_state == FAULT)
	{
//		SET_VOLTAGE(0);
//		SET_CURRENT(0);
//		STOP_CONVERTER();	
	}
}

void cc_cv_mode()
{
	if(VSENSE0 > Vref)                                  // Vref is set by SET_VOLTAGE()
	{
        if(VHoldMode<10)VHoldMode+=1;
        
		if(cc_cv)                                       // cc_cv is the number of slowLoop cycles to complete before switching to Voltage Mode
        {
            cc_cv-=1;                                   // Decrement it by 1,
        }
        else
		{
			if(Imode0)                                  // until it is zero, 
            {
                Imode0 = 0;                             // then, switch to "Voltage Mode"
            }
		}
	}
    else
    {
        VHoldMode-=1;
        if(VHoldMode<(CURRENT_MODE*-1))
        {
            Imode0 = 1;                                 // switch to "Current Mode"
            cc_cv = CURRENT_MODE;                       // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
            VHoldMode=(CURRENT_MODE*-1);
        }
    }
    
    if(ISENSE0 > Iref)                             // Iref is set by "SET_CURRENT(some Value here)" Use this to come back out of FLOAT Mode
	{
		if(!(Imode0))                                     // If not "CURRENT Mode",
        {
            if(battery_state == FLOAT)
            {
                if(VSENSE0<FLOATING_VOLTAGE-40)
                {
                    battery_state=CHARGE;                   // Set CHARGE mode
                    SET_VOLTAGE(CHARGING_VOLTAGE);          // Set Vref back to CHARGING_VOLTAGE
                    SET_CURRENT(ILIM);                      // Set Iref back to ILIM
                    Imode0 = 1;                             // switch to "Current Mode"
                    cc_cv = CURRENT_MODE;                   // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
                }
            }
        }
	}
}
