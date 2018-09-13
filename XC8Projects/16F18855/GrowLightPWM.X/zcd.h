#ifndef _ZCD_H
#define _ZCD_H

#include "system.h"

void ZCD_Initialize(void);

/**
  @Summary
    Implements ISR.

  @Description
    This routine is used to implement the ISR for the interrupt-driven
    implementations.

  @Returns
    None

  @Param
    None
*/
void ZCD_ISR(void);

/**
  @Summary
    Determines if current is sinking or sourcing

  @Description
    This routine is used to determine if current is sinking or sourcing
    depending on output polarity.

    For non inverted polarity:
    high - Indicates current is sinking
    low - Indicates current is sourcing

    For inverted polarity:
    high - Indicates current is sourcing
    low - Indicates current is sinking

  @Preconditions
    ZCD_Initialize() function should have been called before calling this function.

  @Param
    None

  @Returns
   high or low

  @Example
    <code>
    ZCD_Initialize();

    if(ZCD_IsLogicLevel())
    {
        // User code..
    }
    else
    {
        // User code..
    }
    </code>
 */
//bool ZCD_IsLogicLevel(void);

#endif