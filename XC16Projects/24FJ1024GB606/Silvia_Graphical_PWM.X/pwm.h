#include <xc.h>

#ifndef PWM_H
#define	PWM_H

//#define Input   1
//#define Output  0

    
    void InitializeTimers(void);
    void Initialize_PWM(void);
    void setDutyCycle(unsigned int dutyCycle);


#endif	/* PWM_H */

