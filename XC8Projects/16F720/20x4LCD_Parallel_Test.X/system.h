/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        2000000L
#define FCY             SYS_FREQ/4
//#define _XTAL_FREQ      2000000

// Add the following to solve __delay_ms() issues in XC8

#define delay_us(x) _delay((unsigned long)((x)*(SYS_FREQ/4000000.0)))
#define delay_ms(x) _delay((unsigned long)((x)*(SYS_FREQ/4000.0)))

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
