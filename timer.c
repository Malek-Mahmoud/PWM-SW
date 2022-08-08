/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR timer driver
 *
 * Author: Malek Mahmoud Mohammmed
 *
 *******************************************************************************/

#include "timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ... Registers */
#include <avr/interrupt.h> /* For timer ISRs */
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_timer0CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_timer1CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_timer2CallBackPtr)(void) = NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/*******************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_timer0CallBackPtr != NULL_PTR)
	{
		(*g_timer0CallBackPtr)();
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_timer0CallBackPtr != NULL_PTR)
	{
		(*g_timer0CallBackPtr)();
	}
}
/*******************************************************************************/
ISR(TIMER1_OVF_vect)
{
	if(g_timer1CallBackPtr != NULL_PTR)
	{
		(*g_timer1CallBackPtr)();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_timer1CallBackPtr != NULL_PTR)
	{
		(*g_timer1CallBackPtr)();
	}
}
ISR(TIMER1_COMPB_vect)
{
	if(g_timer1CallBackPtr != NULL_PTR)
	{
		(*g_timer1CallBackPtr)();
	}
}
/*******************************************************************************/
ISR(TIMER2_OVF_vect)
{
	if(g_timer2CallBackPtr != NULL_PTR)
	{
		(*g_timer2CallBackPtr)();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_timer2CallBackPtr != NULL_PTR)
	{
		(*g_timer2CallBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the timer0 at normal mode
 */
void timer0_OVFmodeInit(timer_8bitConfigType * config_ptr)
{
	/* Set Timer initial value */
	TCNT0 = config_ptr->s_initTimeValue;
	/* Enable Timer0 Overflow Interrupt */
	TIMSK |= (1<<TOIE0);
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 */
	TCCR0 = (1<<FOC0);
	TCCR0 = (TCCR0 & 0XF8)|(config_ptr->s_clockselection & 0XF7);
}
/*
 * Description : Function to initialize the timer0 at CTC mode
 */
void timer0_CTCmodeInit(timer_8bitConfigType * config_ptr)
{
	/* Set Timer initial value */
	TCNT0 = config_ptr->s_initTimeValue;
	/* Set compare value */
	OCR0 = config_ptr->s_compareValue;
	/* Enable Timer0 t Compare Match Interrupt */
	TIMSK |= (1<<OCIE0);
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01) ;
	TCCR0 = (TCCR0 & 0XCF)|((config_ptr->s_compareOutputMode)<<4);
	TCCR0 = (TCCR0 & 0XF8)|(config_ptr->s_clockselection & 0XF7);
}
/*******************************************************************************/
/*
 * Description : Function to initialize the timer1 at normal mode
 */

void timer1_OVFmodeInit(timer_16bitConfigType * config_ptr)
{
	/* Set Timer initial value */
	TCNT1 = config_ptr->s_initTimeValue;
	/* Enable Timer0 Overflow Interrupt */
	TIMSK |= (1<<TOIE1);
	/* Configure the timer control register A
	 * 1. Non PWM mode FOC1A=0 & FOC1B=0
	 * 2. Normal Mode WGM11=0 & WGM10=0
	 * 3. Normal Mode COM1A0=0 & COM1A1=0=0
	 * 4. Normal Mode COM1B0=0 & COM1B1=0=0
	 * 5. TCCR1A = 0
	 */
	/* Configure the timer control register B
	 * 1. Normal Mode ICNC1=0 & ICES1=0
	 * 2. Normal Mode WGM12=0 & WGM13=0
	 */
	TCCR1B = (TCCR1B & 0XF8)|(config_ptr->s_clockselection & 0XF7);
}
/*
 * Description : Function to initialize the timer1 at CTC mode (channel A)
 */
void timer1_CTCAmodeInit(timer_16bitConfigType * config_ptr)
{
	/* Set Timer initial value */
	TCNT1 = config_ptr->s_initTimeValue;
	/* Set compare value */
	OCR1A = config_ptr->s_compareValue;
	/* Enable Timer1 Compare A Interrupt */
	TIMSK |= (1<<OCIE1A);
	/* Configure timer control register TCCR1A
	 * 1. Setting OC1A (COM1A1 & COM1A0)
	 * 2. FOC1A=1 FOC1B=0
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A = (1<<FOC1A);
	TCCR1A = (TCCR1A & 0x3f )|((config_ptr->s_compareOutputMode)<<6);
	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Setting Prescaler ( CS10 CS11 CS12 )
	 */
	TCCR1B = (1<<WGM12);
	TCCR1B = (TCCR1B & 0XF8)|(config_ptr->s_clockselection & 0XF7);

}
/*
 * Description : Function to initialize the timer1 at CTC mode (channel B)
 */
void timer1_CTCBmodeInit(timer_16bitConfigType * config_ptr)
{
	/* Set Timer initial value */
	TCNT1 = config_ptr->s_initTimeValue;
	/* Set compare value */
	OCR1B = config_ptr->s_compareValue;
	/* Enable Timer1 Compare B Interrupt */
	TIMSK |= (1<<OCIE1B);
	/* Configure timer control register TCCR1A
	 * 1. Setting OC1B (COM1B1 & COM1B0)
	 * 2. FOC1A=0 FOC1B=1
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A = (1<<FOC1B);
	TCCR1A = (TCCR1A & 0x3f )|((config_ptr->s_compareOutputMode)<<4);
	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Setting prescaler ( CS10 CS11 CS12 )
	 */
	TCCR1B = (1<<WGM12);
	TCCR1B = (TCCR1B & 0XF8)|(config_ptr->s_clockselection & 0XF7);
}
/*******************************************************************************/
/*
 * Description : Function to initialize the timer2 at normal mode
 */
void timer2_OVFmodeInit(timer_8bitConfigType * config_ptr)
{
	/* Set Timer initial value */
	TCNT2 = config_ptr->s_initTimeValue;
	/* Enable Timer2 Overflow Interrupt */
	TIMSK |= (1<<TOIE2);
	/* Configure the timer control register
	 * 1. Non PWM mode FOC2=1
	 * 2. Normal Mode WGM21=0 & WGM20=0
	 * 3. Normal Mode COM20=0 & COM21=0
	 */
	TCCR2 = (1<<FOC2);
	TCCR2 = (TCCR2 & 0XF8)|(config_ptr->s_clockselection & 0XF7);
}
/*
 * Description : Function to initialize the timer2 at CTC mode
 */
void timer2_CTCmodeInit(timer_8bitConfigType * config_ptr)
{
	/* Set Timer initial value */
	TCNT0 = config_ptr->s_initTimeValue;
	/* Set compare value */
	OCR0 = config_ptr->s_compareValue;
	/* Enable Timer2 Compare Match Interrupt */
	TIMSK |= (1<<OCIE2);
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC2=1
	 * 2. CTC Mode WGM21=1 & WGM20=0
	 */
	TCCR2 = (1<<FOC2) | (1<<WGM21) ;
	TCCR2 = (TCCR2 & 0XCF)|((config_ptr->s_compareOutputMode)<<4);
	TCCR2 = (TCCR2 & 0XF8)|(config_ptr->s_clockselection & 0XF7);

}
/*******************************************************************************/
/*
 * Description: Function to set the Call Back function address for timer0 normal mode interrupt handler.
 */
void timer0_OVFmode_setCallBack(void(*a_ptr)(void))
{
	g_timer0CallBackPtr = a_ptr;
}
/*
 * Description: Function to set the Call Back function address for timer0 CTC mode interrupt handler.
 */
void timer0_CTCmode_setCallBack(void(*a_ptr)(void))
{
	g_timer0CallBackPtr = a_ptr;
}
/*******************************************************************************/
/*
 * Description: Function to set the Call Back function address for timer1 normal mode interrupt handler.
 */
void timer1_OVFmode_setCallBack(void(*a_ptr)(void))
{
	g_timer1CallBackPtr = a_ptr;
}
/*
 * Description: Function to set the Call Back function address for timer1 CTC mode interrupt handler.
 */
void timer1_CTCmode_setCallBack(void(*a_ptr)(void))
{
	g_timer1CallBackPtr = a_ptr;
}
/*******************************************************************************/
/*
 * Description: Function to set the Call Back function address for timer2 normal mode interrupt handler.
 */
void timer2_OVFmode_setCallBack(void(*a_ptr)(void))
{
	g_timer2CallBackPtr = a_ptr;
}
/*
* Description: Function to set the Call Back function address for timer2 CTC mode interrupt handler.
 */
void timer2_CTCmode_setCallBack(void(*a_ptr)(void))
{
	g_timer2CallBackPtr = a_ptr;
}

{
	g_timer2CallBackPtr = a_ptr;
}
