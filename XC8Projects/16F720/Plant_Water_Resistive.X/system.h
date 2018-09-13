#define SYS_FREQ        2000000L
#define FCY             SYS_FREQ/4

// Add the following to solve __delay_ms() issues in XC8

#define delay_us(x) _delay((unsigned long)((x)*(SYS_FREQ/4000000.0)))
#define delay_ms(x) _delay((unsigned long)((x)*(SYS_FREQ/4000.0)))


//*****************************************************************************************
// Startup Oscillator requirements
//*****************************************************************************************
void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
//*****************************************************************************************



//*****************************************************************************************
// Startup Initialization requirements
//*****************************************************************************************
void Init(void);
//*****************************************************************************************


