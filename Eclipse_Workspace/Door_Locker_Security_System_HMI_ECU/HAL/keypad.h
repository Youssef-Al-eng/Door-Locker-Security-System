/***************************************************************************************************************
 * keypad.h
 * Author: Youssef Alaa
 * Description: Header file for 4x4 matrix keypad driver.
 *              Provides function prototype for reading pressed key and related configurations.
 ***************************************************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../Standard_Types/standard_types.h"

// Keypad configuration: rows and columns
#define KEYPAD_NUM_COLS         4
#define KEYPAD_NUM_ROWS         4

// Keypad pin connections
#define KEYPAD_ROW_PORT_ID      PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID PIN0_ID

#define KEYPAD_COL_PORT_ID      PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID PIN4_ID

// Button logic levels
#define KEYPAD_BUTTON_PRESSED   LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED  LOGIC_HIGH

// Returns the pressed key on the keypad
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
