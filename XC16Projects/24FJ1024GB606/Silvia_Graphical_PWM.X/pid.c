// **************** Includes ***************************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
float Kp[]              = { 50, 50, 50};    // Controller Gain      (inverse of Proportional Band)
float Ki[]              = { 15, 15, 15};    // Controller Integral Reset/Unit Time, determined by how often PID is calculated
float Kd[]              = { 25, 25, 25};    // Controller Derivative (or Rate))
float pidIntegrated[3]  = {  0,  0,  0};
float pidPrevError[3]   = {  0,  0,  0};
float pidPrevInput[3]   = {  0,  0,  0};
int pidMinOutput[3]     = {  0,  0,  0};     // Minimum output limit of Controller
int pidMaxOutput[3]= {1023,1023,1023};  // Maximum output limit of Controller
extern int8_t choice;

void Init_PID(int8_t controller, int pidKp, int pidKi, int pidKd)
{
    Kp[controller]         = pidKp;
    Ki[controller]         = pidKi;
    Kd[controller]         = pidKd;
    pidIntegrated[controller] = 0;
    pidPrevInput[controller] = 0;
}

// *************** Calculate PID Runs faster if called more often **************    
float PID_Calculate(uint8_t controller, uint16_t const setpoint[controller], uint16_t temp[controller])
{
    float error, errorValue, derivativeValue = 0, Result;
        
// **************** Calculate Gain *********************************************    
    error = setpoint[controller] - temp[controller];                                // error calculation

    errorValue  = error * Kp[controller];                           // Calculate proportional value

// **************** Calculate Integral *****************************************    
    pidIntegrated[controller] = pidIntegrated[controller] + (error * Ki[controller]);       // Calculate integral value

    if (pidIntegrated[controller]< pidMinOutput[controller])                        // limit output minimum value
    {
        pidIntegrated[controller]= pidMinOutput[controller];
    }
    
    if (pidIntegrated[controller]> pidMaxOutput[controller])                        // limit output maximum value 
    {
        pidIntegrated[controller]= pidMaxOutput[controller];
    }

// *************** Calculate Derivative ****************************************    
        derivativeValue=(error-pidPrevError[controller])*Kd[controller];
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