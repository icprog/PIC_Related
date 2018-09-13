#include <xc.h>
#include "PID_Lib.h"

#pragma config FOSC = INTOSCIO                                  // Oscillator Selection bits
#pragma config WDTE = OFF                                       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON                                       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON                                       // Brown-out Reset Enable bit (BOR enabled)
#define _XTAL_FREQ 2000000                                      // Must be defined, or Compiler will error out using __delay_ms()


void Reset_PID()
{
  PID_Integrated = 0;
  PID_Prev_Input = 0;
  PID_First_Time = TRUE;
}

void Init_PID(int Kp, int Ki, int Kd, int MinOutput, int MaxOutput)
{
  PID_Kp         = Kp;
  PID_Ki         = Ki;
  PID_Kd         = Kd;
  PID_MinOutput  = MinOutput;
  PID_MaxOutput  = MaxOutput;
  PID_Integrated = 0;
  PID_Prev_Input = 0;
  PID_First_Time = TRUE;
}

int PID_Calculate(int SetPoint, int InputValue){
  int Err, ErrValue, DiffValue, Result;


  Err = SetPoint - InputValue;

  // --- calculate proportional value ---
  ErrValue  = Err * PID_Kp;

  // --- Calculate integrated value ---
  PID_Integrated = PID_Integrated + (Err * PID_Ki);
  // limit it to output minimum and maximum
  if (PID_Integrated < PID_MinOutput) 
    PID_Integrated = PID_MinOutput;
  if (PID_Integrated > PID_MaxOutput)
    PID_Integrated = PID_MaxOutput;

  // --- calculate derivative value ---
  if (PID_First_Time)
  {
    // to avoid a huge DiffValue the first time (PID_Prev_Input = 0)
    PID_First_Time = FALSE;
    PID_Prev_Input = InputValue;
  }
  DiffValue = (InputValue - PID_Prev_Input) * PID_Kd;
  PID_Prev_Input = InputValue;

  // --- calculate total ---
  Result = ErrValue + PID_Integrated - DiffValue; // mind the minus sign!!!
  // limit it to output minimum and maximum
  if (Result < PID_MinOutput) 
    Result = PID_MinOutput;
  if (Result > PID_MaxOutput)
    Result = PID_MaxOutput;
  return (Result);
}