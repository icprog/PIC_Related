////////////////////////////////////////////////////////////////////////////////
//                      KS0108 128 x 64 Graphical LCD
//                          Oscilloscope Example
//
// Filename     : 18F452 GLCD Oscilloscope DR1r1.c
// Programmer   : Steven Cholewiak, www.semifluid.com
// Version      : Version 1.1 - 04/11/2007
// Remarks      : This example draws a digital oscilloscope display to a KS0108
//                graphical LCD. Please note the limitations of the PIC's analog
//                port and make sure to buffer the input for the most accurate
//                reading.
//
//                More information on the circuit can be found at:
//                http://www.semifluid.com/PIC18F2550_GLCD_Oscilloscope.php
////////////////////////////////////////////////////////////////////////////////

#include <18F452.h>
#device ADC=10
#fuses H4,NOWDT,NOPROTECT,NOLVP,NODEBUG
#use delay(clock=40000000)

#use rs232(stream=PC, baud=115200, xmit=PIN_C6, rcv=PIN_C7, ERRORS)

#include <GLCD - modified.c>

#INT_RDA
void serial_isr()                         // Serial Interrupt
{
   if (fgetc(PC) == 0x12 & fgetc(PC) == 0x34 & fgetc(PC) == 0x56 & fgetc(PC) == 0x78 & fgetc(PC) == 0x90) #asm reset #endasm
}

void displayFloat(int8 x, int8 y, float oldValue, float theValue) {
   char toPrintOld[9];
   char toPrint[9];
   sprintf(toPrintOld, "%f", oldValue);
   sprintf(toPrint, "%f", theValue);
   toPrintOld[4] = '\0';
   toPrint[4] = '\0';                              // Limit shown digits to 3
   glcd_text35(x, y, toPrintOld, OFF);
   glcd_text35(x, y, toPrint, ON);
}

void displayInt8(int8 x, int8 y, int8 oldValue, int8 theValue) {
   char toPrintOld[4];
   char toPrint[4];
   sprintf(toPrintOld, "%u", oldValue);
   sprintf(toPrint, "%u", theValue);
   toPrintOld[3] = '\0';
   toPrint[3] = '\0';                              // Limit shown digits to 3
   glcd_text35(x, y, toPrintOld, OFF);
   glcd_text35(x, y, toPrint, ON);
}

void displayInt16(int8 x, int8 y, int16 oldValue, int16 theValue) {
   char toPrintOld[6];
   char toPrint[6];
   sprintf(toPrintOld, "%lu", oldValue);
   sprintf(toPrint, "%lu", theValue);
   toPrintOld[5] = '\0';
   toPrint[5] = '\0';                              // Limit shown digits to 5
   glcd_text35(x, y, toPrintOld, OFF);
   glcd_text35(x, y, toPrint, ON);
}

int8 useThreshold = 0;           // 0 = Off, 1 = Rising, 2 = Falling
int8 theThreshold = 127;
int8 timeType = 1;               // 1 = us, 2 = ms
int8 timePeriod = 4;             // us or ms per measurement (* 25 for each div)
int8 voltageRange = 1;           // 1 = 0 - 5V, 2 = 0 - 2.5V, 3 = 0 - 1.25V
float voltageConst = 0.079365;   // For displaying the scaled voltage
char strAverageV[] = "Av";
char strVMaximum[] = "Mx";
char strVMinimum[] = "Mn";
char strVPtoP[] =    "PP";
char strThreshold[] ="Th";
char strOff[] =      "Off";
char strRising[] =   "Rise";
char strFalling[] =  "Fall";
char strTime[] =     "Tm";
char strMs[] =       "ms/div";
char strHz[] =       "Hz";
char strRange[] =    "R";
char strR0to5[] =    "0-5";
char strR0to25[] =   "0-2.5";
char strR0to12[] =   "0-1.2";

void changeThreshold(int8 theUsage, int8 theValue) {
   float tempFloat = 0.0;

   tempFloat = (theThreshold>>2) * voltageConst;

   if (theUsage == 0)
      glcd_text35(12, 24, strOff, OFF);
   else if (theUsage == 1) {
      glcd_text35(12, 24, strRising, OFF);
      displayFloat(12, 30, tempFloat, (theValue>>2) * voltageConst);
   }
   else if (theUsage == 2) {
      glcd_text35(12, 24, strFalling, OFF);
      displayFloat(12, 30, tempFloat, (theValue>>2) * voltageConst);
   }

   useThreshold = theUsage;
   theThreshold = theValue;

   glcd_text35(0, 24, strThreshold, ON);
   if (useThreshold == 0) glcd_text35(12, 24, strOff, ON);
   else if (useThreshold == 1) glcd_text35(12, 24, strRising, ON);
   else if (useThreshold == 2) glcd_text35(12, 24, strFalling, ON);
}

