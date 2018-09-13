#ifndef PID_H
#define	PID_H

#define Kp              50      // Controller Gain      (inverse of Proportional Band)
#define Ki              1       // Controller Integral Reset/Unit Time, determined by how often PID is calculated
#define Kd              300     // Controller Derivative (or Rate))
#define minimumOutput   0       // Minimum output limit of Controller
#define maximumOutput   1023    // Maximum output limit of Controller

// **************** INIT PID *************************************************** 
// **************** Loads above #defines to the PID Controller *****************
void Init_PID(void);

// **************** Calculate PID (Call more often for fast loops) *************
// *** Output will update every time this is called, so, Reset & derivative ****
// ** actions happen more often, same as if Overall Loop Gain were increased! **
// ******* So, Temperature, poll less often, Flow or pressure more often. ******
// ** This algorithm is a non-interactive PID as opposed to Classic PID, so, ***
// ****** Tuning is handled differently, specifically, Gain is Stanalone. ******
float PID_Calculate(int const setpoint, float temp);

#endif