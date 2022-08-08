
 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR timer driver
 *
 * Author: Malek Mahmoud Mohammmed
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,CLK_1,CLK_8,CLK_64,CLK_256,CLK_1024,CLK_EXT_FALLING,CLK_EXT_RISING
}timer_clockSelectType;
typedef enum
{
	DISABLE,TOGGLE_OCx,CLEAR_OCx,SET_OCx
}timer_compareOutputModeType;
typedef struct
{
	uint8 s_initTimeValue;
	uint8 s_compareValue;
	timer_clockSelectType s_clockselection;
	timer_compareOutputModeType s_compareOutputMode;

}timer_8bitConfigType;

typedef struct
{
	uint16 s_initTimeValue;
	uint16 s_compareValue;
	timer_clockSelectType s_clockselection;
	timer_compareOutputModeType s_compareOutputMode;
}timer_16bitConfigType;
/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/
/*
 * Description : Function to initialize the timer0 at normal mode
 */
void timer0_OVFmodeInit(timer_8bitConfigType * config_ptr);
/*
 * Description : Function to initialize the timer0 at CTC mode
 */
void timer0_CTCmodeInit(timer_8bitConfigType * config_ptr);
/*******************************************************************************/
/*
* Description : Function to initialize the timer1 at normal mode
 */

void timer1_OVFmodeInit(timer_16bitConfigType * config_ptr);
/*
 * Description : Function to initialize the timer1 at CTC mode (channel A)
 */

void timer1_CTCAmodeInit(timer_16bitConfigType * config_ptr);
/*
 * Description : Function to initialize the timer1 at CTC mode (channel B)
 */

void timer1_CTCBmodeInit(timer_16bitConfigType * config_ptr);
/*******************************************************************************/
/*
 * Description : Function to initialize the timer2 at normal mode
 */
void timer2_OVFmodeInit(timer_8bitConfigType * config_ptr);
/*
 * Description : Function to initialize the timer2 at CTC mode
 */
void timer2_CTCmodeInit(timer_8bitConfigType * config_ptr);
/*******************************************************************************/
/*
 * Description: Function to set the Call Back function address for timer0 normal mode interrupt handler.
 */
void timer0_OVFmode_setCallBack(void(*a_ptr)(void));
/*
 * Description: Function to set the Call Back function address for timer0 CTC mode interrupt handler.
 */
void timer0_CTCmode_setCallBack(void(*a_ptr)(void));
/*******************************************************************************/
/*
* Description: Function to set the Call Back function address for timer1 normal mode interrupt handler.
 */
void timer1_OVFmode_setCallBack(void(*a_ptr)(void));
/*
 * Description: Function to set the Call Back function address for timer1 CTC mode interrupt handler.
 */
void timer1_CTCmode_setCallBack(void(*a_ptr)(void));
/*******************************************************************************/
/*
 * Description: Function to set the Call Back function address for timer2 normal mode interrupt handler.
 */
void timer2_OVFmode_setCallBack(void(*a_ptr)(void));
/*
 * Description: Function to set the Call Back function address for timer2 CTC mode interrupt handler.
 */
void timer2_CTCmode_setCallBack(void(*a_ptr)(void));

#endif /* TIMER_H_ */
