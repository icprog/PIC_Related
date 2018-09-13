#include <xc.h>
#include "oc1.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gOC1Mode;

/**
  Section: Driver Interface
*/


void OC1_Initialize (void)
{
    // ENFLT0 disabled; ENFLT1 disabled; OCFLT2 disabled; ENFLT2 disabled; OCSIDL disabled; OCM Edge-Aligned PWM mode; OCFLT1 disabled; OCFLT0 disabled; OCTSEL TMR2; TRIGMODE Only Software; 
    OC1CON1 = 0x0006;
    // SYNCSEL TMR2; TRIGSTAT disabled; DCB Start of instruction cycle; OCINV disabled; OCTRIG Sync; OC32 disabled; FLTOUT disabled; OCTRIS disabled; FLTMD Cycle; FLTTRIEN disabled; 
    OC1CON2 = 0x000C;
    // OC1RS 8192; 
    OC1RS = 0x2000;
    // OC1R 0; 
    OC1R = 0x0000;
	
    gOC1Mode = OC1CON1bits.OCM;
}



void OC1_Tasks( void )
{
    if(IFS0bits.OC1IF)
    {
        IFS0bits.OC1IF = 0;
    }
}



void OC1_Start( void )
{
    OC1CON1bits.OCM = gOC1Mode;
}


void OC1_Stop( void )
{
    OC1CON1bits.OCM = 0;
}


void OC1_SingleCompareValueSet( uint16_t value )
{
    OC1R = value;
}


void OC1_DualCompareValueSet( uint16_t priVal, uint16_t secVal )
{
    OC1R = priVal;
	
    OC1RS = secVal;
}


void OC1_CentreAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    OC1R = priVal;
	
    OC1RS = secVal;
}

void OC1_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    OC1R = priVal;
	
    OC1RS = secVal;
}

void OC1_SecondaryValueSet( uint16_t secVal )
{
   
    OC1RS = secVal;
}


void OC1_PrimaryValueSet( uint16_t priVal )
{
   
    OC1R = priVal;
}

bool OC1_IsCompareCycleComplete( void )
{
    return(IFS0bits.OC1IF);
}


bool OC1_FaultStatusGet( OC1_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC1_FAULT0:status = OC1CON1bits.OCFLT0;
            break;
        case OC1_FAULT1:status = OC1CON1bits.OCFLT1;
            break;
        case OC1_FAULT2:status = OC1CON1bits.OCFLT2;
            break;
        default :
            break;

    }
    return(status);
}


void OC1_FaultStatusClear( OC1_FAULTS faultNum )
{
    
    switch(faultNum)
    { 
        case OC1_FAULT0:OC1CON1bits.OCFLT0 = 0;
                break;
        case OC1_FAULT1:OC1CON1bits.OCFLT1 = 0;
                break;
        case OC1_FAULT2:OC1CON1bits.OCFLT2 = 0;
                break;
        default :
                break;
    }    
}


void OC1_ManualTriggerSet( void )
{
    OC1CON2bits.TRIGSTAT= true; 
}

bool OC1_TriggerStatusGet( void )
{
    return( OC1CON2bits.TRIGSTAT );
}


void OC1_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    OC1CON2bits.TRIGSTAT = 0;
}

/**
 End of File
*/
