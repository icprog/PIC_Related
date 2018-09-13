// *************** Includes ****************************************************    
#include "system.h"

// *************** Defines *****************************************************    
#define celcius         analogs[0]
#define farenheit       analogs[1]
#define down            analogs[2]
#define up              analogs[3]
#define solarInTemp     analogs[4]
#define solarOutTemp    analogs[5]



// *************** Main Routine ************************************************    
void main(void)
{
    SYSTEM_Initialize();
    
    uint16_t analogs[6]     =   {0};                    // array of analog readings (button presses and temperatures)
    
    float displayTemp, displayTemp2;                    // Calculate R of Thermistor, and Temp using SteinHart/Hart equation

//    unsigned char x[8]      =   {0,64,2,0,0,0,0,10};       // looping var, cycle counter, tempDisplay, C or F autoDisplay, display intensity loop counter, startup delay, Reset delay to allow reset to occur before brightness adjustment occurs
    
    char x                  =   0;                      // Looping Initializer
    
    unsigned char loop      =   64;                     // cycle (loop) counter
    
    char choice             =   2;                      // Display degrees C or degrees F, or cycle through both if choice is "2".
    
    char C_or_F             =   1;                      // Default Temperature Display is degrees F
    
    unsigned int bCount     =   0;                      // Loop counter for Backlight setting delay (to allow selection of both pads touched)
    
    unsigned char startDelay=   0;                      // Loop counter to delay touchpad input until ADC stable
    
    unsigned char resetDelay=   0;                      // Loop counter to delay backlight touchpad input until determined if two pads are touched for Reset
    
    unsigned char tPadCount =   10;                     // Touch pad counter (counts up or down from 10, to determine is one or both pads touched) (for C_or_F choice))
    
    
    uint16_t dutyCycle      = 1023;                     // display back light brightness
    
    PWM6_LoadDutyValue(dutyCycle);

    __delay_ms(300);
   
    LCD_Clear();
    
    LCDWriteStringXY(2,0,"A");
    __delay_ms(200);
    LCD_Write_String("L");
    __delay_ms(200);
    LCD_Write_String("O");
    __delay_ms(200);
    LCD_Write_String("H");
    __delay_ms(200);
    LCD_Write_String("A");
    __delay_ms(200);
    LCD_Write_String(" ");
    __delay_ms(200);
    LCD_Write_String("D");
    __delay_ms(200);
    LCD_Write_String("A");
    __delay_ms(200);
    LCD_Write_String("V");
    __delay_ms(200);
    LCD_Write_String("I");
    __delay_ms(200);
    LCD_Write_String("D");
    __delay_ms(200);
    LCD_Write_String(",");
    __delay_ms(200);
    LCDWriteStringXY(1,1,"S");
    __delay_ms(200);
    LCD_Write_String("O");
    __delay_ms(200);
    LCD_Write_String("P");
    __delay_ms(200);
    LCD_Write_String("H");
    __delay_ms(200);
    LCD_Write_String("I");
    __delay_ms(200);
    LCD_Write_String("E");
    __delay_ms(200);
    LCD_Write_String(" ");
    __delay_ms(200);
    LCD_Write_String("&");
    __delay_ms(200);
    LCD_Write_String(" ");
    __delay_ms(200);
    LCD_Write_String("K");
    __delay_ms(200);
    LCD_Write_String("I");
    __delay_ms(200);
    LCD_Write_String("D");
    __delay_ms(200);
    LCD_Write_String("S");
    __delay_ms(200);
    LCD_Write_String("!");
    __delay_ms(5000);
    
    LCD_Clear();

    PWM6_LoadDutyValue(dutyCycle);
        

    while (1)
    {
//        LCDWriteIntXY(7,1,choice,1,0,0);
        for(x=0;x<6;x++) analogs[x]=readAnalog(x);
        
        if(analogs[0]<1020)tPadCount+=1;
            
            
        if(analogs[1]<900)tPadCount-=1;
            
        if(tPadCount<1)
        {
            choice=1;
            LCD_Clear();
            LCDWriteStringXY(0,0,"You Chose ");
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCDWriteStringXY(0,1,"for User Display");
            tPadCount=10;
            __delay_ms(1000);
            LCD_Clear();
        }
        
        if(tPadCount>19)
        {
            choice=0;
            LCD_Clear();
            LCDWriteStringXY(0,0,"You Chose ");
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCDWriteStringXY(0,1,"for User Display");
            tPadCount=10;
            __delay_ms(1000);
            LCD_Clear();
        }
        
        if(analogs[0]<1020&&analogs[1]<970)
        {
            tPadCount=10;
            choice=2;
            LCD_Set_Cursor(0,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
            LCD_Write_Char('&');
            LCD_Write_Char(' ');
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCD_Write_String(" Chosen ");
            
            LCDWriteStringXY(0,1,"for User Display");
            __delay_ms(100);
            LCD_Clear();
        }
        
        
        
        startDelay+=1;
        
        if(startDelay>254)
        {
            startDelay=254;
            
            if(down<900&&up<900)RESET();
            
            if(down<900)
            {
                resetDelay+=1;
                
                if(resetDelay>20)
                {
                    while(down<975)
                    {
                        down=ADCRead(4);
                        
                        if(bCount<1)LCD_Clear();
                        bCount+=1;

                        if(dutyCycle>0)dutyCycle-=1;
                
                        LCDWriteStringXY(0,0,"   BackLight   ");
                        LCDWriteStringXY(0,1,"Intensity: ");
                        LCD_Write_Int(dutyCycle/10,-1,0,0);
                        LCD_Write_Char('%');
                        LCD_Write_Char(' ');
                        PWM6_LoadDutyValue(dutyCycle);
                    }
                    bCount=0;
                    __delay_ms(1000);
                    LCD_Clear();
                    resetDelay=0;
                }
            }

            if(up<900)
            {
                resetDelay+=1;
                
                if(resetDelay>20)
                {
                    while(up<975)
                    {
                        up=ADCRead(5);

                        if(bCount<1)LCD_Clear();
                        bCount+=1;

                        if(dutyCycle<1009)dutyCycle+=1;
                
                        LCDWriteStringXY(0,0,"   BackLight   ");
                        LCDWriteStringXY(0,1,"Intensity: ");
                        LCD_Write_Int(dutyCycle/10,-1,0,0);
                        LCD_Write_Char('%');
                        LCD_Write_Char(' ');
                        PWM6_LoadDutyValue(dutyCycle);
                    }
                    bCount=0;
                    __delay_ms(1000);
                    LCD_Clear();
                    resetDelay=0;
                }
            }
        }

// *************** Calculate & Display Temp ************************************   
        
        displayTemp = (tempCalc(solarInTemp))-6;
        
        displayTemp2 = tempCalc(solarOutTemp);

        if(loop>254)
        {
            tPadCount=10;
            LCDWriteStringXY(0,0,"In");
            LCD_Write_Char(1);
            LCD_Write_String("Solar");
            
            LCDWriteStringXY(0,1,"Out");
            LCD_Write_Char(1);
            LCD_Write_String("Pool");
  
            if(C_or_F==0)
            {
                LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('C');
                LCD_Write_Char(' ');
            
                LCDWriteIntXY(9,1,(int)displayTemp2,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('C');
                LCD_Write_Char(' ');
            }
            
            if(C_or_F==1)
            {
                displayTemp = displayTemp*9/5+320;          // Display Temperature in DegF
                displayTemp2 = displayTemp2*9/5+320;        // Display Temperature in DegF

                LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('F');
                LCD_Write_Char(' ');
            
                LCDWriteIntXY(9,1,(int)displayTemp2,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('F');
                LCD_Write_Char(' ');
            }
            
            
            if(choice==0)C_or_F=0;

            if(choice==1)C_or_F=1;

            if(choice==2)C_or_F=1-C_or_F;
/*            LCDWriteIntXY(0,0,analogs[0],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,0,analogs[1],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(11,0,analogs[2],-1,0,0);
            LCD_Write_Char(' ');

            LCDWriteIntXY(0,1,analogs[3],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,1,analogs[4],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(11,1,analogs[5],-1,0,0);
            LCD_Write_Char(' ');
            
  */          
            loop=0;
        }
        loop+=1;
    }
}