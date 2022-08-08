/*  Freq = 50Hz ---> 1msec  */
/*  Tick time   ---> 1msec/100 = 10usec */
/*  configure the timer tick  */

//#define SIG_PERIOD 100
#define F_CPU 1000000
#define SIG_PERIOD 100
#define NO_OV 10
#include "timer.h"
#include "gpio.h"
#include <avr/io.h>
#include <avr/delay.h>
volatile unsigned short count =0;
volatile unsigned short ov =0;
volatile unsigned short DUTY_CYCLE = 0; 



void main (void)
{
	SREG = (1<<7);
	/*configure timer to give interrrupt every 10usec*/
	timer_8bitConfigType timer0_config = {0,0,CLK_1024,DISABLE};
	timer0_OVFmodeInit(&timer0_config);
	timer0_CTCmode_setCallBack(Callback);
	GPIO_setupPinDirection(PORTA_ID,PIN0_ID,PIN_OUTPUT);
	
	while(1)
	{
		/*Do nothing*/
	}
}
void Callback(void)
{
	ov ++;
	if(ov == NO_OV)
	{
		count ++;
		if(count >= DUTY_CYCLE)
		{
			GPIO_writePin(PORTA_ID,PIN0_ID,LOGIC_LOW);
			DUTY_CYCLE ++;
			if(DUTY_CYCLE == SIG_PERIOD+1)
			{
				DUTY_CYCLE = 0;
			}
		}
		if(count == SIG_PERIOD)
		{
			GPIO_writePin(PORTA_ID,PIN0_ID,LOGIC_LOW);
			count = 0;
		}
		ov =0;
	}
	
}