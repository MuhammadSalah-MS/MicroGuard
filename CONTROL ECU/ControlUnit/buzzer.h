 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PIN			PIN0_ID
#define BUZZER_PORT			PORTA_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Buzzer_init();
void Buzzer_on();
void Buzzer_off();


#endif /* BUZZER_H_ */
