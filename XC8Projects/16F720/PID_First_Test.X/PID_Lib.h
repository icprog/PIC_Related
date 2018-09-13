#ifndef PID_LIB_H_
#define PID_LIB_H_

/*
----------------------------------------------------------
---- PID library with fixed calculation time interval ----
----------------------------------------------------------

Ahmed Lazreg
ahmed.lazreg@pocketmt.com

Translated from original mikroPascal code from D.Rosseel

D. Rosseel
Original: 27-09-2011
Latest update: 27-09-2011

History:
  29-09-2011: Translation from Pascal Code to MikroC
  27-09-2011: Original Version (in mikroPascal).
*/
// Documentation: http://en.wikipedia.org/wiki/PID_controller/ and http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/

#define BOOL unsigned char
#define TRUE 1
#define FALSE 0

int PID_Kp, PID_Ki, PID_Kd;
int PID_Integrated;
int PID_Prev_Input;
int PID_MinOutput, PID_MaxOutput;
BOOL PID_First_Time;

void Init_PID(int Kp, int Ki, int Kd, int MinOutput, int MaxOutput);
// Initialises the PID engine
// Kp = the "proportional" error multiplier
// Ki = the "integrated value" error multiplier
// Kd = the "derivative" error multiplier
// MinOutput = the minimal value the output value can have (should be < 0)
// MaxOutput = the maximal value the output can have (should be > 0)

void Reset_PID();
// Re-initialises the PID engine without change of settings

int PID_Calculate(int Setpoint, int InputValue);
// To be called at a regular time interval (e.g. every 100 msec)
// Setpoint: the target value for "InputValue" to be reached
// InputValue: the actual value measured in the system
// Functionresult: PID function of (SetPoint - InputValue),
//   a positive value means "InputValue" is too low (< SetPoint), the process should take action to increase it
//   a negative value means "InputValue" is too high (> SetPoint), the process should take action to decrease it

#endif  /* PID_LIB_H_ */