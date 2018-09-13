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
