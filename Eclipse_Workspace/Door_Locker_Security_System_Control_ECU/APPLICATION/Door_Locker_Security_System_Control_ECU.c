/***************************************************************************************************************
 * Door_Locker_Security_System_Control_ECU.c
 * Author: Youssef Alaa
 * Module: APPLICATION
 **************************************************************************************************************/

#include "Door_Locker_Security_System_Control_ECU.h"
#include <util/delay.h>
#include <avr/io.h>
#include "../MCAL/uart.h"
#include "../MCAL/twi.h"
#include "../HAL/external_eeprom.h"
#include "../HAL/motor.h"
#include "../HAL/buzzer.h"
#include "../HAL/pir_sensor.h"
#include "../MCAL/timer.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Entered passwords from user in the beginning. */
uint8 g_key[PASSWORD_SIZE], g_key_confirm[PASSWORD_SIZE];
/* Entered passwords from user to open the door. */
uint8 g_key_again[PASSWORD_SIZE];
/* Password stored in EEPROM. */
uint8 g_key_eeprom[PASSWORD_SIZE];
/* EEPROM address that has the password. */
uint16 address = 0x0000;
/* Flag will be high it the password is wrong. */
uint8 g_incorrectPass_flag;
/* Counter used if user enter password wrong. */
uint8 g_incorrectPass2 = 1;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function to receive 2 passwords and check them.
 * If they are identical, save the password to EEPROM.
 * Else, Receive the 2 passwords again.
 */
void receive2Password(uint8 * a_ptr1, uint8 * a_ptr2)
{
	uint8 counter, wrongPass_flag;

	do{
		/* Receiving the 2 passwords from MC1. */
		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(I_AM_READY);
		UART_receiveArray(a_ptr1);
		UART_receiveArray(a_ptr2);

		/* Check if the password and the re-enterd password are identical.
		 * If they are identical, continue the program.
		 * Else, receive the password again.
		 */
		for(counter = 0; counter < PASSWORD_SIZE; counter++)
		{
			if(a_ptr1[counter] != a_ptr2[counter])
			{
				/* Reset the entered password. */
				a_ptr1[counter] = 0;
				a_ptr2[counter] = 0;

				/* Send signal to MC1 that the password is wrong. */
				UART_sendByte(I_AM_READY);
				while(I_AM_READY != UART_receiveByte());
				UART_sendByte(WRONG_PASS);

				wrongPass_flag = 1;
				break;
			}
			else
			{
				wrongPass_flag = 0;
			}
		}
	}while(wrongPass_flag);

	/* Send signal to MC1 that the password is correct. */
	UART_sendByte(I_AM_READY);
	while(I_AM_READY != UART_receiveByte());
	UART_sendByte(CORRECT_PASS);

	/* Save the password in EEPROM. */
	for(counter = 0; counter < PASSWORD_SIZE; counter++)
	{
		EEPROM_writeByte(address+counter, a_ptr1[counter]);
		_delay_ms(20);		/* EEPROM delay > 10ms. */
	}
}

/*
 * Function to receive password and check it.
 * If the user entered password 3 times wrong, alarm will be on.
 * Else, user will enter the password again if it is wrong.
 * If the password is correct, the program will continue normally.
 */
void checkPassAndAlarm(void)
{
	uint8 counter;

	do{
		/* Receiving the password from MC1. */
		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(I_AM_READY);
		UART_receiveArray(g_key_again);

		/* Check if the entered password and the saved password are identical.
		 * If they are identical, open the door.
		 * Else, enter the password again.
		 * If user entered the password wrong 3 times, alarm will turn on.
		 */
		for(counter = 0; counter < PASSWORD_SIZE; counter++)
		{
			if(g_key_eeprom[counter] != g_key_again[counter])
			{
				g_incorrectPass_flag = 1;

				/* Send signal to MC1 that password is wrong. */
				UART_sendByte(I_AM_READY);
				while(I_AM_READY != UART_receiveByte());
				UART_sendByte(WRONG_PASS);
				break;
			}
			else
			{
				g_incorrectPass_flag = 0;
			}
		}

		/* If user entered password incorrect 3 times, alarm will turn on. */
		if(g_incorrectPass_flag)
		{
			if(3 == g_incorrectPass2)
			{
				Buzzer_on();
				/* Wait for 1 minute (59 seconds). */
				for (int i = 0; i < 59; i++) {
					_delay_ms(1000);
				}
				Buzzer_off();

				return;
			}
			else
			{
				Buzzer_off();
				g_incorrectPass2++;
			}
		}

	}while(g_incorrectPass_flag);

	/* Send signal to MC1 that the password is correct. */
	UART_sendByte(I_AM_READY);
	while(I_AM_READY != UART_receiveByte());
	UART_sendByte(CORRECT_PASS);
	/* Reset the counter if the password is correct. */
	g_incorrectPass2 = 1;
}

