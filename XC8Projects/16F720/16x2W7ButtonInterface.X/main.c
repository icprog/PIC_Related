/* Built on a Microchip PIC 16F720 SOIC Micro
 * Inlet temperature connected to AN2 (pin 17)
 * Outlet temperature connected to AN3 (pin 3)
 * Thermistors ranged for -27 degF to 208 degF
 */


#include <xc.h>
#include "system.h"
#include "lcd_hd44780_pic16.h"
#include "configuration_bits.c"
#include "user.h"
#include "AnalogKeyInput.h"

void main ()
{
    ConfigureOscillator();

    Init();                                                     //  Initialize TRIS,ANSEL,PORT,OSCTUNE, and OSC Frequency

    ADCInit();
    
    delay_ms(1750);                                              //Startup delay to allow LCD to Power-Up

    LCDInit(LS_NONE);                                           // Initialize the LCD Module
    delay_ms(1500);

    LCDClear();
    
        unsigned char i, timer = 0;             // timer used to count up time in a loop, to auto exit if user in a menu too long

        unsigned char OldTemp[2];
        
        unsigned char Temp[2];

//        unsigned char Test[] = {ADCRead(2), ADCRead(3)};
        unsigned char Test[2];
 

    while (1)                                                   //  Or, while true, so, Run continuously
    {
        Test[0] = ADCRead(2);
        
        Test[1] = ADCRead(3);
        

        for(i = 0;i<2;i++)
        {
        Temp[i] = TempCalc(Temp[i]);
        
        if(Temp[i] > OldTemp[i] + 1 || Temp[i] < OldTemp[i] - 1)
        {
            Temp[i] = ((OldTemp[i] + Temp[i])/2);
            OldTemp[i] = Temp[i];
        }
        else Temp[i] = OldTemp[i];
        }

        
        for (i=0;i<12;i++)
        {
 //           Out[i] = SetOutput(Out[i], Set[i], Bias[i], Temp[i], Deadband[i]);
        }


   //     OutSum = Out[0] + Out[1] + Out[2] + Out[3] + Out[4] + Out[5] + Out[6] + Out[7] + Out[8] + Out[9] + Out[10] + Out[11];
        
        
/*        if(OutSum == 1)
        {
            for(i=0;i<12;i++)
            {
                if (Temp[i] <= Set[i] + Deadband[i])
                {
                    Output[i] = 1;
                }
                else
                {
                    Output[i] = 0;
                }
            }
        }
        else
        {
            for (i=0;i<12;i++)
            {
                Output[i]= 0;
            }
        }
        
        DeckFloor = Output[0];
  */      
        
 /*       
        TestKey = MenuRead();

        sprintf(s,"%02d/%02d/%02d    %02d:%02d:%02d", time.year, time.month, time.day, time.hour, time.minute, time.second);
        LCD_Set_Cursor(0,0);
        LCD_Write_String(s);

        LCDWriteStringXY(0,9,WeekDay[time.weekday]);

//        LCDWriteStringXY(3,0," Enter to Set Time  ");
//        sprintf(s,"%d %d %d %d %d %d %d %d %d%d%d%d", Out[0], Out[1], Out[2], Out[3], Out[4], Out[5], Out[6], Out[7], Out[8], Out[9], Out[10], Out[11]);
        sprintf(s,"%03d %05d %03d %04d", Temp[0], ADCRead(5), Temp[1], Temp[3]);
        LCD_Set_Cursor(3,0);
        LCD_Write_String(s);

//        sprintf(s,"%04d %04d %04d %04d", Temp[2], OldTemp[2], Temp[3], OldTemp[3]);
  //      LCD_Set_Cursor(2,0);
    //    LCD_Write_String(s);

        LCDWriteStringXY(2,0,"Menu Key to Set Temp");
         
        sprintf(s,"%03d %03d %02d %d %d %d", Set[0], Temp[0], Deadband[0], Out[0], OutSum, Output[0]);
        LCD_Set_Cursor(1,0);
        LCD_Write_String(s);
        

        if (TestKey == KEY_ENTER)
        {
            __delay_ms(750);
            TestKey = 9;
            SetTime();
        }

        if (TestKey == KEY_MENU)
        {
            unsigned char choice = 0;
//            unsigned char choice[][20] ={"Deck Floor Set?     ","Enter Key for Yes   ","Front Entrance Set? ","Enter Key for Yes   ","Utility Rm Flr Set? ","Enter Key for Yes   ",};

            while(TestKey != KEY_ENTER)
            {
                TestKey = MenuRead();
                
                __delay_ms(175);
                   
                timer += 1;
                    
                if(timer > 125)
                {
                    timer = 0;
                    TestKey = KEY_ENTER;
                }

                switch(TestKey)
                {
                    case KEY_DOWN:
                    {
                        choice +=1;
                            
                        if (choice > 12)
                        {
                            choice = 12;
                        }
                    }
                    break;
                        
                    case KEY_UP:
                    {
                        choice -= 1;
                            
                        if(choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;
                        
                }
                
                LCD_Clear();

                if(choice == 0)
                {
                    LCDWriteStringXY(0,0,"Deck Floor Set?     ");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }
            
                if(choice == 1)
                {
                    LCDWriteStringXY(0,0,"Front Entrance Set? ");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 2)
                {
                    LCDWriteStringXY(0,0,"Utility Rm Flr Set? ");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 3)
                {
                    LCDWriteStringXY(0,0,"Master Bath Flr Set?");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 4)
                {
                    LCDWriteStringXY(0,0,"Garage Floor Set?   ");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 5)
                {
                    LCDWriteStringXY(0,0,"Office Floor Set?   ");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 6)
                {
                    LCDWriteStringXY(0,0,"Craft Room Set?     ");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 7)
                {
                    LCDWriteStringXY(0,0,"Southeast Br Set?   ");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 8)
                {
                    LCDWriteStringXY(0,0,"Garage Floor Set?  8");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 9)
                {
                    LCDWriteStringXY(0,0,"9Deck Floor Set?   9");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 10)
                {
                    LCDWriteStringXY(0,0,"9Deck Floor Set?  10");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 11)
                {
                    LCDWriteStringXY(0,0,"9Deck Floor Set?  11");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }

                if(choice == 12)
                {
                    LCDWriteStringXY(0,0,"9Deck Floor Set?  12");
                    LCDWriteStringXY(2,0,"Enter Key for Yes   ");
                }
            }
            
            TestKey = 9;
            __delay_ms(100);
     
            if(choice == 0)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Deck Floor Temp ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }
                
            if(choice == 1)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Entrance Temp   ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }

            if(choice == 2)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Utility Rm Temp ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }

            if(choice == 3)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Deck Floor Temp ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }
                
            if(choice == 4)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Entrance Temp   ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }

            if(choice == 5)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Utility Rm Temp ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }

            if(choice == 6)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Deck Floor Temp ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }
                
            if(choice == 7)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Entrance Temp   ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }

            if(choice == 8)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Utility Rm Temp ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }

            if(choice == 9)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Deck Floor Temp ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }
                
            if(choice == 10)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Entrance Temp   ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }

            if(choice == 11)
            {
                LCD_Clear();
                LCDWriteStringXY(0,0,"Set Utility Rm Temp ");
                Set[choice] = TempSetpoint(Set[choice]);
                LCDWriteStringXY(2,0,"Set Deck Fl DeadBand");
                Deadband[choice] = SetDeadband(Deadband[choice]);
            }
            
            if(choice == 12)
            {
                LCD_Clear();
                TestKey = 9;
                __delay_ms(100);
            }
            LCD_Clear();
        }
        TestKey = 9;
        __delay_ms(100);
    }
*/
    }
}      //        E N D   O F   P R O G R A M

