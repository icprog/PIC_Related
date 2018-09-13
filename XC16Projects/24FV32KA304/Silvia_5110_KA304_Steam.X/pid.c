// **************** Includes ***********\****************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
int internalKp[]                = {   50,   50,  50};   // Controller Gain      (inverse of Proportional Band)
int internalKi[]                = {   15,   15,  15};   // Controller Integral Reset/Unit Time, determined by how often PID is calculated
int internalKd[]                = {   25,   25,  25};   // Controller Derivative (or Rate))
static float pidIntegrated[3]   = {    0,    0,   0};
long pidPrevError[3]            = {    0,    0,   0};
long pidPrevInput[3]            = {    0,    0,   0};
int integralMinOutput[3]        = { -500, -275, -25};
int integralMaxOutput[3]        = {  300,  200,  25};   
int pMinOutput[3]               = {-7811, -275,-120};   // Minimum output limit of Proportional Action
int pidMinOutput[3]             = { -275,    0,   0};   // Minimum output limit of Controller
int pidMaxOutput[3]             = { 7811, 1312, 205};   // Maximum output limit of Controller
int16_t bias[3]                 = {  275,    0,  21};   // Value summed onto Output(Should be Output required to maintain Setpoint with no external upsets) 
extern char tuning;                                     // Set to a 1 when tuning    
//extern int bits[7];                                     // steamPower Bit

//    int result;
  //  float  error, errorValue;
    //long derivativeValue;
    //int pidIntegral;

void Init_PID(int8_t controller, int pidKp, int pidKi, int pidKd)
{
    internalKp[controller]              = pidKp;
    internalKi[controller]              = pidKi;
    internalKd[controller]              = pidKd;
    pidIntegrated[controller]           = 0;
    pidPrevInput[controller]            = 0;
}

// *************** PID_Calculate Runs faster if called more often **************    
int PID_Calculate(unsigned char controller, unsigned int setpoint, unsigned int temp)
{
//    if(!bits[7]) pidMaxOutput[1]=500;                   // Limit steam PID Output until steam is at minimum setpoint(limit overshoot))
    int result;
    float  error, errorValue;
    long derivativeValue;
        
// **************** Calculate Gain *********************************************    
    error = (long)setpoint - temp;                                              // error calculation
 
    errorValue  = error * internalKp[controller]/10;                            // Calculate proportional value
    
    if(errorValue<pMinOutput[controller])
    {
        errorValue=pMinOutput[controller];
    }
    
    if(errorValue>pidMaxOutput[controller])
    {
        errorValue=pidMaxOutput[controller];
    }

// **************** Calculate Integral *****************************************    
    pidIntegrated[controller] += ((error * internalKi[controller])/60);         // Calculate integral value

    if (pidIntegrated[controller]< integralMinOutput[controller])               // limit output minimum value
    {
        pidIntegrated[controller]= integralMinOutput[controller];
    }
    
    if (pidIntegrated[controller]> integralMaxOutput[controller])                        // limit output maximum value 
    {
        pidIntegrated[controller]= integralMaxOutput[controller];
    }
//    pidIntegral=(int)pidIntegrated[controller];
// *************** Calculate Derivative **************************************** 
        derivativeValue=((long)error-pidPrevError[controller])*internalKd[controller];
        
        if(derivativeValue>pidMaxOutput[controller])
        {
            derivativeValue=pidMaxOutput[controller];
        }
        
        if(derivativeValue<-4000)
       {
            derivativeValue=-4000;
        }

        pidPrevError[controller] = (long)error;
        
  
// *************** Calculate Final Output **************************************    
    result = (int)errorValue + (int)pidIntegrated[controller] + (int)derivativeValue;   // Calculate total to send to Output
    
    if (result < pidMinOutput[controller])                              // limit output minimum value
    {
        result = pidMinOutput[controller];
    }
    
    if (result > pidMaxOutput[controller])                              // limit output maximum value 
    {
        result = pidMaxOutput[controller];
    }
    
    if(result+bias[controller]<pidMaxOutput[controller])
    {
        result+=bias[controller];
    }
    else
    {
        result=pidMaxOutput[controller];
    }

/*    if(tuning==1)
    {
        LCDWriteStringXY(0,1,"ERR");
        LCDWriteIntXY(16,1,error,4,0,0);
        LCDWriteCharacter(' ');
        LCDWriteStringXY(40,1,"P")
        LCDWriteIntXY(52,1,errorValue,5,0,0);
        LCDWriteCharacter(' ');
        LCDWriteStringXY(0,2,"I")
        LCDWriteIntXY(0,3,pidIntegrated[controller],5,0,0);            
        LCDWriteCharacter(' ');
        LCDWriteStringXY(32,2,"D")
        LCDWriteIntXY(32,3,derivativeValue,5,0,0);
        LCDWriteCharacter(' ');
        LCDWriteStringXY(58,2,"Out")
        LCDWriteIntXY(58,3,result,5,0,0); 
        __delay_ms(950);
    }
  */  
    return (result);
}