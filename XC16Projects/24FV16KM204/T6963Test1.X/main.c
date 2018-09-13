#include <xc.h>
#include "system.h"
#include "t6963c.h"

int main(void)
{
    t6963c_init();
    t6963c_writeString("Hello world!");
    t6963c_set_address(1,0);
    t6963c_writeString("2nd Line Hello world!");
    
    while(1)
    {
        
    }
    
    ClrWdt();
    return(1);
}
