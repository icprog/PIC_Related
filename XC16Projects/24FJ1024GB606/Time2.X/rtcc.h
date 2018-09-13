#ifndef _RTCC_H
#define _RTCC_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

typedef struct tm bcdTime_t;

/**
 Section: Interface Routines
*/

/**
  @Summary
    Initializes and enables RTCC peripheral

  @Description
    This function sets a time in the RTCC and enables 
    RTCC for operation. It will also configure the Alarm settings.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Example
    <code>
    struct tm currentTime;

    RTCC_Initialize();

    while(!RTCC_TimeGet(&currentTime))
    {
        // Do something
    }
    </code>
*/

void RTCC_Initialize(void);


/**
  @Summary
    Returns the current time from the RTCC peripheral

  @Description
    This function returns the current time from the RTCC peripheral. This
    function uses the C library type struct tm parameter.

  @Preconditions
    None

  @Param
    currentTime - This the parameter which gets filled in by the function. The
    values are set by reading the hardware peripheral

  @Returns
    Whether the data is available or not, true if the data is available.
    false if the data is not available.

  @Example
    Refer to the example for the function RTCC_Initialize
*/

bool RTCC_TimeGet(struct tm *currentTime);

/**
  @Summary
    Sets the initial time for the RTCC peripheral

  @Description
    This function sets the initial time for the RTCC peripheral. This
    function uses the C library type struct tm parameter.

  @Preconditions
    None

  @Param
    initialTime - This parameter sets the values.

  @Returns
    None

  @Example
    Refer to the example for the function RTCC_Initialize
*/

void RTCC_TimeSet(struct tm *initialTime);
/**
  @Summary
    Returns the current time from the RTCC peripheral

  @Description
    This function returns the current time from the RTCC peripheral. This
    function uses the C library type struct tm parameter.

  @Preconditions
    None

  @Param
    currentTime - This the parameter which gets filled in by the function. The
    values are set by reading the hardware peripheral

  @Returns
    Whether the data is available or not, true if the data is available.
    false if the data is not available.

  @Example
    Refer to the example for the function RTCC_Initialize
*/

bool RTCC_BCDTimeGet(bcdTime_t *currentTime);

/**
  @Summary
    Sets the initial time for the RTCC peripheral in BCD format

  @Description
    This function sets the initial time for the RTCC peripheral. This
    the time value in BCD format

  @Preconditions
    None

  @Param
    initialTime - This parameter takes the input value in BCD format

  @Returns
    None

  @Example
    Refer to the example for the function RTCC_Initialize
*/
void RTCC_BCDTimeSet(bcdTime_t *initialTime);

/**
  @Summary
    This function indicates whether to reset the RTCC value or not on  system restart.

  @Description
    This function indicates whether to reset the RTCC value or not on  system restart.

  @Preconditions
    None

  @Param
    bool - parameter to indicate whether to reset RTCC value or not

  @Returns
    None

  @Example
    Refer to the example for the function RTCC_Initialize
*/
void RTCC_TimeReset(bool reset);

/**
  @Summary
    Sets the manual Timestamp A event

  @Description
    This function sets the manual timestamp event. This is a software trigger.

  @Preconditions
    None

  @Param
    None 

  @Returns
    None

  @Example
    Refer to the example for the function RTCC_Initialize
*/
void RTCC_TimestampAEventManualSet(void);



/**
  @Summary
    Gets the timestamp time for the RTCC peripheral

  @Description
    This function gets the RTCC time when timestamp A event occurs. This
    function uses the C library type struct tm parameter. Timestamp event can be
    software or hardware trigger.

  @Preconditions
    None

  @Param
    currentTime -  This is the parameter which gets filled in by the function. The
    values are set by reading the hardware peripheral.
    This is the RTCC time when timestamp occurs.

  @Returns
    Whether the data is available or not, true if the data is available.
    false if the data is not available.

  @Example
    Refer to the example for the function RTCC_Initialize
*/
bool RTCC_TimestampADataGet(struct tm *currentTime);


/**
  @Summary
    Gets the timestamp time for the RTCC peripheral in BCD format

  @Description
    This function gets the RTCC time when timestamp A event occurs. This
    function uses the C library type struct tm parameter. Timestamp event can be
    software or hardware trigger.

  @Preconditions
    None

  @Param
    currentTime -  This is the parameter which gets filled in by the function. The
    values are set by reading the hardware peripheral.
    This is the RTCC time when timestamp occurs.

  @Returns
    Whether the data is available or not, true if the data is available.
    false if the data is not available.

  @Example
    Refer to the example for the function RTCC_Initialize
*/
bool RTCC_TimestampA_BCDDataGet(bcdTime_t *currentTime);


/* Function:
    bool RTCC_Task(void)

  Summary:
    Status function which returns the RTCC interrupt flag status

  Description:
    This is the status function for the RTCC peripheral. 
*/
bool RTCC_Task(void);

#endif