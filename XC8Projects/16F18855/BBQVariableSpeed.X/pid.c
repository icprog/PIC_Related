// **************** Includes ***************************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
int16_t         error           = 0;
static int16_t  lastError       = 0;
int16_t         errorValue      = 0;
int16_t         derivativeValue = 0;
int16_t         Result          = 0;
int16_t         Kp              = 3;    // Controller Gain      (inverse of Proportional Band)
int16_t         Ki              = 1;    // Controller Integral Reset/Unit Time, determined by how often PID is calculated
int16_t         Kd              = 20;   // Controller Derivative (or Rate))
int16_t         integralValue   = 0;
int16_t         oldError        = 0;
static int16_t pidIntegrated    = 0;
static int16_t  D_PrevError     = 0;
int16_t         pidMinOutput    = 0;        // Minimum output limit of Controller
int16_t         pidMaxOutput    = 1023;     // Maximum output limit of Controller
static uint8_t  loop            = 0;        // Loop to limit Reset action

// *************** Calculate PID Runs faster if called more often **************    
int16_t PID_Calculate(int16_t setpoint, int16_t temp)
{
    loop+=1;
// **************** Calculate Gain *********************************************    
    error = setpoint - temp;                                                    // error calculation
    
    errorValue  = error * Kp;                                                   // Calculate proportional value
    
    if(errorValue>pidMaxOutput)errorValue=pidMaxOutput;
    if(errorValue<-1023)errorValue=-1023;

// *************** Calculate Derivative ****************************************    
    derivativeValue=(error-D_PrevError)*Kd;
    D_PrevError = error;
//    if(derivativeValue>150)derivativeValue=150;
  
    
// **************** Calculate Integral Action ********************************** 
    if(loop>2)
    {
    if(error>=2)error=2;
    if(error<=-2)error=-2;

    
    if(error>=0)                                                                // Temperature is lower than setpoint
    {
        if(error>=lastError)                                                    // and, the Error is getting larger or not changing
        {
            if(pidIntegrated<pidMaxOutput)pidIntegrated = pidIntegrated + (error * Ki);// so, Sum onto the integral value
        }
        else                                                                    // Error is getting smaller, and we are below setpoint, but moving towards setpoint,
        {
            if(pidIntegrated>-1023)pidIntegrated = pidIntegrated - (error * Ki);  //  so subtract some Integral
        }
    }
    else                                                                        // Temperature is higher than setpoint, so, error is now Negative
    {
        if(error>=lastError)                                                     // Error is now a negative value, so ">" is a smaller error, so, we are moving towards setpoint

        {
            if(pidIntegrated<pidMaxOutput)pidIntegrated = pidIntegrated - (error * Ki);// Subtract integral 
        }
        else
        {
            if(pidIntegrated>-1023)pidIntegrated = pidIntegrated + (error * Ki);  // Add Integral gain 
        }
        if(pidIntegrated>0)pidIntegrated=0;


        //    if (pidIntegrated< pidMinOutput)                                            // limit output minimum value
  //  {
    //    pidIntegrated= pidMinOutput;
    //}
    
//    if (pidIntegrated> pidMaxOutput)                                            // limit output maximum value 
  //  {
    //    pidIntegrated= pidMaxOutput;
    }
    oldError    =   lastError;
    
    integralValue = pidIntegrated;                                              // Write the Static Variable pidIntegrated to an auto variable, so we can pass it to main as a global
    
    lastError=error;                                                            // Set lastError = to error (for next iteration)
    
    loop=0;
    }

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