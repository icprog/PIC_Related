// **************** Includes ***************************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
int16_t error           = 0;
int16_t errorValue      = 0;
int16_t derivativeValue = 0;
int16_t Result          = 0;
int Kp                  = 4;    // Controller Gain      (inverse of Proportional Band)
int Ki                  = 1;    // Controller Integral Reset/Unit Time, determined by how often PID is calculated
int Kd                  = 8;    // Controller Derivative (or Rate))
int16_t pidIntegrated   = 0;
int16_t pidPrevError    = 0;
int pidMinOutput        = 0;     // Minimum output limit of Controller
int pidMaxOutput        = 4095;  // Maximum output limit of Controller

// *************** Calculate PID Runs faster if called more often **************    
float PID_Calculate(int16_t setpoint, int16_t temp)
{
    // **************** Calculate Gain *********************************************    
    error = setpoint - temp;                                // error calculation

    errorValue  = error * Kp;                           // Calculate proportional value

// *************** Calculate Derivative ****************************************    
        derivativeValue=(error-pidPrevError)*Kd;
        pidPrevError = error;
  
// **************** Calculate Integral *****************************************  

    pidIntegrated = pidIntegrated + (error * Ki)+derivativeValue;       // Calculate integral value

    if (pidIntegrated< pidMinOutput)                        // limit output minimum value
    {
        pidIntegrated= pidMinOutput;
    }
    
    if (pidIntegrated> pidMaxOutput)                        // limit output maximum value 
    {
        pidIntegrated= pidMaxOutput;
    }

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