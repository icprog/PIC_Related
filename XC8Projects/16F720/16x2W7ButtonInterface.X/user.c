
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include "system.h"
#include "user.h"


void Init()
 {                           // Initialization Function

    TRISA = 0b00010100;                 // 0 = output 1 = input
    ANSELA = 0b00010100;                // RA2 and RA4 as Analog (0 = Digital, 1 = Analog)
    PORTA = 0b00000000;                 // Set all port A register to 1, 1 = off, 0 = on, (if sinking)

    TRISB = 0b00000000;                 // 0 = output, 1 = input
    ANSELB = 0b00000000;                // No Analogs (0 = Digital, 1 = Analog)
    PORTB = 0x00;                       // Set all port B register to 0, 1 = off, 0 = on

    TRISC = 0x00;                       // 0 = output 1 = input
    ANSELC = 0x00;                      // 0 = Digital, 1 = Analog
    PORTC = 0xff;                       // Set all port C register to 1, 1 = off, 0 = on


    FVRCON = 0xf3;

}

void ADCInit(){
        ADCON1 = 0x10;                   // Set ADC conversion clock FOSC/8 See Page 80
}
unsigned char ADCRead(unsigned char ch)  //Function to Read given ADC channel (0-14)

{
    ADCON0=0x00;                         // Set ADCON0 to all zero's
    ADCON0=(ch<<2);                      // Select ADC Channel (write the decimal value of ch, Left shifted two places, writing to Bits 5,4,3 and 2)
    ADON=1;                              // Enable the ADC module (on selected channel)
    delay_us(1500);                      // Delay 1500 us to allow the ADC cap to charge
    GO_nDONE=1;                          // Start conversion
    while(GO_nDONE);                     // Wait for the conversion to finish
    ADON=0;                              // Disable the ADC
    return ADRES;                        // Return the Analog value
}


unsigned char TempCalc(unsigned char a)
{
    if(a < 51)
    {
        return 255;
    }
    else
    {
//    return ((a - 819)/3.276 - 500);       // - 500 for -50.0 to 50.0 Range
    return (a - 51)/ 7;               // Range of 0.0 to 50.0 C
    }
}

//***************************************************************************************************************************************************************

unsigned char TempSetpoint(unsigned char b)
{
    unsigned char result = b;
    
    char TestKey;
    
    unsigned char timer = 0;
    
    unsigned char DisplayValue, Display2;
    
    char s [20];

    delay_ms(500);
    
    TestKey = MenuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = MenuRead();
        
        timer += 1;
        
        delay_ms(175);            // 150 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 100)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            goto Exit;
        }
        
        DisplayValue = result;
        
        Display2 = DisplayValue%10;
        
        DisplayValue = DisplayValue/10;
        
//***************************************************************************************************************************************************************

//        sprintf(s,"Setpoint = %02d.%d", DisplayValue, Display2);
  //      LCD_Set_Cursor(1,0);
    //    LCD_Write_String(s);

//***************************************************************************************************************************************************************
        
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
                            
                if(result >= 250)
                    {
                        result = 250;
                    }
                }
            break;
            }
        }
        
        Exit:;
        
        TestKey = 9;            // Ensure TestKey is set to KEY_NONE before exiting
    
    return (result);
}

//***************************************************************************************************************************************************************

unsigned char SetDeadband(unsigned char b)
{
    unsigned char result = b, TestKey = 9, DisplayValue, Display2;
    
    unsigned char timer = 0;
    
    char s [20];

    delay_ms(500);
    
    TestKey = MenuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = MenuRead();
        
        timer += 1;
        
        delay_ms(175);            // delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 100)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            goto Exit;
        }
        
        DisplayValue = result;
        
        Display2 = DisplayValue%10;
        
        DisplayValue = DisplayValue/10;

//***************************************************************************************************************************************************************
        
//        sprintf(s,"DeadBand = %01d.%d", DisplayValue, Display2);
  //      LCD_Set_Cursor(3,0);
    //    LCD_Write_String(s);
//***************************************************************************************************************************************************************
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 1;
                            
                if (result <= 5)
                    {
                        result = 5;
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
        
        Exit:;
        
        TestKey = 9;                            // Ensure TestKey is set to KEY_NONE before exiting
    
    return (result);
}


//***************************************************************************************************************************************************************

unsigned char SetOutput(unsigned char Out, unsigned char SetPoint, char Bias, unsigned char ProcessVariable, unsigned char Deadband)
{
    if (ProcessVariable <= SetPoint + Bias)
        return 1;
    else
    if (ProcessVariable >= SetPoint + Bias + Deadband)
        return 0;
    else
        return Out;
    
}

//***************************************************************************************************************************************************************