void changeTimeDivision(int8 theType, int16 theValue) {
   float tempFloat = 0.0, tempFloat2 = 0.0;

   glcd_text35(0, 36, strTime, ON);
   if (theType == 1) {
      tempFloat = timePeriod * 25;
      tempFloat2 = theValue * 25;
      displayFloat(12, 36, tempFloat/1000, tempFloat2/1000);
   }
   else if (theType == 2)
      displayFloat(12, 36, timePeriod * 25, theValue * 25);

   timeType = theType;
   timePeriod = theValue;

   if ((theType == 1) && (timePeriod < 16)) timePeriod = 16;

   glcd_text35(4, 42, strMs, ON);
}

void changeVoltageRange(int8 theType) {
   glcd_text35(0, 54, strRange, ON);
   if (voltageRange == 1) glcd_text35(8, 54, strR0to5, OFF);
   else if (voltageRange == 2) glcd_text35(8, 54, strR0to25, OFF);
   else if (voltageRange == 3) glcd_text35(8, 54, strR0to12, OFF);

   voltageRange = theType;

   if (voltageRange == 1) voltageConst = 0.079365;
   else if (voltageRange == 2) voltageConst = 0.039683;
   else if (voltageRange == 3) voltageConst = 0.019841;

   if (voltageRange == 1) glcd_text35(8, 54, strR0to5, ON);
   else if (voltageRange == 2) glcd_text35(8, 54, strR0to25, ON);
   else if (voltageRange == 3) glcd_text35(8, 54, strR0to12, ON);
}

