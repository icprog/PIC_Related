#define F_CPU						16000000UL		// CPU frequency in Hertz
#define NORITAKE_VFD_RESET_DELAY	500				// Delay in milliseconds before initializing the VFD module.
	// 500 ms is more than enough time for the module to start up.
	// You may lower this value depending on your module and connection.

#define NORITAKE_VFD_COLS			20				// The number of columns the display supports
#define NORITAKE_VFD_LINES			2				// The number of lines the display supports
#define NORITAKE_VFD_BRIGHTNESS_BOOST 0 			// 1=Using a CU-UX module that supports brightness boost, 0=Not using a module does not supports brightness boost
//	The following models support brightness boost:
//		CU16025-UX6J
//		CU16025-UX6A
//		CU20025-UX1J
#define NORITAKE_VFD_CU20045_UW4J	0				// 1=Using a CU20045-UW4J (different addresses from other CU-U 20x4 models), 0=Using any other model


// Options specific to DS2045G
#define NORITAKE_VFD_BC             0               // 1=DS2045G VFD, 0=CU-U VFD Module
#define NORITAKE_VFD_FONT           1               // 1=Japanese Katakana (default), 0=European

// -------------------------------------------------------------
// SELECTING INTERFACE
// NORITAKE_VFD_INTERFACE
//		0 SERIAL
//		1 PARALLEL
// NORITAKE_VFD_PARLLEL
//		0 M68
//		1 I80
// -------------------------------------------------------------
#define NORITAKE_VFD_INTERFACE	0	// Interface: 1=parallel, 0=serial
#define NORITAKE_VFD_PARALLEL	0	// Parallel mode: 1=I80, 0=M68
#define NORITAKE_VFD_4BIT		0	// 1=4-bit mode, 0=8-bit mode
#define NORITAKE_VFD_NO_RW_LINE	0	// 1=R/W line is not connected (read disabled in M68), 0=read enabled in M68


// -------------------------------------------------------------
// SERIAL OPTIONS
//	SIO_PORT & SIO_PIN	Data line port and pin
//	SCK_PORT & SCK_PIN	Clock line port and pin
//	STB_PORT & STB_PIN	Strobe line port and pin
//  Please refer to VFD module specification for pin assignments.
// -------------------------------------------------------------
#if NORITAKE_VFD_INTERFACE==0
#	define SIO_PORT	PORTG
#	define SIO_PIN	4

#	define SCK_PORT	PORTG
#	define SCK_PIN	3

#	define STB_PORT	PORTB
#	define STB_PIN	7
#endif


// -------------------------------------------------------------
// PARALLEL OPTIONS
//	I80
//		RS_PORT & RS_PIN	RS line port & pin
//		WR_PORT & WR_PIN	WR line port & pin
//		RD_PORT & RD_PIN	RD line port & pin
//	M68
//		RS_PORT & RS_PIN	RS line port & pin
//		RW_PORT & RW_PIN	R/W line port & pin
//		E_PORT & E_PIN		E line port & pin
//	D0_PORT & D0_PIN		Data bit 0 port &pin
//	D1_PORT & D1_PIN		Data bit 1 port &pin
//	D2_PORT & D2_PIN		Data bit 2 port &pin
//	D3_PORT & D3_PIN		Data bit 3 port &pin
//	D4_PORT & D4_PIN		Data bit 4 port &pin
//	D5_PORT & D5_PIN		Data bit 5 port &pin
//	D6_PORT & D6_PIN		Data bit 6 port &pin
//	D7_PORT & D7_PIN		Data bit 7 port &pin
//  Please refer to VFD module specification for pin assignments.
// -------------------------------------------------------------
#if NORITAKE_VFD_INTERFACE==1
#	if NORITAKE_VFD_PARALLEL==1	// I80 INTERFACE
#		define	RS_PORT	PORTG
#		define	RS_PIN	2
#		define	WR_PORT	PORTG
#		define	RD_PORT	PORTG
#		define	WR_PIN	0
#		define	RD_PIN	1
#	else						// M68 INTERFACE
#		define	RS_PORT	PORTG
#		define	RS_PIN	2
#		define	RW_PORT	PORTG
#		define	E_PORT	PORTG
#		define	RW_PIN	0
#		define	E_PIN	1
#	endif
#	define	D0_PORT	PORTC
#	define	D1_PORT	PORTC
#	define	D2_PORT	PORTC
#	define	D3_PORT	PORTC
#	define	D4_PORT	PORTC
#	define	D5_PORT	PORTC
#	define	D6_PORT	PORTC
#	define	D7_PORT	PORTC
#	define	D0_PIN	0
#	define	D1_PIN	1
#	define	D2_PIN	2
#	define	D3_PIN	3
#	define	D4_PIN	4
#	define	D5_PIN	5
#	define	D6_PIN	6
#	define	D7_PIN	7
#endif
