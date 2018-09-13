#include "user.h"
#include "lcd.h"


uint8_t  halfSec, lastState, toggle = 2;
extern uint8_t mainTimer;

// ***************************************************************************************************************************************************************
void heartBeat(void)
{
    halfSec = RCFGCALbits.HALFSEC;
    
    
    if (halfSec == 0)                                                           //If halfSec is 0
    {
        if (halfSec != lastState)                                               //If halfSec changed since last read
        {
            toggle = 3 - toggle;        //toggle = (a + b) - toggle, set toggle to either a or b, and it toggles between them
            LCD_Set_Cursor(3,19);
            LCD_Write_Char(toggle);                                                  //Display HeartBeat Symbol Open Heart
            mainTimer += 1;;                                                    //Increment the OutState Counter
        }
    }
    lastState = halfSec;                //And set them equal to each other, so, it doesn't count again next time through
}



void ADCInit(void)
{
    // ADSIDL disabled; ASAM disabled; FORM Absolute decimal result, unsigned, right-justified; MODE12 enabled; ADON enabled; DONE disabled; SAMP disabled; SSRC Clearing sample bit ends sampling and starts conversion; 

    AD1CON1 = 0x8400;

    // OFFCAL disabled; ALTS disabled; PVCFG AVDD; BUFM disabled; BUFREGEN disabled; NVCFG0 AVSS; SMPI 1; CSCNA disabled; 

    AD1CON2 = 0x0000;

    // ADRC FOSC/2; SAMC 0; EXTSAM disabled; ADCS 5; 

    AD1CON3 = 0x0005;

    // CH0SA AN0; CH0SB AN0; CH0NB AVSS; CH0NA AVSS; 

    AD1CHS = 0x0000;

    // CSS3 disabled; CSS4 disabled; CSS5 disabled; CSS6 disabled; CSS7 disabled; CSS8 disabled; CSS9 disabled; CSS10 disabled; CSS11 disabled; CSS0 disabled; CSS12 disabled; CSS13 disabled; CSS2 disabled; CSS14 disabled; CSS1 disabled; CSS15 disabled; 

    AD1CSSL = 0x0000;

    // CSS16 disabled; CSS29 disabled; CSS17 disabled; CSS18 disabled; CSS27 disabled; CSS19 disabled; CSS28 disabled; CSS30 disabled; CSS21 disabled; CSS22 enabled; CSS20 disabled; CSS26 disabled; CSS23 disabled; 

    AD1CSSH = 0x0040;


//    adc_obj.intSample = AD1CON2bits.SMPI;

}

//***************************************************************************************************************************************************************

int ADCRead(ADC_CHANNEL channel)
{
    uint16_t result;
    AD1CHS = channel;
    AD1CON1bits.SAMP = 1;
    __delay_us(100);
//    __delay_us(400);
    AD1CON1bits.SAMP = 0;
    while(!AD1CON1bits.DONE)
    {
         IFS0bits.AD1IF = false;
    }
    result = ADC1BUF0;
    return result;
}

//***************************************************************************************************************************************************************

int TempCalc(int a)
{
    if(a < 819)
    {
        return 499;
    }
    else
    {
//    return ((a - 819)/3.276 - 500);       // - 500 for -50.0 to 50.0 Range
    return ((a - 819)/6.552);               // Range of 0.0 to 50.0 C
    }
}

//***************************************************************************************************************************************************************

int TempSetpoint(int b)
{
    int result = b;
    
    char TestKey;
    
    unsigned char timer = 0;
    
    __delay_ms(500);
    
    TestKey = MenuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = MenuRead();
        
        timer += 1;
        
        __delay_ms(175);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 100)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteStringXY(1,0,"Setpoint = ");
        LCDWriteDecIntXY(1,11,result,3);

        heartBeat();
        
        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 50)
                    {
                        result = 50;
                    }
                }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 350)
                    {
                        result = 350;
                    }
                }
            break;
            }
        }
        
        TestKey = 9;            // Ensure TestKey is set to KEY_NONE before exiting
    
    return (result);
}

//***************************************************************************************************************************************************************

unsigned char SetDeadband(unsigned char b)
{
    unsigned char result = b, TestKey = 9;

    unsigned char timer = 0;
    
    __delay_ms(500);
    
    TestKey = MenuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = MenuRead();
        
        timer += 1;
        
        __delay_ms(175);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 100)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        
        LCDWriteStringXY(3,0,"DeadBand = ");
        LCDWriteDecIntXY(3,11,result,2);

        heartBeat();
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 1;
                            
                if (result <= 2)
                    {
                        result = 2;
                    }
                }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
               if(result >= 50)
                    {
                        result = 50;
                    }
                }
            break;
            }
        }
        
        TestKey = 9;                            // Ensure TestKey is set to KEY_NONE before exiting
    
    return (result);
}

//***************************************************************************************************************************************************************


signed char SetBiasNeg15(signed char b)
{
    signed char result = b;
    
    char TestKey;
    
    unsigned char timer = 0;
    
    __delay_ms(500);
    
    TestKey = MenuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = MenuRead();
        
        timer += 1;
        
        __delay_ms(175);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 100)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }

        LCDWriteStringXY(1,0,"-15 Bias = ");
        LCDWriteDecIntXY(1,11,result,2);

        heartBeat();

        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 0)
                    {
                        result = 0;
                    }
                }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 50)
                    {
                        result = 50;
                    }
                }
            break;
            }
        }
        
        TestKey = 9;            // Ensure TestKey is set to KEY_NONE before exiting
    
    return (result);
}

//***************************************************************************************************************************************************************


signed char SetBiasNeg25(signed char b)
{
    signed char result = b;
    
    char TestKey;
    
    unsigned char timer = 0;
    
    __delay_ms(500);
    
    TestKey = MenuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = MenuRead();
        
        timer += 1;
        
        __delay_ms(175);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 100)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteStringXY(3,0,"-25 Bias = ");
        LCDWriteDecIntXY(3,11,result,2);

        heartBeat();

        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 0)
                    {
                        result = 0;
                    }
                }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 70)
                    {
                        result = 70;
                    }
                }
            break;
            }
        }
        
        TestKey = 9;                                                            // Ensure TestKey is set to KEY_NONE before exiting
    
    return (result);
}


//***************************************************************************************************************************************************************

bool SetOutput(bool Out, int SetPoint, signed char Bias, int ProcessVariable, unsigned char Deadband)
{
    if (ProcessVariable <= SetPoint + Bias)                                     //Turn on Output if PV < SP + Bias.
        return 1;
    else
    if (ProcessVariable >= SetPoint + Bias + Deadband)                          //Turn off Output if PV >= SP + Bias + Deadband
        return 0;
    else
        return Out;                                                             //All other cases, leave it as it was.
    
}

//***************************************************************************************************************************************************************
