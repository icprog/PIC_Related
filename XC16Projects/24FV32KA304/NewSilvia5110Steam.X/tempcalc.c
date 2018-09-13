#include "tempcalc.h"

float R, steinhart;         // Calculate R of Thermistor, and Temp using SteinHart/Hart equation

// *************** Calculate & Display Temp ************************************    
float tempCalc(unsigned int a)
{
    R = 10010/((4095/(float)a) - 1);            // Resistance of Thermistor (R Reference/1023/readTemp -1) 10K Resistor on board reads 10.01K
    steinhart = R /10090;                       // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
    steinhart = log(steinhart);                 // ln(R/Ro)
    steinhart /= 4001.03;                       // 1/Beta * ln(R/Ro)
    steinhart += 1.0 / (25 + 273.15);           // + (1/To, Temperature in degK @ 25C)
    steinhart = 1.0 / steinhart;                // Invert
    steinhart -= 273.15;                        // convert to DegC
    steinhart = steinhart*10;                   // *10 to get one decimal of precision
    steinhart = steinhart*9/5+320;              // Display Temperature in DegF

    return ((unsigned int)steinhart);               
}

int aTempCalc(unsigned int a)
{
//    return a;
    
    if(a < 820)
    {
        return 500;
    }
    else
    {
        return ((int)(((a - 820)/1.096)+500));               
    }
}

