#include "PID_Lib.h"

int PID_Kp[3], PID_Ki[3];
unsigned char PID_Kd[3];
int PID_Integrated[3];
int PID_Prev_Input[3];
int PID_MinOutput[3], PID_MaxOutput[3];
unsigned char PID_First_Time[3];

// ***************************************************************************************************************************************************************
void Init_PID(unsigned char controller, int Kp, int Ki, char Kd, int MinOutput, int MaxOutput)
{
  PID_Kp[controller]         = Kp;
  PID_Ki[controller]         = Ki;
  PID_Kd[controller]         = Kd;
  PID_MinOutput[controller]  = MinOutput;
  PID_MaxOutput[controller]  = MaxOutput;
  PID_Integrated[controller] = 0;
  PID_Prev_Input[controller] = 0;
  PID_First_Time[controller] = 1;
}

// ***************************************************************************************************************************************************************
int PID_Calculate(unsigned char controller, int const setpoint[controller], int temp[controller])
{
  int Err, ErrValue, DerivativeValue, Result;

  Err = eepromGetData(setpoint[controller]) - temp[controller];
  
  // --- calculate proportional value ---
  ErrValue  = Err * PID_Kp[controller];

  // --- Calculate integrated value ---
  PID_Integrated[controller] = PID_Integrated[controller] + (Err * PID_Ki[controller]);
 
  // limit it to output minimum and maximum
  if (PID_Integrated[controller] < PID_MinOutput[controller]) 
    PID_Integrated[controller] = PID_MinOutput[controller];
  if (PID_Integrated[controller] > PID_MaxOutput[controller])
    PID_Integrated[controller] = PID_MaxOutput[controller];

  // --- calculate derivative value ---
  if (PID_First_Time[controller])
  {
    // to avoid a huge DerivativeValue the first time (PID_Prev_Input = 0)
    PID_First_Time[controller] = 0;
    PID_Prev_Input[controller] = temp[controller];
  }
  
  DerivativeValue = (temp[controller] - PID_Prev_Input[controller]) * PID_Kd[controller];
  PID_Prev_Input[controller] = temp[controller];
    
  // --- calculate total ---
  Result = ErrValue + PID_Integrated[controller] - DerivativeValue; // mind the minus sign!!!
  // limit it to output minimum and maximum
  if (Result < PID_MinOutput[controller]) 
    Result = PID_MinOutput[controller];
  if (Result > PID_MaxOutput[controller])
    Result = PID_MaxOutput[controller];

  return (Result);
}
// ***************************************************************************************************************************************************************