void main() {
   int8 const numOfSamples = 100;
   int16 HQadcReadings[numOfSamples];
   int8 adcReadings[numOfSamples], adcReadingsOld[numOfSamples];
   int8 i = 0;
   int8 thres2 = 1;
   int16 tempThres = 0, k = 0;
   float avgV = 0.0, avgVOld = 0.0;
   float maxV = 0.0, maxVOld = 0.0;
   float minV = 0.0, minVOld = 0.0;
   float ptopV = 0.0, ptopVOld = 0.0;
   int16 theFreq = 0.0, theFreqOld = 0.0;

   SETUP_ADC_PORTS(AN0);           // Setup ADC Pins
   SETUP_ADC(ADC_CLOCK_DIV_64);              // Setup ADC
   SETUP_TIMER_0(RTCC_INTERNAL|RTCC_DIV_1);  // Use the int. osc. for Timer 0
   SETUP_TIMER_1(T1_DISABLED);               // Disable Timer 1
   SETUP_TIMER_2(T2_DISABLED, 127, 1);       // Disable Timer 2
   SETUP_TIMER_3(T3_DISABLED);               // Disable Timer 3
   SETUP_CCP1(CCP_OFF);                      // Disable CCP1
   SETUP_CCP2(CCP_OFF);                      // Disable CCP2

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   glcd_init(ON);                            // Must initialize the LCD
   glcd_line((128-numOfSamples),0,(128-numOfSamples),63,ON);

   // Draw static text
   glcd_text35(0, 0, strAverageV, ON);
   glcd_text35(0, 6, strVMaximum, ON);
   glcd_text35(0, 12, strVMinimum, ON);
   glcd_text35(0, 18, strVPtoP, ON);
   glcd_text35(20, 48, strHz, ON);
   // Setup variable ranges
   changeVoltageRange(1);                    // Set voltage range
   changeTimeDivision(1, 200);                // Set time divisions
   changeThreshold(1, 127);                  // Set threshold level

   set_adc_channel(0);
   delay_ms(10);

   delay_ms(100);
   while (TRUE) {
      // If using threshold, wait until it has been reached
      if (voltageRange == 1) tempThres = (int16) theThreshold << 2;
      else if (voltageRange == 2) tempThres = (int16) theThreshold << 1;
      else if (voltageRange == 3) tempThres = (int16) theThreshold;
      if (useThreshold == 1) {
         k = 0;
         while ((READ_ADC()>tempThres) && (k<65535)) (k++);
         k = 0;
         while ((READ_ADC()<tempThres) && (k<65535)) (k++);
      }
      else if (useThreshold == 2) {
         k = 0;
         while ((READ_ADC()<tempThres) && (k<65535)) (k++);
         k = 0;
         while ((READ_ADC()>tempThres) && (k<65535)) (k++);
      }

      // Collect ADC readings
      if (timeType == 1)
         for (i=0; i<numOfSamples; i++) {
            HQadcReadings[i] = read_adc();
            delay_us(timePeriod-16);
         }
      else if (timeType == 2)
         for (i=0; i<numOfSamples; i++) {
            HQadcReadings[i] = read_adc();
            delay_ms(timePeriod);
         }
      for (i=0; i<numOfSamples; i++) {
         if (voltageRange == 1) adcReadings[i] = 63-(HQadcReadings[i]>>4);
         else if (voltageRange == 2) adcReadings[i] = 63-(HQadcReadings[i]>>3);
         else if (voltageRange == 3) adcReadings[i] = 63-(HQadcReadings[i]>>2);
      }

      // Draw ADC readings
      for (i=1; i<numOfSamples; i++)
         glcd_pixel(i+(128-numOfSamples),adcReadingsOld[i],OFF);
      for (i=1; i<numOfSamples; i++)
         glcd_pixel(i+(128-numOfSamples),adcReadings[i],ON);
      for (i=0; i<numOfSamples; i++)
         adcReadingsOld[i] = adcReadings[i];

      // Calculate and display frequency of signal using zero crossing
      // displayint8(0, 54, thres2, 0);
      if (useThreshold != 0) {
         for (i=0; i<63; i+=3)
               glcd_pixel(thres2+(128-numOfSamples),i,OFF);
         if (useThreshold == 1) {
            thres2 = 1;
            while ((adcReadings[thres2]<(63-(theThreshold>>2))) && (thres2<numOfSamples-1)) (thres2++);
            thres2++;
            while ((adcReadings[thres2]>(63-(theThreshold>>2))) && (thres2<numOfSamples-1)) (thres2++);
         }
         else if (useThreshold == 2) {
            thres2 = 1;
            while ((adcReadings[thres2]>(63-(theThreshold>>2))) && (thres2<numOfSamples-1)) (thres2++);
            thres2++;
            while ((adcReadings[thres2]<(63-(theThreshold>>2))) && (thres2<numOfSamples-1)) (thres2++);
         }
         // displayint8(0, 54, 0, thres2);
         for (i=0; i<63; i+=3)
            glcd_pixel(thres2+(128-numOfSamples),i,ON);

         k = (int16) thres2 * timePeriod;
         if (timeType == 1) theFreq = (float) 1000/k * 1000;
         if (timeType == 2) theFreq = (float) 1000/k;
         displayInt16(0, 48, theFreqOld, theFreq);
         theFreqOld = theFreq;
      }

      // Calculate and display Average V
      avgV = 0;
      for (i=0; i<numOfSamples; i++)
         avgV = (float) avgV + adcReadings[i];
      avgV = (float) (63-(avgV / numOfSamples)) * voltageConst;
      displayFloat(12, 0, avgVOld, avgV);
      avgVOld = avgV;

      // Calculate and display Maximum V
      maxV = 63;
      for (i=0; i<numOfSamples; i++)
         if (adcReadings[i]<maxV) maxV = adcReadings[i];
      maxV = (float) (63-maxV) * voltageConst;
      displayFloat(12, 6, maxVOld, maxV);
      maxVOld = maxV;

      // Calculate and display Minimum V
      minV = 0;
      for (i=0; i<numOfSamples; i++)
         if (adcReadings[i]>minV) minV = adcReadings[i];
      minV = (float) (63-minV) * voltageConst;
      displayFloat(12, 12, minVOld, minV);
      minVOld = minV;

      // Calculate and display Peak-to-peak V
      ptopV = maxV - minV;
      displayFloat(12, 18, ptopVOld, ptopV);
      ptopVOld = ptopV;

      // Display graph lines
      if (useThreshold != 0)
         for (i=29; i<127; i+=3)
            glcd_pixel(i,63-(theThreshold>>2),ON);
      for (i=0; i<63; i+=5) {
         glcd_pixel(53,i,ON);
         glcd_pixel(78,i,ON);
         glcd_pixel(103,i,ON);
         glcd_pixel(127,i,ON);
      }

      delay_ms(100);    // Reduces flicker by allowing pixels to be on
                       // much longer than off
   }
}
