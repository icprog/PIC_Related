#include    "usermenu.h"
#include    "menu.h"

extern char pull;

void Pull(void)
{
    while(pull<1)
    {
        pull+=1;
    }
    
}
void userMenu(void)
{
    char testKey2   =   None;
    int timer2      =   0;
    int setRangeL[]         = {1750,2650,1850};         // Set Point Low Limits      FIX Group Setpoint back to Min 180
    int setRangeH[]         = {2100,3000,2150};         // Set Point High Limits
    
    extern unsigned int setpoint[];                     //setpoint EEPROM Address "offset" values
    extern int const Kp[];
    extern int const Ki[];
    extern int const Kd[];
    extern char *desc[];

    LCDClear();
    LCDBitmap(&menu1[0], 5,84);         //Draw Menu1
    gotoXY(1,4);
    LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX

    __delay_ms(1000);
            
    while(testKey2==None)
    {
        LCDWriteStringXY(0,1,"\"Time\" Sets Time");
        
        LCDWriteStringXY(0,2,"\"ST\\SP\" for Auto Set");
        
        LCDWriteStringXY(0,3,"\"PID\" for Tuning");
        
        testKey2 = readButton();
        timer2 +=1;
        __delay_ms(10);
 
        if (timer2 > 500)
        {
            timer2 = 0;
            LCDClear();
            LCDBitmap(&menu0[0], 5, 59);//Draw Menu0
            gotoXY(1,4);
            LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
            goto Exit;
        }
    }
            
// ******************************************************************************
    if(testKey2==Menu)
    {
        SetTime();
          
        timer2 = 0;

        LCDBitmap(&menu2[0], 5, 84);                 //Draw Menu1
        gotoXY(1,4);
        LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
        __delay_ms(500);
    }
            
// ******************************************************************************
    if(testKey2==Down)
    {
        writeStartStopTimes();
    }
    

// ******************************************************************************
    if(testKey2==Enter)
    {
        goto Exit;
    }
            
// ******************************************************************************
    if(testKey2==Up)
    {
        int8_t choice = 0;
           
        timer2 = 0;

        LCDClear();
        LCDBitmap(&menu2[0], 5, 84);    //Draw Menu2
        gotoXY(1,4);
        LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX

        while(testKey2 != Enter)
        {
            testKey2 = readButton();
            __delay_ms(10);
                
            if(timer2 > 500)
            {
                timer2 = 0;
                goto Exit;                  
            }

            switch(testKey2)
            {
                case Down:
                {
                    choice -=1;
                            
                    if (choice < 0)
                    {
                        choice = 0;
                    }
                }
                break;

                        
                case Up:
                {
                    choice += 1;
                            
                    if(choice > 2)
                    {
                        choice = 2;
                    }
                }
                break;
                    
                case Menu:
                {
                    goto Exit;
                }
                break;
            }

            LCDWriteStringXY(0,0,"PID Settings for");
            LCDWriteStringXY(0,1,desc[choice]);
            LCDWriteStringXY(0,3,"Up/Dn Keys to Change");
            LCDWriteStringXY(0,4,"  \"Enter\" to Accept ")

            timer2 += 1;
        }
            
        LCDClear();
        LCDBitmap(&menu2[0], 5, 84);              //Draw Menu2
        gotoXY(1,4);
        LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
        LCDWriteStringXY(0,1,"SetPoint = ");
        eepromPutData(setpoint[choice], setParameter(44,1,setRangeL[choice],setRangeH[choice],eepromGetData(setpoint[choice])));
            
        LCDWriteStringXY(0,2,"Gain =");
        eepromPutData(Kp[choice], setParameter(44,2,0,200,eepromGetData(Kp[choice])));

        LCDWriteStringXY(0,3,"Integral =");
        eepromPutData(Ki[choice], setParameter(44,3,0,500,eepromGetData(Ki[choice])));

        LCDWriteStringXY(0,4,"Derivative =");
        eepromPutData(Kd[choice], setParameter(44,4,0,500,eepromGetData(Kd[choice])));
            
            
        Init_PID(choice,eepromGetData(Kp[choice]),eepromGetData(Ki[choice]),eepromGetData(Kd[choice]));                

        timer2 = 0;

        Exit:
        LCDClear();
        LCDBitmap(&menu0[0], 5, 59);            //Draw Menu0
        gotoXY(1,4);
        LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
    }
}