#ifndef _INTERRUPT_MANAGER_H
#define _INTERRUPT_MANAGER_H

#include <xc.h>

/**
  @Summary
    Initializes the interrupt priorities of the PIC24FJ1024GB606

  @Description
    This routine sets the interrupt priorities of the modules that have been configured
    for the PIC24FJ1024GB606

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        INTERRUPT_Initialize ();
    }
    </code>

*/
void INTERRUPT_Initialize(void);

#endif