/*
 * Function to delay for 15s.
 */
void delay_15s(void)
{
	Timer_ConfigType timer_configrations1 = {0, 65535, TIMER1_ID, F_CPU_1024, COMPARE_MODE};
	Timer_init(&timer_configrations1);
	while(!(TIFR & (1<<OCF1A)));
	TIFR |= (1<<OCF1A);
	Timer_ConfigType timer_configrations2 = {0, 51621, TIMER1_ID, F_CPU_1024, COMPARE_MODE};
	Timer_init(&timer_configrations2);
	while(!(TIFR & (1<<OCF1A)));
	TIFR |= (1<<OCF1A);

	/* De-initialize timer1. */
	Timer_deInit(TIMER1_ID);

}

/*
 * The main function.
 */
int main(void)
{
	uint8 counter, key;

	/* Initialize UART with configurations. */
	UART_ConfigType uart_configrations = {9600, UART_Parity_ODD, UART_STOP_1_BIT, MODE_EIGHT_BIT};
	UART_init(&uart_configrations);

	/* Initialize TWI with configurations. */
	TWI_ConfigType twi_configrations = {0x01, 62};		/* For 100Kb/s. */
	TWI_init(&twi_configrations);

	/* Initialize Modules. */
	DcMotor_Init();
	Buzzer_init();
	PIR_init();

	/* Receive the 2 input passwords and check them. */
	/* If they are identical, save them to EEPROM. */
	receive2Password(g_key, g_key_confirm);

	while(1)
	{
		/* Receive the button that user had entered. */
		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(I_AM_READY);
		key = UART_receiveByte();

		switch(key)
		{
		case '+':
			/* Take the password from EEPROM. */
			for(counter = 0; counter < PASSWORD_SIZE; counter++)
			{
				EEPROM_readByte(address+counter, g_key_eeprom+counter);
			}

			/* Receive password and check it.*/
			checkPassAndAlarm();

			/* To go to home screen if the password was wrong 3 times. */
			if(3 == g_incorrectPass2)
			{
				g_incorrectPass2 = 1;
				break;
			}

			/* Open the door. */
			DcMotor_Rotate(CW, MOTOR_MAX_SPEED);

			/* Wait 15s until door is opened. */
			delay_15s();

			/* Send PIR status. */
			UART_sendByte(I_AM_READY);
			while(I_AM_READY != UART_receiveByte());
			UART_sendByte(PIR_getState());

			/* Wait until there is no movement. */
			while(PIR_getState())
			{
				DcMotor_Rotate(STOP, MOTOR_STOP);
			}

			/* Send PIR status when there is no movement.. */
			UART_sendByte(PIR_getState());

			/* Close the door. */
			DcMotor_Rotate(CCW, MOTOR_MAX_SPEED);

			/* Wait 15s until door is closed. */
			delay_15s();

			DcMotor_Rotate(STOP, MOTOR_STOP);

			break;

		case '-':
			/* Take the password from EEPROM. */
			for(counter = 0; counter < PASSWORD_SIZE; counter++)
			{
				EEPROM_readByte(address+counter, g_key_eeprom+counter);
			}

			/* Receive password and check it.*/
			checkPassAndAlarm();

			/* To go to home screen if the password was wrong 3 times. */
			if(3 == g_incorrectPass2)
			{
				g_incorrectPass2 = 1;
				break;
			}

			/* Receive the 2 input passwords and check them. */
			/* If they are identical, save them to EEPROM. */
			receive2Password(g_key, g_key_confirm);

			break;

		default :
			break;
		}
	}
	return 0;
}
