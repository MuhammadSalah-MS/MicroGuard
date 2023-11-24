 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the AVR TIMER1 driver
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/


#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

#define TIMER1_INITIAL_VALUE	0			/* TCNT Register Initial Value */
#define TIMER1_COMPARE_VALUE	31250		/* OCR  Register Value */

/* Timer1 User-defined Configurations */

typedef enum
{
	NO_CLK,CLK1,CLK8,CLK64,CLK256,CLK1024,CLK_EXT_FAL,CLK_EXT_RIS
}Timer1_Prescaler;

typedef enum
{
	TIMER_MODE_NORMAL,TIMER_MODE_PWM8,TIMER_MODE_PWM9,TIMER_MODE_PWM10,TIMER_MODE_CTC,TIMER_MODE_PWM_FAST8,TIMER_MODE_PWM_FAST9,TIMER_MODE_PWM_FAST10,
	TIMER_MODE_PWM_PF_ICR,TIMER_MODE_PWM_PF_OCRA1,TIMER_MODE_PWM_ICR,TIMER_MODE_PWM_OCRA1,TIMER_MODE_CTC_ICR1,TIMER_MODE_RESERVED,TIMER_MODE_PWM_FAST_ICR,TIMER_MODE_PWM_FAST_OCRA1
}Timer1_Mode;


typedef struct
{
	uint16 initial_value;
	uint16 compare_value;
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
}Timer1_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize the AVR TIMER1 by:
 * 1. Setup the timing like with ability to configure in different modes (Normal / CTC ..)
 * 2. Enable the CLOCK.
 * 3. Setup the user-define Frequency.
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 * Function Responsible to disable the AVR TIMER1 by disable the clock source
 * and remove call back function
 */
void Timer1_deinit(void);

/*
 * Description :
 * Function Responsible to set the call function - used in application - address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));






#endif /* TIMER1_H_ */
