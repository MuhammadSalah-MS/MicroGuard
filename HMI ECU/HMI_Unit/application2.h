/******************************************************************************
 *
 * Module: Application
 *
 * File Name: application.c ( HMI ECU )
 *
 * Description: Main application header file
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/


#ifndef CONTROLUNIT_APPMACROS_H_
#define CONTROLUNIT_APPMACROS_H_

#include "std_types.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define CREATE_PASS 'A'
#define PASS_CREATED 'A'
#define CHECK_PASS 'B'
#define PASS_CHECKED 'B'
#define UNLOCK_MOTOR 'C'
#define MOTOR_UNLOCKED 'C'
#define OPEN_MOTOR 'Q'
#define MOTOR_OPENED 'Q'
#define LOCK_MOTOR 'W'
#define MOTOR_LOCKED 'W'
#define DOOR_FINISH 'R'
#define CHANGE_PASSWORD 'D'
#define PASSWORD_CHANGED 'D'
#define ERROR 'Z'
#define THREE_UMATCHED_PASS 'E'
#define WAITING_STATE 'F'
#define MAIN_OPTIONS 1
#define OPEN_DOOR 2

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void tickscalc(void);

void Timer1_delay(uint8 seconds);


#endif /* CONTROLUNIT_APPMACROS_H_ */
