/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Source file for PWM (Pulse width modulation) driver
 *
 * Author: Muhammad Salah Ahmed Hefny
 *
 *******************************************************************************/

#include "pwm.h"
#include <avr/io.h>
#include "common_macros.h"

static uint8 PWM_prescaler_bits(uint8 prescaler_value)
{
	if (prescaler_value == 0)
		return 0;
	else if (prescaler_value == 1)
		return 1;
	else if (prescaler_value == 8)
		return 2;
	else if (prescaler_value == 64)
		return 3;
	else if (prescaler_value == 256)
		return 4;
	else if (prescaler_value == 1024)
		return 5;

}

void PWM_generatePwm(uint8 dutyCycle)
{

	TCNT0 = 0; /* Start Counting Up from zero */
	OCR0 = (2.54*dutyCycle); /* Setting Duty Cycle /*
	/*
	 * Configure Timer Registers   :
	 * TCCR0 Register:
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/pre_scaler CS00= x CS01= x  CS02= x
	 *
	 */
	DDRB  = DDRB | (1<<PB3); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC
	CLEAR_BIT(TCCR0, FOC0);
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	uint8 clock_select = PWM_prescaler_bits(PWM_PRESCALER);
	SET_BIT(TCCR0, COM01);
	TCCR0 = TCCR0 | (0x07&clock_select);
	CLEAR_BIT(TIMSK, OCIE0);
	CLEAR_BIT(TIMSK, TOIE0);


}
