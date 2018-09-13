#ifndef PID_LIB_H
#define	PID_LIB_H

#include "eeprom.h"

// ***************************************************************************************************************************************************************
void Init_PID(unsigned char controller, int Kp, int Ki, char Kd, int MinOutput, int MaxOutput);
// Initialises the PID engine
// Kp = the "proportional" error multiplier
// Ki = the "integrated value" error multiplier
// Kd = the "derivative" error multiplier
// MinOutput = the minimal value the output value can have (should be <= 0)
// MaxOutput = the maximal value the output can have (should be > 0)

// ***************************************************************************************************************************************************************
int PID_Calculate(unsigned char controller, int const setpoint[0], int temp[0]);

// To be called at a regular time interval (e.g. every 100 msec)
// Setpoint: the target value for "InputValue" to be reached
// InputValue: the actual value measured in the system
// Functionresult: PID function of (SetPoint - InputValue),
// a positive value means "InputValue" is too low (< SetPoint), the process should take action to increase it
// a negative value means "InputValue" is too high (> SetPoint), the process should take action to decrease it
#endif
// ***************************************************************************************************************************************************************
