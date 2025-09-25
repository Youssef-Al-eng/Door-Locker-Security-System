/***************************************************************************************************************
 * keypad.c
 * Author: Youssef Alaa
 * Description: Source file for the 4x4 matrix keypad driver.
 ***************************************************************************************************************/

#include "keypad.h"
#include "../MCAL/gpio.h"
#include <util/delay.h>

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif

#endif // !STANDARD_KEYPAD

uint8 KEYPAD_getPressedKey(void)
{
	uint8 col, row;

	// Configure all keypad pins as input initially
	for (row = 0; row < KEYPAD_NUM_ROWS; row++)
		GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_INPUT);

	for (col = 0; col < KEYPAD_NUM_COLS; col++)
		GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col, PIN_INPUT);

	while (1)
	{
		for (row = 0; row < KEYPAD_NUM_ROWS; row++)
		{
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, KEYPAD_BUTTON_PRESSED);

			for (col = 0; col < KEYPAD_NUM_COLS; col++)
			{
				if (GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col) == KEYPAD_BUTTON_PRESSED)
				{
#if (KEYPAD_NUM_COLS == 3)
#ifdef STANDARD_KEYPAD
					return ((row * KEYPAD_NUM_COLS) + col + 1);
#else
					return KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
#endif
#elif (KEYPAD_NUM_COLS == 4)
#ifdef STANDARD_KEYPAD
					return ((row * KEYPAD_NUM_COLS) + col + 1);
#else
					return KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
#endif
#endif
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_INPUT);
			_delay_ms(5); // Debounce delay for Proteus simulation
		}
	}
}

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	switch (button_number)
	{
	case 10: return '*';
	case 11: return 0;
	case 12: return '#';
	default: return button_number;
	}
}
#elif (KEYPAD_NUM_COLS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	switch (button_number)
	{
	case 1:  return 7;
	case 2:  return 8;
	case 3:  return 9;
	case 4:  return '%';
	case 5:  return 4;
	case 6:  return 5;
	case 7:  return 6;
	case 8:  return '*';
	case 9:  return 1;
	case 10: return 2;
	case 11: return 3;
	case 12: return '-';
	case 13: return 13; // Custom use (e.g., Enter)
	case 14: return 0;
	case 15: return '=';
	case 16: return '+';
	default: return button_number;
	}
}
#endif

#endif // !STANDARD_KEYPAD
