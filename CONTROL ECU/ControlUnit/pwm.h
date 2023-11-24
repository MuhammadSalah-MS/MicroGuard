/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for PWM (Pulse width modulation) driver
 *
 * Author: Muhammad Salah Ahmed Hefny
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define CPU_FREQUENCY 8000000
#define PWM_PRESCALER 8

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Private function to adjust the prescaler bits needed for PWM register
 */
static uint8 PWM_prescaler_bits(uint8 prescaler_value);

/*
 * Description :
 *	function responsible to generate PWM signals with specific duty-cycles
 */

void PWM_generatePwm(uint8 dutyCycle);


#endif /* PWM_H_ */
