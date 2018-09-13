// **************** Includes ***************************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
int16_t error               = 0;
static int16_t lastError    = 0;
int16_t errorValue          = 0;
int16_t derivativeValue     = 0;
int16_t Result              = 0;
int Kp                      = 10;   // Controller Gain      (inverse of Proportional Band)
int Ki                      = 1;    // Controller Integral Reset/Unit Time, determined by how often PID is calculated
int Kd                      = 2;    // Controller Derivative (or Rate))
int16_t integralValue       = 0;
static int16_t pidIntegrated= 0;
static int D_PrevError      = 0;
int pidMinOutput            = 0;        // Minimum output limit of Controller
int pidMaxOutput            = 2047;     // Maximum output limit of Controller

// *************** Calculate PID Runs faster if called more often **************    
int16_t PID_Calculate(int16_t setpoint, int16_t temp)
{
// **************** Calculate Gain *********************************************    
    error = setpoint - temp;                                                    // error calculation
    
    errorValue  = error * Kp;                                                   // Calculate proportional value

// **************** Calculate Integral Action **********************************    
    if(error>=0)                                                                // Temperature is lower than setpoint
    {
        if(error>=lastError)                                                    // Error is getting larger or not changing
        {
            if(pidIntegrated<2047)pidIntegrated = pidIntegrated + (error * Ki/4);// Sum onto the integral value
        }
        else                                                                    // Error is getting smaller
        {
            if(pidIntegrated>0)pidIntegrated = pidIntegrated - (error * Ki/8);  // Subtract 1/2 of the integral gain from the integrated total
        }
    }
    else                                                                        // Temperature is higher than setpoint
    {
        if(error>lastError)                                                     // Error is now a negative value, so ">" is a smaller error
        {
            if(pidIntegrated<2047)pidIntegrated = pidIntegrated - (error * Ki/16);// Sum a small amount to integral value to control Output from going too low (Cools slowly)
        }
        else
        {
            if(pidIntegrated>0)pidIntegrated = pidIntegrated + (error * Ki/2);  // Subtract Integral gain 
        }
    }

    if (pidIntegrated< pidMinOutput)                                            // limit output minimum value
    {
        pidIntegrated= pidMinOutput;
    }
    
    if (pidIntegrated> pidMaxOutput)                                            // limit output maximum value 
    {
        pidIntegrated= pidMaxOutput;
    }
    
    integralValue = pidIntegrated;                                              // Write the Static Variable pidIntegrated to an auto variable, so we can pass it to main as a global
    
    lastError=error;                                                            // Set lastError = to error (for next iteration)

// *************** Calculate Derivative ****************************************    
    derivativeValue=(error-D_PrevError)*Kd;
    D_PrevError = error;
  
// *************** Calculate Final Output **************************************    
    Result = errorValue+integralValue+derivativeValue;      // Calculate total to send to Output 
    
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