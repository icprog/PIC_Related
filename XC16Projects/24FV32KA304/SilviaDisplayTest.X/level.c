#include "level.h"


char waterTankLevel(void)
{
    int level;
    
    level = ADCRead(6);
    
    if(level <796)
    {
        level = 0;
    }
    else if(level > 3970)
    {
        level = 100;
    }
    else
    {
       level = (level-796)/31.74;
    }
    return level;
}

            

