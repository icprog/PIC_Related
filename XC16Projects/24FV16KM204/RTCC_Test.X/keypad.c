
#include "keypad.h"

uint8_t KeyBuffer[4][3];	//Raw key samples
uint8_t KeyState[4];
uint8_t KeyPrevState[4];

uint8_t KeyRepeatWait[4];   //Repeat counters
uint8_t KeyRepeatRate[4];

#define KEY_REPEAT_WAIT 75;
#define KEY_REPEAT_RATE 10;

volatile uint8_t key;

//Queue
volatile uint8_t KeypadCmdQ[KEYPAD_QMAX];	//Final Command Received (Buffer)
volatile int8_t KeypadQFront=-1,KeypadQEnd=-1;

void KeypadInit()
{
	uint8_t i;
	for(i=0;i<4;i++)        	//Init Key States
	{
		KeyPrevState[i]=RELEASED;
		KeyState[i]=RELEASED;

		//Repeat
		KeyRepeatWait[i]=KEY_REPEAT_WAIT;
		KeyRepeatRate[i]=KEY_REPEAT_RATE;
	}

/*	//First make all i/o pins input
	D_LEFT_KEY_DDR&=(~(1<<D_LEFT_KEY_POS));		//LEFT
	D_RIGHT_KEY_DDR&=(~(1<<D_RIGHT_KEY_POS));	//RIGHT
	D_ENTER_KEY_DDR&=(~(1<<D_ENTER_KEY_POS));	//ENTER
	DEL_KEY_DDR&=(~(1<<DEL_KEY_POS));			//DEL


	//Now enable internal pullups
	D_LEFT_KEY_PORT|=(1<<D_LEFT_KEY_POS);		//LEFT
	D_RIGHT_KEY_PORT|=(1<<D_RIGHT_KEY_POS);		//RIGHT
	D_ENTER_KEY_PORT|=(1<<D_ENTER_KEY_POS);		//ENTER
	DEL_KEY_PORT|=(1<<DEL_KEY_POS);			//DEL


	//Init TIMER0 for keypad scanner (Approx 244 fps)
	TCCR0=(1<<CS02);	//Prescaller 256
	TIMSK|=(1<<TOIE0);	//Enable overflow interrupt

	sei();//Enable interrupts
 */
}

interupt(TIMER0_OVF_vect)
{
	
	static uint8_t n=0;

	//Take 3 raw samples for major voting
	for(uint8_t i=0;i<4;i++)
	{
		KeyBuffer[i][n]=GetRawKeyState(i);
	}

	n++;
	
	//3 samples taken
	if(n==3)
	{
		//reset counter
		n=0;
		
		
		for(uint8_t i=0;i<4;i++)
		{
			KeyPrevState[i]=KeyState[i];
			KeyState[i]=MajorVote(i);

			if(KeyState[i]==PRESSED)
			{
				if(KeyPrevState[i]==RELEASED)
				{
					//Now We Have Got a key press
					//Add it to Queue
				
					//Step1:Check of Q full
					if((KeypadQEnd==(KEYPAD_QMAX-1) && KeypadQFront==0)||((KeypadQEnd+1)==KeypadQFront))
					{
						KeypadQFront++;
						if(KeypadQFront==(KEYPAD_QMAX)) 
							KeypadQFront=0;
					}

					if(KeypadQEnd==(KEYPAD_QMAX-1))
						KeypadQEnd=0;
					else
						KeypadQEnd++;

					KeypadCmdQ[KeypadQEnd]=i;
					if(KeypadQFront==-1) KeypadQFront=0;
				}
				else
				{
					if(KeyRepeatWait[i]!=0) KeyRepeatWait[i]--;
					else
					{
						KeyRepeatRate[i]--;
						if(KeyRepeatRate[i]==0)
						{
							KeyRepeatRate[i]=KEY_REPEAT_RATE;

							//Now We Have Got a keypress
							//Add it to Queue
				
							//Step1:Check of Q full
							if((KeypadQEnd==(KEYPAD_QMAX-1) && KeypadQFront==0)||((KeypadQEnd+1)==KeypadQFront))
							{
								KeypadQFront++;
								if(KeypadQFront==(KEYPAD_QMAX)) 
									KeypadQFront=0;
							}

							if(KeypadQEnd==(KEYPAD_QMAX-1))
								KeypadQEnd=0;
							else
								KeypadQEnd++;

							KeypadCmdQ[KeypadQEnd]=i;
							if(KeypadQFront==-1) KeypadQFront=0;

							
						}
					}


				}
			}
			else
			{
				KeyRepeatWait[i]=KEY_REPEAT_WAIT;
			}
		}
	}

}

uint8_t GetRawKeyState(uint8_t KeyCode)
{
	if(KeyCode==KEY_LEFT)
	{
		return ((D_LEFT_KEY_PIN & (1<<D_LEFT_KEY_POS)));
	}

	if(KeyCode==KEY_RIGHT)
	{
		return ((D_RIGHT_KEY_PIN & (1<<D_RIGHT_KEY_POS)));
	}

	if(KeyCode==KEY_ENTER)
	{
		return ((D_ENTER_KEY_PIN & (1<<D_ENTER_KEY_POS)));
	}

	if(KeyCode==KEY_CANCEL)
	{
		return ((DEL_KEY_PIN & (1<<DEL_KEY_POS)));
	}

	return RELEASED;
}

uint8_t MajorVote(uint8_t keycode)
{
	if(KeyBuffer[keycode][0]==PRESSED)
	{
		if(KeyBuffer[keycode][1]==PRESSED)
		{
			return PRESSED;
		}
		else
		{
			if(KeyBuffer[keycode][2]==PRESSED)
				return PRESSED;
			else
				return RELEASED;
		}
	}
	else
	{
		if(KeyBuffer[keycode][1]==RELEASED)
		{
			return RELEASED;
		}
		else
		{
			if(KeyBuffer[keycode][2]==PRESSED)
				return PRESSED;
			else
				return RELEASED;
		}
	}
}

uint8_t GetKeypadCmd(char wait)
{
	unsigned char cmd;

	if(wait)
		while(KeypadQFront==-1);
	else
		if(KeypadQFront==-1) return (KEY_NONE);

	cmd=KeypadCmdQ[KeypadQFront];

	if(KeypadQFront==KeypadQEnd) 
		KeypadQFront=KeypadQEnd=-1;
	else
	{
		if(KeypadQFront==(KEYPAD_QMAX-1))
			KeypadQFront=0;
		else
			KeypadQFront++;
	}

	return cmd;
}
	


