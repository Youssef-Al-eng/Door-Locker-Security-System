/***************************************************************************************************************
 * File: buzzer.c
 * Description: Source file for controlling the buzzer (init, turn on, turn off).
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#include "buzzer.h"
#include "../MCAL/gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Initializes the buzzer pin as output and ensures the buzzer is off.
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_CONNECTION, BUZZER_PIN_CONNECION, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_CONNECTION, BUZZER_PIN_CONNECION, LOGIC_LOW);
}

/*
 * Turns on the buzzer.
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_CONNECTION, BUZZER_PIN_CONNECION, LOGIC_HIGH);
}

/*
 * Turns off the buzzer.
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_CONNECTION, BUZZER_PIN_CONNECION, LOGIC_LOW);
}
