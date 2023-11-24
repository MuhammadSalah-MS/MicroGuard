/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Buzzer driver Source file
 *
 * Author: Muhammad Salah Ahmed Hefny
 *
 *******************************************************************************/


#include "buzzer.h"
#include "gpio.h"
#include "common_macros.h"

/*
 * Description :
 * Function Responsible to setup the Buzzer Pin Direction as OUTPUT
 *
 */
void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

/*
 * Description :
 * Function Responsible to enable the buzzer
 *
 */
void Buzzer_on()
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

/*
 * Description :
 * Function Responsible to disable the buzzer
 *
 */
void Buzzer_off()
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}
