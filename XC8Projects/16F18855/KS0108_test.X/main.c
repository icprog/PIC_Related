#include <xc.h>
#include "system.h"
#include "glcd.h"



void main(void)
{
    Init();
    RA3 = 1;
    __delay_ms(1000);
    RA3 = 0;
    __delay_ms(1000);
 //                      _lcd_reset();
    lcd_screenon(0);
    lcd_cls();

    
    while(1)
    {
        lcd_selectside(LEFT);

        lcd_setpage(0);
    //        RA3 = 1;
        lcd_setyaddr(0);
        lcd_putchar('a');
        
        lcd_selectside(RIGHT);
        lcd_setpage(0);
        lcd_setyaddr(0);
        lcd_putchar('9');

        
        RA3 = 1;
        __delay_ms(5000);
        RA3 = 0;
        __delay_ms(1000);
    }
}
