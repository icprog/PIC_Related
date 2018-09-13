#ifndef _TRAPS_H
#define _TRAPS_H

#include "system.h"

/**
 * Error codes
 */
typedef enum 
{
    /* ----- Traps ----- */
    TRAPS_OSC_FAIL = 0, /** Oscillator Fail Trap vector */
    TRAPS_STACK_ERR = 1, /** Stack Error Trap Vector */
    TRAPS_ADDRESS_ERR = 2, /** Address Error Trap Vector */
    TRAPS_MATH_ERR = 3, /** Math Error Trap Vector */
    TRAPS_NVM_ERR = 7, /** NVM Error Trap Vector */
} TRAPS_ERROR_CODE;

/**
  @Summary
    Default handler for the traps

  @Description
    This routine will be called whenever a trap happens. It stores the trap
    error code and waits forever.
    This routine has a weak attribute and can be over written.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    None.

*/
void __attribute__((naked, noreturn, weak)) TRAPS_halt_on_error(uint16_t code);

#endif