// Following should display a float on the LCD, unfortunately, the Code is too big for memory in 16F720
/*
void TempCheck()
{
    unsigned int tempin,tempout;
    const float tempread[] = {0};
//    const float tempread[] = {2825,754,2645,555,2445,355};    // This needs to be a propper look-up table

    ADCInit();

    LCDWriteStringXY(0,0,"T In:");
    LCDWriteStringXY(0,1,"T Out:");

    tempin = ADCRead(2);
    displaynum(100.9);


 //   tempout = ADCRead(3);
//    line = 1;
//    displaynum(tempread[tempout]);
}

void displaynum(float num)
{
    int num1,dn,hn,tn,on;

    num1 = num;
    num = num - num1;
    num = num/0.10;

    dn = num;
    dn+=48;

    hn = num1/100;
    hn+=48;
    num1 = num1%100;
    tn = num1/10;
    tn+=48;
    num1 = num1%10;
    on = num1;
    on+=48;

    LCDWriteIntXY(8,0,hn,1);
    LCDWriteIntXY(9,0,tn,1);
    LCDWriteIntXY(10,0,on,1);
    LCDWriteStringXY(11,0,".");
    LCDWriteIntXY(12,0,dn,2);
    LCDWriteStringXY(13,0,"%0F")  
}
*/

