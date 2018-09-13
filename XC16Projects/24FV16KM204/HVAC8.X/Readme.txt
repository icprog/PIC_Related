This is a work in progress, and as such, may have some errors or contradictions 
between actual code and documentation, especially around the LCD, which is 
getting moved to different pins to free up a few analogs.

Project to control 11 floor (or air) temperatures on my natural gas fired glycol heating boiler system.

Project is built around a Microchip PIC24FV16KM204 microcontroller.

To Preserve EEProm Data through a Program Cycle, the Project Configuration needs the PICKit3 Conf Item "Preserve EEPROM Memory" Box checked!!!

Fix for the annoying ToolTips in MPLabX 3.20
Goto Tools -> Options,
Then select "Embedded"
Select "Generic Settings" and disable "On mouse-over source lines in editor, evaluate break point status"

Still ToDo: (Coding)
Add Vdd measurement/display (To bring attention if the Buck needs Adjusting),  (Done, Feb 17,2016, still needs tuning, when get home)


ToDo: (Hardware)
Add Zener to clamp supply voltage to 5.5V
Add Zeners to clamp Analog voltages to 5.1V
Add Buck to adjust supply voltage
Add Red-On/Green-Off LED's for each output,tested design on Feb 17, 2016, works as expected

char *desc[] = {"Deck Floor ","Deck Rm Air ","Utility Flr ","Entrance Flr ","Master Bath ","Office Floor ","Craft Rm Flr ","SE BedRm Flr ","Media Rm Flr ","Garage Floor ","Garage Rm Air"};

char const setpoint[] =          {230, 210, 220, 230, 240, 220, 220, 180, 220, 150, 120};    //setpoint

unsigned char const deadband[] = { 10,   5,  10,  10,   7,   5,   5,   5,   5,   5,  10};    //dead band 

signed char BiasWarm[] =         {-99, -99, -30, -40, -40, -55, -55, -30, -30, -10,  -5};    //Setpoint Bias when Temperature above +5C (Hard coded, non-EEPROM values)

signed char Bias5[] =            {-20,  -5, -20,  -5, -20, -15, -15, -20, -10,  -5,  -5};    //Setpoint Bias when Temperature between 0C and +5C (Hard coded, non-EEPROM values)

signed char Bias0[] =            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};    //Setpoint Bias when Temperature between -5C and 0C (Hard coded, non-EEPROM values)

signed char BiasNeg5[] =         { 20,   5,  15,  10,  10,   5,   5,   0,  10,   0,   0};    //Setpoint Bias when Temperature between -15C and -5C (Hard coded, non-EEPROM values)

signed char const biasNeg15[] =  { 40,  10,  20,  25,  20,  15,  15,  10,  15,  15,  10};    //biasNeg15 (Temperature between -15C and -25C)

signed char const biasNeg25[] =  { 70,  15,  35,  45,  40,  30,  30,  15,  20,  30,  20};    //biasNeg25 (Temperature below -25C)

Outputs:

"Deck Floor "       _LATC8
"Utility Flr "      _LATC9
"Entrance Flr "     _LATA7
"Master Bath "      _LATB10
"Office Floor "     _LATB11
"Craft Rm Flr "     _LATA10
"SE BedRm Flr "     _LATA11
"Media Rm Flr "     _LATA2
"Garage Floor "     _LATA3

BackLight Control   _LATA1

Inputs: (Number in brackets is ANALOG Channel number)

ADCRead(0),         Read Deck Floor Temperature
ADCRead(4),         Read Deck Room Air Temperature   
ADCRead(5),         Read Utility Floor Temperature
ADCRead(6),         Read Entrance Floor Temperature
ADCRead(10),        Read Master Bath Temperature
ADCRead(11),        Read Office Floor Temperature
ADCRead(12),        Read Craft Room Floor Temperature
ADCRead(17),        Read SE Basement BedRoom Floor Temperature
ADCRead(18),        Read Media Room Floor Temperature
ADCRead(19),        Read Garage Floor Temperature
ADCRead(20),        Read Garage Room Air Temperature

ADCRead(9),         Read Outside Air Temperature


Pins Used:

1   AN21/_RB9   IP/OP   y+ Touchscreen (Both analog IP and Digital OP)
2   _RC6        LCD     LCD REGISTER SELECT Bit
3   _RC7        LCD     LCD ENABLE Bit
4   _LATC8      OP      Deck Floor Out
5   _LATC9      OP      Utility Floor Out
6   _LATA7      OP      Entrance Floor Out
7   VCap        SYS     VCap
8   _LATB10     OP      Master Bath Floor Out
9   _LATB11     OP      Office Floor Out
10  AN12        IP      Read Craft Room Floor Temperature
11  AN11        IP      Read Office Floor Temperature  
12  _LATA10     OP      Craft Room Floor Out
13  _LATA11     OP      SE Basement Floor Out
14  AN10        IP      Read Master Bath Floor Temperature
15  AN9         IP      Read Outside Air Temperature
16  AVss        SYS     Analog Vss
17  AVdd        SYS     Analog AVdd
18  MCLR/Vpp    SYS     Master Clear/Programming Voltage
19  AN0         IP      Read Deck Floor Temperature
20  _LATA1      OP      Turn off BackLight after 60 seconds of no use
21  PGED1       SYS     Programming Pin Data
22  PGEC1       SYS     Programming Pin Clock
23  AN4         IP      Read Deck Room Air Temperature
24  AN5         IP      Read Utility Floor Temperature
25  AN6         IP      Read Entrance Floor Temperature
26  AN7/_RC1    IP/OP   x+ Touchscreen (Both Analog IP and Digital OP)
27  _RC2        IP/OP   x- Touchscreen (Both High Impedance IP and Digital OP)
28  Vdd         SYS Vdd
29  Vss         SYS Vss
30  _LATA2      OP  Media Room Floor Out
31  _LATA3      OP  Garage Floor Out
32  _RA8        IP/OP   y- Touchscreen (Both High Impedance IP and Digital OP)
33  SOSCI       SYS Secondary Oscillator In
34  SOSCO       SYS Secondary Oscillator Out
35  RA9         LCD LCD Port D4
36  RC3         LCD LCD Port D5
37  RC4         LCD LCD Port D6
38  RC5         LCD LCD Port D7
39  Vss         SYS Vss
40  Vdd         SYS Vdd
41  AN17        IP  Read SE Basement BedRoom Floor Temperature
42  AN18        IP  Read Media Room Floor Temperature
43  AN19        IP  Read Garage Floor Temperature
44  AN20        IP  Read Garage Room Air Temperature
