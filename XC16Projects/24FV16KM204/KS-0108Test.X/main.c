#include <xc.h>
#include "system.h"
#include "glcd.h"

int main(void)
{
//    int mine = 12345;

    InitApp();
    init_lcd();

    while(1)
    {
 //       cls();
/*        LCDWriteStringXY(0,0, "ABCDEFGHIJKLMNOP");
        LCDWriteStringXY(0,16,"QRSTUVWXYZabcdef");
        LCDWriteStringXY(1,0, "ghijklmnopqrstuv");
        LCDWriteStringXY(1,16,"wxyz0123456789!@");
        LCDWriteStringXY(2,0, "#$%^&*()_+=-?><|");
        LCDWriteStringXY(2,16,"}{][~`/|\")");
        
        LCDWriteStringXY(4,2,"I guess the fo");
        LCDWriteStringXY(4,16,"nts are not");
        LCDWriteStringXY(5,5,"100% yet!!");
        __delay_ms(12000);

        loadimg(&toplogo_bmp[0], 1024);             //Draw my logo(or start screen)
        __delay_ms(2000);
    
        cls();
        
        LCDWriteIntXY(0,10,mine,-1);
        __delay_ms(1000);
        LCDWriteStringXY(5,0, "DAVE likes progr");
        LCDWriteStringXY(5,16,"amming!!");
        __delay_ms(2000);
        LCDWriteStringXY(2,0,"DAVE is an OK'is");
        LCDWriteStringXY(2,16,"h programmer!!??");
        __delay_ms(2000);
        LCDWriteStringXY(3,7,"FUCK!!, O");
        LCDWriteStringXY(3,16,"K, it works now!");
        __delay_ms(2000);
        LCDWriteStringXY(7,0,"Oh, and Damon SU");
        LCDWriteStringXY(7,16,"CKS!!!");
        __delay_ms(4000); */
    }
    return (1);
}
