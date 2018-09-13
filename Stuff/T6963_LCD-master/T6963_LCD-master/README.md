#PIC24 interface to T6963 LCD
copied from [here](https://www.ccsinfo.com/forum/viewtopic.php?t=49389)<br />
[demo video](https://www.youtube.com/watch?v=_WcaunQZPQc)<br />
used to test HDM128GS24 (Toshiba T6963C Graphic LCD)<br />
changed code to work with MPLABX and PIC24FJ128GB110<br />

<ul>
<li>RA 0->7 LCD Data Bus</li>
<li>RA0 p17</li>
<li>RA1 p38</li>
<li>RA2 p58</li>
<li>RA3 p59</li>
<li>RA4 p60</li>
<li>RA5 p61</li>
<li>RA6 p91</li>
<li>RA7 p92</li>
<li>RA 14 C/D p66</li>
<li>RA 15 RD p67</li>
<li>RC 1 WR p6</li>
<li>RC 2 CE p7</li>
<li>RC 3 RESET p8</li>
<li>RC 4 FS1 p9</li>
</ul>
EastRising LCD (EMR240128-2)<br />
bought on [ebay](http://www.ebay.com/itm/301023710583?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT)<br />
pin		desc<br />
<ul>
<li>1		Frame Ground connected to Vss</li>
<li>2		Vss</li>
<li>3		Vdd</li>
<li>4		Vo - LCD contrast input</li>
<li>5		/WR</li>
<li>6		/RD</li>
<li>7		/CE</li>
<li>8		CD</li>
<li>9		/RST</li>
<li>10		DB0</li>
<li>11		DB1</li>
<li>12		DB2</li>
<li>13		DB3</li>
<li>14		DB4</li>
<li>15		DB5</li>
<li>16		DB6</li>
<li>17		DB7</li>
<li>18		FS1 - Font select</li>
<li>19		Vee - Power booster output for Vo</li>
<li>20		LED_A - Pos power for backlight</li>
<li>21		LED_K - Neg power supply for backlight</li>
</ul>
C/D=H, /WR=L, /RD=H : Command Write<br />
C/D=H, /WR=H, /RD=L : Status Read<br />
C/D=L, /WR=L, /RD=H : Data Write<br />
C/D=L, /WR=H, /RD=L : Data Read<br />

Reset Signal:<br />
/RST = L, Reset the LCD Module<br />
/RST = H, Normal Running<br />

Font Selection Input:<br />
FS1=H : 6x8 font<br />
FS1=L : 8x8 font<br />

using 20k pot from ground to Vee with center tap connected to Vo.<br />
LED_A -> +5v<br />
LED_K -> GND<br />
