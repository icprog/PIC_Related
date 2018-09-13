#ifndef PID_LIB_H
#define	PID_LIB_H

#include "eeprom.h"


void Init_PID0(int Kp, int Ki, char Kd, int MinOutput, int MaxOutput);
void Init_PID1(int Kp, int Ki, char Kd, int MinOutput, int MaxOutput);
void Init_PID2(int Kp, int Ki, char Kd, int MinOutput, int MaxOutput);
// Initialises the PID engine
// Kp = the "proportional" error multiplier
// Ki = the "integrated value" error multiplier
// Kd = the "derivative" error multiplier
// MinOutput = the minimal value the output value can have (should be <= 0)
// MaxOutput = the maximal value the output can have (should be > 0)

/*
void Reset_PID0();                                                               // Re-initialises the PID engine without change of settings
void Reset_PID1();                                                               // Re-initialises the PID engine without change of settings
void Reset_PID2();                                                               // Re-initialises the PID engine without change of settings
*/

int PID_Calculate0(int const setpoint[0], int temp[0]);
int PID_Calculate1(int const setpoint[1], int temp[1]);
int PID_Calculate2(int const setpoint[2], int temp[2]);
// To be called at a regular time interval (e.g. every 100 msec)
// Setpoint: the target value for "InputValue" to be reached
// InputValue: the actual value measured in the system
// Functionresult: PID function of (SetPoint - InputValue),
// a positive value means "InputValue" is too low (< SetPoint), the process should take action to increase it
// a negative value means "InputValue" is too high (> SetPoint), the process should take action to decrease it


#endif