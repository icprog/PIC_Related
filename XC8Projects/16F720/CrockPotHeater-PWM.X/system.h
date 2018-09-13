#define SYS_FREQ        62500L
#define _XTAL_FREQ      62500
#define FCY             SYS_FREQ/4

// Add the following to solve __delay_ms() issues in XC8

//#define __delay_us(x) _delay((unsigned long)((x)*(SYS_FREQ/4000000.0)))
//#define __delay_ms(x) _delay((unsigned long)((x)*(SYS_FREQ/4000.0)))


void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

void Init(void);                // Initialize PORTS, TRIS, ANSEL, Etc
