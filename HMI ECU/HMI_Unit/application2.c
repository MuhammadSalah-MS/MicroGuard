/******************************************************************************
 *
 * Module: Application
 *
 * File Name: application.c ( HMI ECU )
 *
 * Description: Main application
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/



#include "application2.h"

#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer1.h"
#include "std_types.h"
#include "common_macros.h"
#include "avr/interrupt.h"
#include <util/delay.h>




/* Global Variables */
uint8 volatile ticks=0;
uint8 unmatched_count=0;


/* Create configuration for the TIMER1 driver */
Timer1_ConfigType TIMER1_Configurations = {TIMER1_INITIAL_VALUE,TIMER1_COMPARE_VALUE,CLK256,TIMER_MODE_CTC};


/* Function Prototypes */
void tickscalc(void);
void Timer1_delay(uint8 seconds);
uint8 password_Checker();
void sendPassword();

/* Main Function */
int main()
{
	SET_BIT(SREG,7); /* Enable Global Interrupts */


	/* Drivers Configurations & Initialization */
	uint8 password_created=0;
	UART_ConfigType UART_Configurations = {EIGTH_BITS,PARITRY_DISABLED,STOP_ONEBIT ,BAUD_9600 };
	UART_init(&UART_Configurations);
	LCD_init();

	/* Local Variables Declarations */
	uint8 state=0;
	uint8 operation_in=0;

	if (!password_created)
	{
		state=CREATE_PASS;
	}
	else {
		state=MAIN_OPTIONS;
	}



	while (1)
	{

		if (state==CREATE_PASS) /* First State for first time entry */
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Pls Enter New");
			LCD_displayStringRowColumn(1,0,"Password:");
			LCD_moveCursor(1,9); /* Adjust password place */
			UART_sendByte(CREATE_PASS);  /* Inform the Control ECU */
			sendPassword();		 /* Receive Password , And send to Control */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Pls Re-Enter the     ");
			LCD_displayStringRowColumn(1,0,"same pass:");
			_delay_us(10);
			sendPassword();
			if (UART_recieveByte()==PASS_CREATED)
			{
				password_created=1;
				state=MAIN_OPTIONS; /* Change to Main Options if passwords received correctly */
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString("What the hell");
			}

		}

		else if (state==MAIN_OPTIONS)
		{
			LCD_clearScreen();
			/* Display The Options */
			LCD_displayStringRowColumn(0,0,"+ : Open Door");
			LCD_displayStringRowColumn(1,0,"- : Change Pass");
			operation_in=KEYPAD_getPressedKey(); /* Read the operation */
			_delay_ms(200);
			/* Reject any other input buttons except + and - */
			while (operation_in!='+'&&operation_in!='-')
			{
				LCD_moveCursor(1,15);
				operation_in=KEYPAD_getPressedKey();
				LCD_displayCharacter(operation_in);
				_delay_ms(200);
			}
			/* Give three time to read password if not correct */
			for (uint8 i=0;i<3;i++)
			{
				if(password_Checker()==PASS_CHECKED)
				{
					if (operation_in=='+')
					{
						state=OPEN_DOOR;
					}
					else if (operation_in=='-')
					{
						state=CHANGE_PASSWORD;
					}
					unmatched_count=0;
					break; /* break if password is correct */
				}
				else {

					unmatched_count++;

				}
			}

			if (unmatched_count==3)
			{
				UART_sendByte(THREE_UMATCHED_PASS);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,5,"Error!!");
				Timer1_delay(60);
				unmatched_count=0;
				state=MAIN_OPTIONS;

			}

		}

		else if (state==OPEN_DOOR)
		{
			UART_sendByte(UNLOCK_MOTOR);
			uint8 screen_status;
			screen_status=UART_recieveByte();
			if (screen_status==MOTOR_UNLOCKED)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Door is");
				LCD_displayStringRowColumn(1,0,"Un-lokcing");
			}
			screen_status = UART_recieveByte();
			if (screen_status==MOTOR_OPENED)
			{
				LCD_clearScreen();
				LCD_displayString("Door is Open");

			}
			screen_status = UART_recieveByte();
			if (screen_status==MOTOR_LOCKED)
			{
				LCD_clearScreen();
				LCD_displayString("Door is Locking");
			}
			screen_status = UART_recieveByte();
			if (screen_status==DOOR_FINISH)
			{
				state=MAIN_OPTIONS;
			}
		}
		else if (state==CHANGE_PASSWORD)
		{

			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Pls re-Enter Pass ");
			LCD_moveCursor(1,0);
			UART_sendByte(CHANGE_PASSWORD);
			sendPassword();
			if (UART_recieveByte()==PASSWORD_CHANGED)
			{
				state=CREATE_PASS;
			}


		}


	}

}

uint8 password_Checker()
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Enter Pass:");
	LCD_moveCursor(1,0);
	UART_sendByte(CHECK_PASS);
	sendPassword();
	uint8 value;
	value=UART_recieveByte();
	return value;

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

void sendPassword()
{
	uint8 password[7];
	for (int i=0;i<5;i++)
	{
		password[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(250); /* Press time */
	}
	while (KEYPAD_getPressedKey()!='+'); /* Enter Sending Button */
	password[5]='#';
	password[6]='\0';

	UART_sendString(password); /* Send Password To control unit */

}

