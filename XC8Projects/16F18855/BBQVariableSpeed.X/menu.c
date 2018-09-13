#include    "menu.h"
#include    "lcd.h"

#define Kp_offset               0
#define Ki_offset               1
#define Kd_offset               2

#define pitSetpoint             setpoint[0]
#define backLightSetpoint       setpoint[1]
#define upKey                   RB0
#define downKey                 RB1
#define enterKey                RB2
#define delayNumber             30                          // Number of cycles for keypress delay at 200ms, before switch to 10ms delay

uint16_t lowRangeSet[2]         =   {750,10};               // lowrangeSet[0] is Pit Temp setpoint lower limit, lowrangeSet[1] is backlight intensity

uint16_t highRangeSet[2]        =   {2750,1023};            // highRangeSet[0] is Pit Temp setpoint upper limit, highRangeSet[1] is backlight intensity

uint16_t setpoint[2]            =   {2150,523};             // default startup setpoints for Pit temp & backlight

char const *desc[]              =   {" Pit Temp:","BackLight:"};

unsigned char loop                  =   64;

int menuDelay                       =   0;
    
char delayCount                     =   0;

char key                            =   0;

char choice                         =   0;

char testKey                        =   0;

int timer                           =   0;

char timer2                         =   0;



char readKey(void)
{
    if(downKey)
    {
        if(key>0)key-=1;
    }
    
    if(upKey)
    {
        if(key<1)key+=1;
    }
    
    return key;
}

void menuChoice(void)
{
    while(enterKey != 1)
    {
        choice = readKey();
                
        if(timer > 4000)
        {
            timer = 0;
            goto Exit;                                             
        }
        
        if(timer2>125)LCDWriteStringXY(0,0,"Up/Down to Alter")else LCDWriteStringXY(0,0,"Enter to Select ");
        
        LCDWriteStringXY(0,1,desc[choice]);
        
        if(timer2>249)timer2=0;
        
        timer+=1;
        timer2+=1;
    }
    timer=0;
    timer2=0;
    
    __delay_ms(1000);
    
    if(choice==0)LCDWriteIntXY(10,1,setpoint[choice],-1,1,0)else LCDWriteIntXY(10,1,setpoint[choice],-1,0,0);
    
    __delay_ms(2000);
        
    while(enterKey != 1)
    {
        if(timer > 4000)
        {
            timer = 0;
            LCDWriteStringXY(0,0,"   Good-Bye!!   ");
            __delay_ms(2000);
            goto Exit;                                             
        }
        __delay_ms(2);
        timer+=1;
                    
        if(upKey)
        {
            delayCount+=2;
//            if(delayCount==2)setpoint[choice]+=1;
            setpoint[choice]+=1;
            if(setpoint[choice]>highRangeSet[choice])setpoint[choice]=highRangeSet[choice];
            if(choice==0)LCDWriteIntXY(10,1,setpoint[choice],-1,1,0)else LCDWriteIntXY(10,1,setpoint[choice],-1,0,0);
            LCD_Write_Char(' ');
            menuDelay=1255;
            if(delayCount<delayNumber)
            {
                __delay_ms(150);
            }
            if(delayCount>(delayNumber+10))delayCount=(delayNumber+10);
            
            timer=0;
        }
        
        
        if(downKey)
        {
            delayCount+=2;
            setpoint[choice]-=1;
            if(setpoint[choice]<=lowRangeSet[choice])setpoint[choice]=lowRangeSet[choice];
            if(choice==0)LCDWriteIntXY(10,1,setpoint[choice],-1,1,0)else LCDWriteIntXY(10,1,setpoint[choice],-1,0,0);
            LCD_Write_Char(' ');
            menuDelay=1255;

            if(delayCount<delayNumber)
            {
                __delay_ms(150);
            }
            
            if(delayCount>(delayNumber+10))delayCount=(delayNumber+10);
            
            timer=0;
        }
        
        PWM7_LoadDutyValue(backLightSetpoint);

        
        if(delayCount>0)delayCount-=1;
        
        if(!(downKey || upKey))
        {
            if(menuDelay>0)
            {
                menuDelay-=1;
            }
        }
    }        
    Exit:
    timer=0;
    loop=254;
    LCD_Clear();
//    PWM6MD      =   0;                                                          // Re-enable PWM6 Module (viperFanOut) 
}