/******************************************************************************
 *
 * Module: Application
 *
 * File Name: application.c ( Control ECU )
 *
 * Description: Main application
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/

#include "application.h"
#include "twi.h"
#include "uart.h"
#include "common_macros.h"
#include "std_types.h"
#include <util/delay.h>
#include "external_eeprom.h"
#include "dcmotor.h"
#include "buzzer.h"
#include "timer1.h"
#include "avr/interrupt.h"

/* Global Variables */
uint8 volatile ticks=0;

/* Create configuration for the TIMER1 driver */
Timer1_ConfigType TIMER1_Configurations = {TIMER1_INITIAL_VALUE,TIMER1_COMPARE_VALUE,CLK256,TIMER_MODE_CTC};



int main()
{

	SET_BIT(SREG,7); /* Enable Global Interrupts */

	/* Drivers Configurations & Initialization */
	/* Create configuration structure for TWI (I2C) driver */
	TWI_ConfigType TWI_Configurations = {0b00000010, 0x02, prescaler_1};
	TWI_init(&TWI_Configurations);
	/* Create configuration structure for UART driver */
	UART_ConfigType UART_Configurations = {EIGTH_BITS, PARITRY_DISABLED, STOP_ONEBIT, BAUD_9600 };
	UART_init(&UART_Configurations);
	/* Set the Call back function pointer in the Timer driver for Interrupts handler */
	Timer1_setCallBack(tickscalc);
	DcMotor_Init();
	Buzzer_init();
	/* Local Variables Declarations */
	uint8 first_password[6];
	uint8 second_password[6];
	uint8 flag=0;

	while (1)
	{
		uint8 state=UART_recieveByte();
		flag=0;
		if (state==CREATE_PASS) /* Set password for first time */
		{
			UART_receiveString(first_password); /* Receive Password */
			_delay_us(10);
			UART_receiveString(second_password); /* Receive it again for checking */

			for (uint8 i=0;i<5;i++)
			{
				if (first_password[i]!=second_password[i])
				{
					flag=1;
					UART_sendByte(A_ERROR);
					break;
				}
			}

			if (!flag) /* No Difference in two passwords */
			{
				for (int i=0;i<5;i++)
				{
					EEPROM_writeByte(0x0000+i,first_password[i]);
					_delay_ms(10);

				}
				UART_sendByte(PASS_CREATED);
			}
		}

		else if (state==CHECK_PASS) /* Password Check with the one in EEprom */
		{
			UART_receiveString(first_password);
			uint8 br_flag=0;

			uint8 val=0;
			for (int i=0;i<5;i++)
			{

				EEPROM_readByte(0x0000+i, &val);  /* Read 0x0F from the external EEPROM */
				_delay_ms(10);
				if (first_password[i]!=val)
				{
					br_flag=1;
					UART_sendByte(A_ERROR);
					break;
				}
			}

			if (!br_flag)
			{
				UART_sendByte(PASS_CHECKED);
			}

		}
		else if (state==UNLOCK_MOTOR) /* Motor Open */
		{

			Timer1_init(&TIMER1_Configurations);
			UART_sendByte(MOTOR_UNLOCKED);
			ticks=0;

			while (ticks<=15)
			{
				DcMotor_Rotate(MOTOR_CW,MOTOR_MAX_SPEED);
			}
			ticks=0;
			UART_sendByte(MOTOR_OPENED);
			while (ticks<=3)
			{
				DcMotor_Rotate(MOTOR_STOP,0);
			}
			ticks=0;
			UART_sendByte(MOTOR_LOCKED);
			while (ticks<=15)
			{
				DcMotor_Rotate(MOTOR_ANTI_CW,MOTOR_MAX_SPEED);
			}
			Timer1_deinit();
			ticks=0;
			DcMotor_Rotate(MOTOR_STOP,0);
			UART_sendByte(DOOR_FINISH);
		}

		else if (state==CHANGE_PASSWORD) /* Change password */
		{
			UART_receiveString(first_password);
			uint8 br_flag=0;

			uint8 val=0;
			for (int i=0;i<5;i++)
			{

				EEPROM_readByte(0x0000+i, &val);  /* Read 0x0F from the external EEPROM */
				_delay_ms(10);
				if (first_password[i]!=val)
				{
					br_flag=1;
					UART_sendByte(A_ERROR);
					break;
				}
			}

			if (!br_flag)
			{
				UART_sendByte(PASSWORD_CHANGED);
			}
			state=WAITING_STATE;// wait until getting new state

		}
		else if (state==THREE_UMATCHED_PASS)
		{

			Buzzer_on();
			Timer1_delay(60);
			Buzzer_off();
			state=WAITING_STATE; // wait until getting new state

		}
	}
}

void tickscalc(void)
{
	ticks++;
}

void Timer1_delay(uint8 seconds)
{
	Timer1_init(&TIMER1_Configurations);
	Timer1_setCallBack(tickscalc);
	ticks=0;
	while (ticks<=seconds); /* Do Nothing */
	Timer1_deinit();
	ticks=0;

}

