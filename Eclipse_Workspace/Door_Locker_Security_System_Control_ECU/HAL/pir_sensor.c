/***************************************************************************************************************
 * File: pir_sensor.c
 * Description: Source file for initializing and reading data from a PIR motion sensor.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#include "pir_sensor.h"
#include <avr/io.h>
#include "../MCAL/gpio.h"

/*******************************************************************************
 *                             Function Definitions                             *
 *******************************************************************************/

/*
 * Initializes the PIR sensor by setting its GPIO pin as input.
 */
void PIR_init(void)
{
	GPIO_setupPinDirection(PIR_PORT_CONNECTION, PIN_CONNECTION, PIN_INPUT);
}

/*
 * Returns the state of the PIR sensor (1 if motion detected, 0 otherwise).
 */
uint8 PIR_getState(void)
{
	return GPIO_readPin(PIR_PORT_CONNECTION, PIN_CONNECTION);
}
