// used to test ports for LCD
// 
#define USE_HEARTBEAT 1
#define DATA_LEN 8
#define DELAY_TIME 10
#include "../lib/include/pic24_all.h"
#define LCD_WR              LATCbits.LATC1        // LCD Write control line pin number p6
#define LCD_CE             LATCbits.LATC2       // LCD Enable control line pin number p7
#define LCD_RST             LATCbits.LATC3        // LCD RST_ line p8
#define LCD_CD              LATAbits.LATA14       // LCD Control/data Select line p43
#define LCD_RD              LATAbits.LATA15       // LCD Read control line  pin number p44

#define STA0               LATAbits.LATA0        // Check command execution capability p17
#define STA1               LATAbits.LATA1        // Check data read/write capability p38
#define STA2               LATAbits.LATA2        // Check Auto mode data read capability p58
#define STA3               LATAbits.LATA3        // Check Auto mode data write capability p59
#define STA4               LATAbits.LATA4        // Check controller operation capability p60
#define STA5               LATAbits.LATA5        // Error flag. Used for screen peek and screen copy p61
#define STA6               LATAbits.LATA6        // Check the blink condition p91
#define STA7               LATAbits.LATA7        // Check the blink condition p92

    //tabs here
int main (void) 
{
    int i;
    UCHAR txchar;
    UCHAR txchar2;
    txchar = 0x21;
    configClock();        //no UART for slave
    configHeartbeat();
    configDefaultUART(DEFAULT_BAUDRATE);
    CONFIG_RC2_AS_DIG_OUTPUT(); // CE
    CONFIG_RA15_AS_DIG_OUTPUT(); // RD
    CONFIG_RC1_AS_DIG_OUTPUT();  // WR
    CONFIG_RA14_AS_DIG_OUTPUT(); // CD
    CONFIG_RC3_AS_DIG_OUTPUT(); // RESET

   CONFIG_RA0_AS_DIG_OUTPUT();
   CONFIG_RA1_AS_DIG_OUTPUT();
   CONFIG_RA2_AS_DIG_OUTPUT();
   CONFIG_RA3_AS_DIG_OUTPUT();
   CONFIG_RA4_AS_DIG_OUTPUT();
   CONFIG_RA5_AS_DIG_OUTPUT();
   CONFIG_RA6_AS_DIG_OUTPUT();
   CONFIG_RA7_AS_DIG_OUTPUT();

    txchar = 0;
    while(1)
    {
    outChar(txchar);
    LCD_CE = 0;
    LCD_RD = 0;
    LCD_WR = 0;
    LCD_CD = 0;
    LCD_RST = 0;
/*
    STA0 = 0;
    STA1 = 0;
    STA2 = 0;
    STA3 = 0;
    STA4 = 0;
    STA5 = 0;
    STA6 = 0;
    STA7 = 0;
*/
    DELAY_MS(DELAY_TIME);
    LCD_CE = 1;
    LCD_RD = 1;
    LCD_WR = 1;
    LCD_CD = 1;
    LCD_RST = 1;
/*
    STA0 = 1;
    STA1 = 1;
    STA2 = 1;
    STA3 = 1;
    STA4 = 1;
    STA5 = 1;
    STA6 = 1;
    STA7 = 1;
*/
    txchar2++;
    LATA &= 0xff00;
    LATA |= 0x00ff & txchar2;
    DELAY_MS(DELAY_TIME);
    if(++txchar > 0x7e)
       txchar = 0x21;
    }
}
