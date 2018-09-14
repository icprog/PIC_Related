// **************** Includes ***************************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************    
float PID_Kp, PID_Ki;
float PID_Kd;
float pidIntegrated;
float pidPrevInput = 0;
int pidMinOutput, pidMaxOutput;

// **************** INIT PID ***************************************************    
void Init_PID(void)
{
  PID_Kp         = Kp;              // Gain Parameter       Defined in pid.h
  PID_Ki         = Ki;              // Integral Parameter   Defined in pid.h
  PID_Kd         = Kd;              // Derivative Parameter Defined in pid.h
  pidMinOutput  = minimumOutput;    // Min Output Parameter Defined in pid.h
  pidMaxOutput  = maximumOutput;    // Max Output Parameter Defined in pid.h
  pidIntegrated = 0;                // Contains the Output Integrated over the Time Base
  pidPrevInput = 0;                 // monitor change since last measurement, to calculate Derivative Value
}

// *************** Calculate PID Runs faster if called more often **************    
float PID_Calculate(int const setpoint, float temp)
{
    float error, errorValue, derivativeValue = 0, pidPrevError = 0, Result;
        
// **************** Calculate Gain *********************************************    
    error = setpoint - temp;                                // error calculation

    errorValue  = error * PID_Kp;                           // Calculate proportional value

// **************** Calculate Integral *****************************************    
    pidIntegrated = pidIntegrated + (error * PID_Ki);       // Calculate integral value

    if (pidIntegrated< pidMinOutput)                        // limit output minimum value
    {
        pidIntegrated= pidMinOutput;
    }
    
    if (pidIntegrated> pidMaxOutput)                        // limit output maximum value 
    {
        pidIntegrated= pidMaxOutput;
    }

// *************** Calculate Derivative ****************************************    
        derivativeValue=(error-pidPrevError)*PID_Kd;
        pidPrevError = error;
  
// *************** Calculate Final Output **************************************    
    Result = errorValue + pidIntegrated+ derivativeValue;   // Calculate total to send to Output
    
    if (Result < pidMinOutput)                              // limit output minimum value
    {
        Result = pidMinOutput;
    }
    
    if (Result > pidMaxOutput)                              // limit output maximum value 
    {
        Result = pidMaxOutput;
    }
 
    return (Result);
}