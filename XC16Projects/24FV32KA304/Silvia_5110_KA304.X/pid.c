// **************** Includes ***************************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
float internalKp[]              = {  50,  50,  50}; // Controller Gain      (inverse of Proportional Band)
float internalKi[]              = {  15,  15,  15}; // Controller Integral Reset/Unit Time, determined by how often PID is calculated
float internalKd[]              = {  25,  25,  25}; // Controller Derivative (or Rate))
float pidIntegrated[3]          = {   0,   0,   0};
float pidPrevError[3]           = {   0,   0,   0};
float pidPrevInput[3]           = {   0,   0,   0};
int pidMinOutput[3]             = {   0,   0,   0}; // Minimum output limit of Controller
int pidMaxOutput[3]             = {8191,8191,8191}; // Maximum output limit of Controller
extern int8_t choice;                                                                           // Not needed? FIX

void Init_PID(int8_t controller, int pidKp, int pidKi, int pidKd)
{
    internalKp[controller]              = pidKp;
    internalKi[controller]              = pidKi;
    internalKd[controller]              = pidKd;
    pidIntegrated[controller]           = 0;
    pidPrevInput[controller]            = 0;
}

// *************** PID_Calculate Runs faster if called more often **************    
float PID_Calculate(unsigned char controller, unsigned int setpoint, unsigned int temp)
{
    float error, errorValue, derivativeValue = 0, Result;
        
// **************** Calculate Gain *********************************************    
    error = setpoint - temp;                                // error calculation

    errorValue  = error * internalKp[controller];                           // Calculate proportional value

// **************** Calculate Integral *****************************************    
    pidIntegrated[controller] = pidIntegrated[controller] + (error * internalKi[controller]);       // Calculate integral value

    if (pidIntegrated[controller]< pidMinOutput[controller])                        // limit output minimum value
    {
        pidIntegrated[controller]= pidMinOutput[controller];
    }
    
    if (pidIntegrated[controller]> pidMaxOutput[controller])                        // limit output maximum value 
    {
        pidIntegrated[controller]= pidMaxOutput[controller];
    }

// *************** Calculate Derivative ****************************************    
        derivativeValue=(error-pidPrevError[controller])*internalKd[controller];
        pidPrevError[controller] = error;
  
// *************** Calculate Final Output **************************************    
    Result = errorValue + pidIntegrated[controller]+ derivativeValue;   // Calculate total to send to Output
    
    if (Result < pidMinOutput[controller])                              // limit output minimum value
    {
        Result = pidMinOutput[controller];
    }
    
    if (Result > pidMaxOutput[controller])                              // limit output maximum value 
    {
        Result = pidMaxOutput[controller];
    }
 
    return (Result);
}