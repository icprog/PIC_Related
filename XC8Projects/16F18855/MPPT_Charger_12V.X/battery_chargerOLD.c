#include "battery_charger.h"

uint8_t             battery_state0;
uint8_t             battery_state1;
uint16_t            Imin0Count;
uint16_t            Imin1Count;
//uint16_t            Iflat_db;
int16_t             state_counter0;
int16_t             state_counter1;
int16_t             Imin0;
int16_t             Imin1;
int16_t             Iref0;                                       // setpoint for current output
int16_t             Vref0;                                       // setpoint for voltage output
int16_t             Iref1;                                       // setpoint for current output
int16_t             Vref1;                                       // setpoint for voltage output
//uint16_t            warmup;
int16_t             Iout;
//uint16_t            Vout;
int8_t              Imode0          =   1;
int8_t              Imode1          =   1;
uint8_t             cc_cv0          =   0;
uint8_t             cc_cv1          =   0;
int8_t              V0HoldMode      =   0;
int8_t              V1HoldMode      =   0;
int16_t             voltage[4]      =   {0};                    // Store calculated Voltage values
int16_t             current[4]      =   {0};                    // Store Calculated Current Values




void Init_Battery_State_Machine()
{
	battery_state0 = PRECHARGE;                          // Set to PRECHARGE on a system Reset
	state_counter0 = PRECHARGE_TIME;                     // Set counter to PRECHARGE_TIME

	SET_CURRENT0(ILIM_PRECHARGE);                        // SET_CURRENT to ILIM_PRECHARGE (ILIM_PRECHARGE is in lead-acid_agm.h)
	SET_VOLTAGE0(CHARGING_VOLTAGE);                      // SET_VOLTAGE to CHARGING_VOLTAGE (CHARGING_VOLTAGE is in lead-acid_agm.h) SET_VOLTAGE sets Vref value

	Imin0 = IFLOAT;                                      // Set Imin to the IFLOAT Current Limit (found in lead_acid_agm.h)
	Imin0Count = IminUpdate;
}

void Battery_State_Machine()
{
	if(battery_state0 == PRECHARGE)
	{
		if(VSENSE0 < CUTOFF_VOLTAGE)                    // If Battery Voltage is below CUTOFF_VOLTAGE
		{
			if(state_counter0>0)                         // If state_counter > 0
            {
                state_counter0-=1;                       // decrement it
            }
            else
            {
                battery_state0 = FAULT;                  // else, Set FAULT mode
			}
		} 
        else                                            // VSENSE is >= CUTOFF_VOLTAGE
		{
			battery_state0 = CHARGE;                     // Set CHARGE mode
			SET_CURRENT0(ILIM);                          // Set Current sets IRef value
		}
	}
    else if(battery_state0 == CHARGE)
	{
		if(CONSTANT_VOLTAGE0)                           // Mode is "Voltage Mode", not "Current Mode", So we are applying Topping current
		{
			if(ISENSE0 < Imin0)      // || ISENSE1 < Imin)
			{
                Imin0Count-=2;
                if(Imin0Count<2)                          // Current has been low for at least IminCount cycles (600 cycles, or about 10 minutes)
                {
                    battery_state0 = FLOAT;              // Switch to Float Charging Mode    
                }
			}
            else
			{
				if(Imin0Count<IminUpdate)Imin0Count+=1; // Keep us from going into Float because of sporadic sun
			}
		}
	} 
    else if(battery_state0 == FLOAT)
	{
        SET_VOLTAGE0(FLOATING_VOLTAGE);
    	SET_CURRENT0(IFLOAT);                            // Set Current sets IRef value
    }
	else
	if(battery_state0 == FAULT)
	{
        LCDWriteStringXY(0,0,"BATTERY FAULT");
        Imode0=0;
        Imode1=0;
        __delay_ms(2000);
//		SET_VOLTAGE(0);
//		SET_CURRENT(0);
//		STOP_CONVERTER();	
	}
}

void cc_cv_mode()
{
	if(VSENSE0>Vref0)                                  // Vref is set by SET_VOLTAGE()
	{
        if(V0HoldMode<12)V0HoldMode+=1;
        
		if(cc_cv0)                                       // cc_cv is the number of slowLoop cycles to complete before switching to Voltage Mode
        {
            cc_cv0-=1;                                   // Decrement it by 1,
        }
        else
		{
			if(Imode0)                                  // until it is zero, 
            {
                Imode0 = 0;                             // then, switch to "Voltage Mode"
            }
		}
	}
    else if(VSENSE0<Vref0)
    {
        V0HoldMode-=1;
        if(V0HoldMode<(CURRENT_MODE*-1))
        {
            Imode0 = 1;                                 // switch to "Current Mode"
            cc_cv0 = (CURRENT_MODE*2);                   // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
            V0HoldMode=(CURRENT_MODE*-1);
        }
    }
    else V0HoldMode=V0HoldMode;
    
    if(ISENSE0>Iref0)                                  // Iref is set by "SET_CURRENT(some Value here)" Use this to come back out of FLOAT Mode
	{
		if(!Imode0)                                     // If not "CURRENT Mode",
        {
            if(battery_state0 == FLOAT)
            {
                battery_state0=CHARGE;                   // Set CHARGE mode
                SET_VOLTAGE0(CHARGING_VOLTAGE);          // Set Vref back to CHARGING_VOLTAGE
                SET_CURRENT0(ILIM);                      // Set Iref back to ILIM
                Imode0 = 1;                             // switch to "Current Mode"
                cc_cv0 = CURRENT_MODE;                   // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
            }
        }
	}


    
    
	if(VSENSE1>Vref1)                                  // Vref is set by SET_VOLTAGE()
	{
        if(V1HoldMode<12)V1HoldMode+=1;
        
		if(cc_cv1)                                       // cc_cv is the number of slowLoop cycles to complete before switching to Voltage Mode
        {
            cc_cv1-=1;                                   // Decrement it by 1,
        }
        else
		{
			if(Imode1)                                  // until it is zero, 
            {
                Imode1 = 0;                             // then, switch to "Voltage Mode"
            }
		}
	}
    else if(VSENSE1<Vref1)
    {
        V1HoldMode-=1;
        if(V1HoldMode<(CURRENT_MODE*-1))
        {
            Imode1 = 1;                                 // switch to "Current Mode"
            cc_cv1 = (CURRENT_MODE*2);                   // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
            V1HoldMode=(CURRENT_MODE*-1);
        }
    }
    else V1HoldMode=V1HoldMode;
    
    if(ISENSE1>Iref1)                                  // Iref is set by "SET_CURRENT(some Value here)" Use this to come back out of FLOAT Mode
	{
		if(!Imode1)                                     // If not "CURRENT Mode",
        {
            if(battery_state1 == FLOAT)
            {
                battery_state1=CHARGE;                   // Set CHARGE mode
                SET_VOLTAGE1(CHARGING_VOLTAGE);          // Set Vref back to CHARGING_VOLTAGE
                SET_CURRENT1(ILIM);                      // Set Iref back to ILIM
                Imode1 = 1;                             // switch to "Current Mode"
                cc_cv1 = CURRENT_MODE;                   // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
            }
        }
	}
}
