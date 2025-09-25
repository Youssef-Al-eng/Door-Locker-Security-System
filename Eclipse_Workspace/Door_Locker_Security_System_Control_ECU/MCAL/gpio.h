/***************************************************************************************************************
 * File: gpio.h
 * Description: Header file for controlling AVR GPIO pins and ports.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef MCAL_GPIO_H_
#define MCAL_GPIO_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

typedef enum {
	PIN_INPUT,
	PIN_OUTPUT
} GPIO_PinDirectionType;

typedef enum {
	PORT_INPUT,
	PORT_OUTPUT = 0xFF
} GPIO_PortDirectionType;

/*******************************************************************************
 *                            Function Prototypes                              *
 *******************************************************************************/

/*
 * Sets the direction of a specified pin on a specified port.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Writes a logic value (HIGH/LOW) to a specific pin.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Reads and returns the logic value of a specific pin.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
 * Sets the direction for all pins of a specific port.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*
 * Writes a value to all pins in a specific port.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Reads and returns the value of a specific port.
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* MCAL_GPIO_H_ */
