// **************** Includes ***********\****************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
int internalKp[]                = {   50,   50,  50};   // Controller Gain      (inverse of Proportional Band)
int internalKi[]                = {   15,   15,  15};   // Controller Integral Reset/Unit Time, determined by how often PID is calculated
int internalKd[]                = {   25,   25,  25};   // Controller Derivative (or Rate))
static float pidIntegrated[3]   = {    0,    0,   0};
long pidPrevError[3]            = {    0,    0,   0};
long pidPrevInput[3]            = {    0,    0,   0};
int integralMinOutput[3]        = {    0,    0,   0};
int integralMaxOutput[3]        = {   50,  100,  40};   
int pMinOutput[3]               = {-7811, -575,   0};   // Minimum output limit of Proportional Action
int pidMinOutput[3]             = { -275,    0,   0};   // Minimum output limit of Controller
int pidMaxOutput[3]             = { 7811, 1812, 205};   // Max limit of Controller (If steamSwitch is on, OC3R has 6000 summed to its output, so 1812+6000=7812 Out)
int16_t bias[3]                 = {  275,    0,  22};   // Value summed onto Output(Should be Output required to maintain Setpoint with no external upsets) 
extern int8_t tuning[3];                                // Set to a 1 when tuning    


void Init_PID(int8_t controller, int pidKp, int pidKi, int pidKd)
{
    internalKp[controller]              = (float)pidKp;
    internalKi[controller]              = (float)pidKi;
    internalKd[controller]              = (float)pidKd;
    pidIntegrated[controller]           = 0;
    pidPrevInput[controller]            = 0;
}

// *************** PID_Calculate Runs faster if called more often **************    
int PID_Calculate(unsigned char controller, unsigned int setpoint, unsigned int temp)
{
    int result;
    float  error, errorValue;
    long derivativeValue;
        
// **************** Calculate Gain *********************************************    
    error=(long)setpoint-temp;                                                  // error calculation
 
    errorValue=error*internalKp[controller]/10;                                 // Calculate proportional value
    
    if(errorValue<pMinOutput[controller])errorValue=pMinOutput[controller];
    
    if(errorValue>pidMaxOutput[controller])errorValue=pidMaxOutput[controller];

// **************** Calculate Integral *****************************************    
    pidIntegrated[controller]+=((error*internalKi[controller])/600);            // Calculate integral value in repeats/minute

    if (pidIntegrated[controller]<integralMinOutput[controller])                // limit output minimum value
    {
        pidIntegrated[controller]=integralMinOutput[controller];
    }
    
    if (pidIntegrated[controller]>integralMaxOutput[controller])                // limit output maximum value 
    {
        pidIntegrated[controller]=integralMaxOutput[controller];
    }

 // *************** Calculate Derivative **************************************** 
        derivativeValue=((long)error-pidPrevError[controller])*internalKd[controller];
        
        if(derivativeValue>pidMaxOutput[controller])derivativeValue=pidMaxOutput[controller];
        
        if(derivativeValue<-200)derivativeValue=-200;

        pidPrevError[controller] = (long)error;

// *************** Calculate Final Output **************************************    
    result=(int)errorValue+(int)pidIntegrated[controller]+(int)derivativeValue; // Calculate total to send to Output
    
    if (result<pidMinOutput[controller])result=pidMinOutput[controller];        // limit output minimum value
    
    if (result>pidMaxOutput[controller])result=pidMaxOutput[controller];        // limit output maximum value 
    
    if(result+bias[controller]<pidMaxOutput[controller])result+=bias[controller];

    else result=pidMaxOutput[controller];

    if(tuning[0] || tuning[1] || tuning[2])
    {
        LCDWriteStringXY(0,0,"MV");
        LCDWriteIntXY(16,0,temp,4,1,0);
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
    return (result);
}