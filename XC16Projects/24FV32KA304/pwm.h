#include <xc.h>

#ifndef PWM_H
#define	PWM_H

#define Input   1
#define Output  0

    
    void InitializeTimer2For_PWM(void);
    void Initialize_PWM(void);
    void SetDutyCycle_PWM(unsigned int DutyCycle);


#endif	/* PWM_H */

