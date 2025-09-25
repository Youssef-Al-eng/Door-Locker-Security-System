/***************************************************************************************************************
 * Door_Locker_Security_System_HMI_ECU.c
 * Author: Team TKH Embedded
 * Module: APPLICATION
 **************************************************************************************************************/

#include "Door_Locker_Security_System_HMI_ECU.h"
#include <util/delay.h>
#include <avr/io.h>
#include "../HAL/keypad.h"
#include "../HAL/lcd.h"
#include "../MCAL/uart.h"
#include "../MCAL/timer.h"

uint8 g_key[PASSWORD_SIZE], g_key_confirm[PASSWORD_SIZE];
uint8 g_key_again[PASSWORD_SIZE];
uint8 g_incorrectPass1 = 1;

void takePassFromUser(uint8 * a_ptr)
{
	uint8 counter = 0;
	while(counter < PASSWORD_SIZE)
	{
		_delay_ms(KEYPAD_DELAY);
		uint8 key = KEYPAD_getPressedKey();
		if(key != '=' && key != '-' && key != '+')
		{
			a_ptr[counter] = key;
			LCD_displayCharacter('*');
			counter++;
		}
	}
	while('=' != KEYPAD_getPressedKey());
}

void creatingPassword(void)
{
	uint8 wrongPass_flag;
	do{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "PLZ Enter Pass:");
		LCD_moveCursor(1, 0);
		takePassFromUser(g_key);

		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "PLZ Re-Enter The");
		LCD_displayStringRowColumn(1, 0, "Same Pass:");
		takePassFromUser(g_key_confirm);

		UART_sendByte(I_AM_READY);
		while(I_AM_READY != UART_receiveByte());
		UART_sendArray(g_key, PASSWORD_SIZE);
		UART_sendArray(g_key_confirm, PASSWORD_SIZE);

		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(I_AM_READY);
		wrongPass_flag = UART_receiveByte();

		if(wrongPass_flag)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 3, "Try Again.");
			_delay_ms(MESSAGE_DELAY);
		}
	}while(wrongPass_flag);
}

void checkPassAndAlarm(void)
{
	uint8 wrongPass_flag;
	do{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "PLZ Enter Old");
		LCD_displayStringRowColumn(1, 0, "Pass:");
		takePassFromUser(g_key_again);

		UART_sendByte(I_AM_READY);
		while(I_AM_READY != UART_receiveByte());
		UART_sendArray(g_key_again, PASSWORD_SIZE);

		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(I_AM_READY);
		wrongPass_flag = UART_receiveByte();

		if(wrongPass_flag)
		{
			if(3 == g_incorrectPass1)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 2, "System Locked");
				LCD_displayStringRowColumn(1, 1, "Wait For 1 Min");
				for (int i = 0; i < 59; i++) {
					_delay_ms(1000);
				}
				return;
			}
			else
			{
				g_incorrectPass1++;
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 3, "Try Again.");
				_delay_ms(MESSAGE_DELAY);
			}
		}
	}while(wrongPass_flag);
	g_incorrectPass1 = 1;
}

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
	Timer_deInit(TIMER1_ID);
}

int main(void)
{
	LCD_init();
	UART_ConfigType uart_configrations = {9600, UART_Parity_ODD, UART_STOP_1_BIT, MODE_EIGHT_BIT};
	UART_init(&uart_configrations);

	LCD_displayStringRowColumn(0, 6, "Hello");
	_delay_ms(MESSAGE_DELAY);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 1, "Welcome To our");
	LCD_displayStringRowColumn(1, 5, "System");
	_delay_ms(MESSAGE_DELAY);

	creatingPassword();

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Password Created");
	LCD_displayStringRowColumn(1, 2, "Successfully");
	_delay_ms(MESSAGE_DELAY);

	while(1)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");

		UART_sendByte(I_AM_READY);
		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(KEYPAD_getPressedKey());

		switch (KEYPAD_getPressedKey())
		{
		case '+':
			checkPassAndAlarm();
			if(3 == g_incorrectPass1)
			{
				g_incorrectPass1 = 1;
				break;
			}
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 1, "Door Unlocking");
			LCD_displayStringRowColumn(1, 4, "PLZ Wait");
			delay_15s();

			while(I_AM_READY != UART_receiveByte());
			UART_sendByte(I_AM_READY);
			if(UART_receiveByte())
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 1, "Wait For People");
				LCD_displayStringRowColumn(1, 4, "To Enter");
			}

			while(UART_receiveByte());

			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 2, "Door Locking");
			delay_15s();
			break;

		case '-':
			checkPassAndAlarm();
			if(3 == g_incorrectPass1)
			{
				g_incorrectPass1 = 1;
				break;
			}
			creatingPassword();
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Password Changed");
			LCD_displayStringRowColumn(1, 2, "Successfully");
			_delay_ms(MESSAGE_DELAY);
			break;

		default:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 3, "Try Again.");
			_delay_ms(MESSAGE_DELAY);
		}
	}
	return 0;
}
