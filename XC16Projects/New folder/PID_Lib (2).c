#include "PID_Lib.h"
    

int PID_Kp[3], PID_Ki[3];
unsigned char PID_Kd[3];
int PID_Integrated[3];
int PID_Prev_Input[3];
int PID_MinOutput[3], PID_MaxOutput[3];
unsigned char PID_First_Time[3];
//int Err;

/*
void Reset_PID0()
{
  PID_Integrated[0] = 0;
  PID_Prev_Input[0] = 0;
  PID_First_Time[0] = 1;
}

void Reset_PID1()
{
  PID_Integrated[1] = 0;
  PID_Prev_Input[1] = 0;
  PID_First_Time[1] = 1;
}

void Reset_PID2()
{
  PID_Integrated[2] = 0;
  PID_Prev_Input[2] = 0;
  PID_First_Time[2] = 1;
}
*/

void Init_PID0(int Kp, int Ki, char Kd, int MinOutput, int MaxOutput)
{
  PID_Kp[0]         = Kp;
  PID_Ki[0]         = Ki;
  PID_Kd[0]         = Kd;
  PID_MinOutput[0]  = MinOutput;
  PID_MaxOutput[0]  = MaxOutput;
  PID_Integrated[0] = 0;
  PID_Prev_Input[0] = 0;
  PID_First_Time[0] = 1;
}
void Init_PID1(int Kp, int Ki, char Kd, int MinOutput, int MaxOutput)
{
  PID_Kp[1]         = Kp/10;
  PID_Ki[1]         = Ki/10;
  PID_Kd[1]         = Kd;
  PID_MinOutput[1]  = MinOutput;
  PID_MaxOutput[1]  = MaxOutput;
  PID_Integrated[1] = 0;
  PID_Prev_Input[1] = 0;
  PID_First_Time[1] = 1;
}

void Init_PID2(int Kp, int Ki, char Kd, int MinOutput, int MaxOutput)
{
  PID_Kp[2]         = Kp/10;
  PID_Ki[2]         = Ki/10;
  PID_Kd[2]         = Kd;
  PID_MinOutput[2]  = MinOutput;
  PID_MaxOutput[2]  = MaxOutput;
  PID_Integrated[2] = 0;
  PID_Prev_Input[2] = 0;
  PID_First_Time[2] = 1;
}

int PID_Calculate0(int const setpoint[0], int temp[0])
{
  int Err, ErrValue, DerivativeValue, Result;


  Err = eepromGetData(setpoint[0]) - temp[0];
  
//  LCDWriteIntXY(0,0,Err,4);
  
  // --- calculate proportional value ---
  ErrValue  = Err * PID_Kp[0];
  //LCDWriteIntXY(0,7,PID_Kp[0],4);
  //LCDWriteIntXY(1,0,ErrValue,4);
  

  // --- Calculate integrated value ---
  PID_Integrated[0] = PID_Integrated[0] + (Err * PID_Ki[0]);
  
  //LCDWriteIntXY(2,0,(Err * PID_Ki[0]),4);
  //LCDWriteIntXY(3,0,PID_Integrated[0],4);
  
  // limit it to output minimum and maximum
  if (PID_Integrated[0] < PID_MinOutput[0]) 
    PID_Integrated[0] = PID_MinOutput[0];
  if (PID_Integrated[0] > PID_MaxOutput[0])
    PID_Integrated[0] = PID_MaxOutput[0];

  // --- calculate derivative value ---
  if (PID_First_Time[0])
  {
    // to avoid a huge DerivativeValue the first time (PID_Prev_Input = 0)
    PID_First_Time[0] = 0;
    PID_Prev_Input[0] = temp[0];
  }
  
  //LCDWriteIntXY(0,14,PID_Prev_Input[0],4);
  
  DerivativeValue = (temp[0] - PID_Prev_Input[0]) * PID_Kd[0];
  PID_Prev_Input[0] = temp[0];
  
  //LCDWriteIntXY(1,10,DerivativeValue,4);
  
  

  //LCDWriteIntXY(2,10,PID_Prev_Input[0],4);
  
  // --- calculate total ---
  Result = ErrValue + PID_Integrated[0] - DerivativeValue; // mind the minus sign!!!
  // limit it to output minimum and maximum
  if (Result < PID_MinOutput[0]) 
    Result = PID_MinOutput[0];
  if (Result > PID_MaxOutput[0])
    Result = PID_MaxOutput[0];
 
  //LCDWriteIntXY(3,10,Result,4);

  return (Result);
}


int PID_Calculate1(int const setpoint[1], int temp[1])
{
  int Err, ErrValue, DerivativeValue, Result;


  Err = eepromGetData(setpoint[1]) - temp[1];

  // --- calculate proportional value ---
  ErrValue  = Err * PID_Kp[1];

  // --- Calculate integrated value ---
  PID_Integrated[1] = PID_Integrated[1] + (Err * PID_Ki[1]);
  // limit it to output minimum and maximum
  if (PID_Integrated[1] < PID_MinOutput[1]) 
    PID_Integrated[1] = PID_MinOutput[1];
  if (PID_Integrated[1] > PID_MaxOutput[1])
    PID_Integrated[1] = PID_MaxOutput[1];

  // --- calculate derivative value ---
  if (PID_First_Time[1])
  {
    // to avoid a huge DerivativeValue the first time (PID_Prev_Input = 0)
    PID_First_Time[1] = 0;
    PID_Prev_Input[1] = temp[1];
  }
  DerivativeValue = (temp[1] - PID_Prev_Input[1]) * PID_Kd[1];
  PID_Prev_Input[1] = temp[1];

  // --- calculate total ---
  Result = ErrValue + PID_Integrated[1] - DerivativeValue; // mind the minus sign!!!
  // limit it to output minimum and maximum
  if (Result < PID_MinOutput[1]) 
    Result = PID_MinOutput[1];
  if (Result > PID_MaxOutput[1])
    Result = PID_MaxOutput[1];
  return (Result);
}



int PID_Calculate2(int const setpoint[2], int temp[2])
{
  int Err, ErrValue, DerivativeValue, Result;


  Err = eepromGetData(setpoint[2]) - temp[2];

  // --- calculate proportional value ---
  ErrValue  = Err * PID_Kp[2];

  // --- Calculate integrated value ---
  PID_Integrated[2] = PID_Integrated[2] + (Err * PID_Ki[2]);
  // limit it to output minimum and maximum
  if (PID_Integrated[2] < PID_MinOutput[2]) 
    PID_Integrated[2] = PID_MinOutput[2];
  if (PID_Integrated[2] > PID_MaxOutput[2])
    PID_Integrated[2] = PID_MaxOutput[2];

  // --- calculate derivative value ---
  if (PID_First_Time[2])
  {
    // to avoid a huge DerivativeValue the first time (PID_Prev_Input = 0)
    PID_First_Time[2] = 0;
    PID_Prev_Input[2] = temp[2];
  }
  DerivativeValue = (temp[2] - PID_Prev_Input[2]) * PID_Kd[2];
  PID_Prev_Input[2] = temp[2];

  // --- calculate total ---
  Result = ErrValue + PID_Integrated[2] - DerivativeValue; // mind the minus sign!!!
  // limit it to output minimum and maximum
  if (Result < PID_MinOutput[2]) 
    Result = PID_MinOutput[2];
  if (Result > PID_MaxOutput[2])
    Result = PID_MaxOutput[2];
  return (Result);
}
