/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for the AVR TIMER1 driver
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/

#include "timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"
#include "std_types.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/


ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initialize the AVR TIMER1 by:
 * 1. Setup the timing like with ability to configure in different modes (Normal / CTC ..)
 * 2. Enable the CLOCK.
 * 3. Setup the user-define Frequency.
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/************************** TCCR1A Description **************************
	 * COM1A1 = Disabled in non-pwm modes
	 * COM1A0 = Disabled in non-pwm modes
	 * COM1B1 = Disabled in non-pwm modes
	 * COM1B0 = Disabled in non-pwm modes
	 * FOC1A  = active in non-pwm modes
	 * FOC1B  = active in non-pwm modes
	 * WGM11  = affect timer mode / operation
	 * WGM10  = affect timer mode / operation
	 * All bits are configured with the pre-defined dynamic configurations
	 ***********************************************************************/

	TCCR1A=0;
	/************************** TCCR1B Description **************************
	 * ICNC1 = Disabled in non ICU usage
	 * ICES1 = Disabled in non ICU usage
	 * RES 	 = reserved bit
	 * WGM13 = affect timer mode / operation
	 * WGM12 = affect timer mode / operation
	 * CS12  = Clock Select bit
	 * CS11  = Clock Select bit
	 * CS10  =  Clock Select bit
	 * All bits are configured with the pre-defined dynamic configurations
	 ***********************************************************************/
	TCCR1B=0;
	TCNT1=0;

	TCNT1=Config_Ptr->initial_value;

	/************************** TIMSK Description **************************
	 * OCIE2 = Timer2 bit - not used -
	 * TOIE2 = Timer2 bit - not used -
	 * TICIE1 = Disabled in non ICU usage
	 * OCIE1A  = Enabled to allow compare match A interrupt
	 * OCIEB  =  1/0 allow/disallow compare match B interrupt
	 * TOIE1 = Enabled to allow timerover flow intterupt
	 * OCIE0 = Timer0 bit - not used -
	 * TOIE0 = Timer0 bit - not used -
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/


	if (Config_Ptr->mode==TIMER_MODE_NORMAL)
	{
		/* NOT PWM MODE */
		SET_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1A,FOC1B);

		/* Normal Mode (TIMER OVER FLOW) Interrupt Enable */
		SET_BIT(TIMSK,TOIE1);


	}
	else if (Config_Ptr->mode==TIMER_MODE_CTC)
	{
		/* NOT PWM MODE */
		SET_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1A,FOC1B);

		SET_BIT(TCCR1B,WGM12);
		OCR1A=Config_Ptr->compare_value;

		/* CTC (COMPARE MATCH) Interrupt Enable */
		SET_BIT(TIMSK,OCIE1A);


	}
	TCCR1B|=Config_Ptr->prescaler;


}

/*
 * Description :
 * Function Responsible to Disable Timer1
 */
void Timer1_deinit(void)
{
	/* Disable Clock Source entered to Timer */
	TCCR1B=0;
	/* Reset the global pointer value */
	g_callBackPtr = NULL_PTR;

}

/*
 * Description :
 * Function Responsible to Set the Call-back function used in Interrupt-Handeler
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* set the call back function address ar received */
	g_callBackPtr = a_ptr;
}


