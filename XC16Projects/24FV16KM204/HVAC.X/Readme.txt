This is a work in progress, and as such, may have some errors or contradictions 
between actual code and documentation, especially around the LCD, which is 
getting moved to different pins to free up a few analogs.

To Do:
1. Set up all I/O
2. Finish Pin Map
3. Add Touch Input
4. Set-up Inputs to react to press immediately, then repeat after a short delay
5. Change LCD Pins to free up Analog inputs

Project to control 12 floor (or air) temperatures on my natural gas fired glycol heating boiler system.

Project is built around a Microchip PIC24FV16KM204 microcontroller.

Outputs:

"Deck Floor "       _RC8
"Utility Flr "      _RC9
"Entrance Flr "     _RA7
"Master Bath "
"Office Floor "
"Craft Rm Flr "
"SE BedRm Flr "
"Media Rm Flr "
"Garage Floor "
"Spare        "

Inputs: (Number in brackets is ANALOG Channel number)

ADCRead(0),         Read Deck Floor Temperature
ADCRead(4),         Read Deck Room Air Temperature   
ADCRead(5),         Read Utility Floor Temperature
ADCRead(10),        Read Entrance Floor Temperature
ADCRead(11),        Read Master Bath Temperature
ADCRead(12),        Read Office Floor Temperature
ADCRead(13),        Read Craft Room Floor Temperature
ADCRead(17),        Read SE Basement BedRoom Floor Temperature
ADCRead(18),        Read Media Room Floor Temperature
ADCRead(19),        Read Garage Floor Temperature
ADCRead(20),        Read Garage Room Air Temperature
ADCRead(21),        Read Spare Temperature

ADCRead(9),         Read Outside Air Temperature


Pins Used:

1   AN21    IP  Spare
2   _RC6    LCD LCD REGISTER SELECT Bit
3   _RC7    LCD LCD ENABLE Bit
4   _RC8    OP  Deck Floor Out
5   _RC9    OP  Utility Floor Out
6   _RA7    OP  Entrance Floor Out
7   VCap    SYS VCap
8
9
10
11
12
13
14
15  AN9     IP  Read Outside Air Temperature
16  AVss    SYS Analog Vss
17  AVdd    SYS Analog AVdd
18
19  AN0     IP  Read Deck Floor Temperature
20
21  PGED1   SYS Programming Pin Data
22  PGEC1   SYS Programming Pin Clock
23  AN4     IP  Read Deck Room Air Temperature
24  AN5     IP  Read Utility Floor Temperature
25
26
27
28  Vdd     SYS Vdd
29  Vss     SYS Vss
30
31
32
33
34
35  RA9     LCD LCD Port D4
36  RC3     LCD LCD Port D5
37  RC4     LCD LCD Port D6
38  RC5     LCD LCD Port D7
39  Vss     SYS Vss
40  Vdd     SYS Vdd
41  AN17    IP  Read SE Basement BedRoom Floor Temperature
42  AN18    IP  Read Media Room Floor Temperature
43  AN19    IP  Read Garage Floor Temperature
44  AN20    IP  Read Garage Room Air Temperature
