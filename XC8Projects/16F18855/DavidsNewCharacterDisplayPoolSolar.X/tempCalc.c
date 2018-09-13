#include    "tempCalc.h"
#include    <math.h>

float tempCalc(int analogValue)
{
    float R, steinhart;                         // Calculate R of Thermistor, and Temp using SteinHart/Hart equation

    R = 10020/(1023/(float)analogValue - 1);    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
    steinhart = R /10061;                       // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
    steinhart = log(steinhart);                 // ln(R/Ro)
    steinhart /= 3995;                          // 1/Beta * ln(R/Ro)
    steinhart += 1.0 / (25 + 273.15);           // + (1/To, Temperature in degK @ 25C)
    steinhart = 1.0 / steinhart;                // Invert
    steinhart -= 273.15;                        // convert to DegC

    steinhart*=10;                              // multiply by 10 to create displayable decimal point (LCDWriteInt...)
        
//    steinhart = steinhart*9/5+320;              // Display Temperature in DegF
        
    return steinhart;    
}
