YOU MUST AGREE THIS TERMS AND CONDITIONS. THIS SOFTWARE IS
PROVIDED BY NORITAKE CO., INC "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR SORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------
ABOUT THIS DEMO
This project demonstrates how to use the Noritake_VFD_CUU code
library to set the brightness on Noritake CU-U Vacuum
Fluorescent Display (VFD) modules. You MUST download and install
the Noritake_VFD_CUU code library before running the demo.

	http://www.noritake-elec.com

Please refer to the instructions on the download page and
"README" included with the Noritake_VFD_CUU code library for
information on how to install the Noritake_VFD_CUU code library 
and demos.  This document assumes that you have already
configured "config.h" file in the Noritake_VFD_CUU code library
as described in those documents.

For more information on the methods used in this document, please
refer to the method reference documentation in the
Noritake_VFD_CUU code library.

----------------------------------------------------------------
BEHAVIOR
This demo will behave differently depending on which Noritake
CU-U VFD module you will use. Set NORITAKE_VFD_BRIGHTNESS_BOOST
to 1 if your VFD module has the brightness boost feature. Set
NORITAKE_VFD_BRIGHTNESS_BOOST to 0 if your VFD module does not 
have the brightness boost feature.

The Noritake VFD CU-U modules that support brightness boost will
have model numbers in the following form:

	CU*****-UX**

	Example: CU20025-UX1J

For modules WITHOUT the brightness boost feature:
	1) This demo will set the brightness to 25% and display:
		Noritake
		25% Brightness
	2) Wait 1 second.
	3) Set the brightness to 50% and display:
		Noritake
		50% Brightness
	4) Wait 1 second.
	5) Set the brightness to 75% and display:
		Noritake
		75% Brightness
	6) Wait 1 second.
	7) Set the brightness to 100% and display:
		Noritake
		100% Brightness
	8) Wait 1 second.
	9) Repeat from step 1.

For modules with the brightness boost feature:
	1) This demo will set the brightness to 50% and display:
		Noritake
		50% Brightness
	2) Wait 1 second.
	3) Set the brightness to 100% and display:
		Noritake
		100% Brightness
	4) Wait 1 second.
	5) Set the brightness to 150% and display:
		Noritake
		150% Brightness
	6) Wait 1 second.
	7) Set the brightness to 200% and display:
		Noritake
		200% Brightness
	8) Wait 1 second.
	9) Repeat from step 1.

----------------------------------------------------------------
KEY POINTS
1) Initialize the VFD module with the CUU_init() method.
2) Print with print() method.
3) Set the brightness with CUU_brightness() method.
4) Move the cursor with CUU_setCursor() method.

----------------------------------------------------------------
LISTING
#include "../src/config.h"
#include "../src/Noritake_VFD_CUU.h"
#include <util/delay.h>

int main() {
	Noritake_VFD_CUU vfd;

#if NORITAKE_VFD_BRIGHTNESS_BOOST==1
	int min = 50, max = 200, step = 50;
#else
	int min = 25, max = 100, step = 25;
#endif

	vfd.CUU_init(); // initialize VFD
	vfd.print("Noritake"); // print Noritake on the first line
	for (;;)
		for (int i = min; i<=max; i+=step) {
			vfd.CUU_brightness(i); // Set the brightness
			vfd.CUU_setCursor(0,1); // Go to second line
			vfd.print(i); // print the brightness value
			vfd.print("% Brightness ");
			_delay_ms(1000); // wait one second
		}
}

----------------------------------------------------------------
E-M-0055-01 06/25/2012
----------------------------------------------------------------
CHANGES
Revision 1
    Code listing changed to follow new directory structure.
    
SUPPORT

For further support, please contact:
	Noritake Co., Inc.
	2635 Clearbrook Dr 
	Arlington Heights, IL 60005 
	800-779-5846 
	847-439-9020
	support.ele@noritake.com

All rights reserved. © Noritake Co., Inc.