/*/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dcmotor.c
 *
 * Description: DC Motor driver Source file
 *
 * Author: Muhammad Salah Ahmed Hefny
 *
 *******************************************************************************/
#include "dcmotor.h"
#include "common_macros.h"
#include "std_types.h"
#include "pwm.h"
#include "gpio.h"

void DcMotor_Init(void)
{

	GPIO_setupPinDirection(MOTOR1_INPUT_PORT, MOTOR1_INPUT_PIN0, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR1_INPUT_PORT, MOTOR1_INPUT_PIN1, PIN_OUTPUT);
	GPIO_writePin(MOTOR1_INPUT_PORT,MOTOR1_INPUT_PIN0,LOGIC_LOW);
	GPIO_writePin(MOTOR1_INPUT_PORT,MOTOR1_INPUT_PIN1,LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{

	/*
	 * Description :
	 * Motor Stops when its two terminals are low (LOW,LOW)
	 * Motor Changes its direction by changing the voltage on its terminals (HIGH,LOW) -  (LOW,HIGH)
	 * Motor Speed Range between 0-100
	 */

	if (state == MOTOR_STOP)
	{
		GPIO_writePin(MOTOR1_INPUT_PORT, MOTOR1_INPUT_PIN0, LOGIC_LOW);
		GPIO_writePin(MOTOR1_INPUT_PORT, MOTOR1_INPUT_PIN1, LOGIC_LOW);
	}
	else if (state == MOTOR_CW)
	{
		GPIO_writePin(MOTOR1_INPUT_PORT, MOTOR1_INPUT_PIN0, LOGIC_LOW);
		GPIO_writePin(MOTOR1_INPUT_PORT, MOTOR1_INPUT_PIN1, LOGIC_HIGH);

	}
	else if (state == MOTOR_ANTI_CW)
	{
		GPIO_writePin(MOTOR1_INPUT_PORT, MOTOR1_INPUT_PIN0, LOGIC_HIGH);
		GPIO_writePin(MOTOR1_INPUT_PORT ,MOTOR1_INPUT_PIN1, LOGIC_LOW);

	}

	PWM_generatePwm(speed);

}
