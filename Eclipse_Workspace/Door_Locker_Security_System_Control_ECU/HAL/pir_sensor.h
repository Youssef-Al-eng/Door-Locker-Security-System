/***************************************************************************************************************
 * File: pir_sensor.h
 * Description: Header file for interfacing with a PIR motion sensor.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef HAL_PIR_SENSOR_H_
#define HAL_PIR_SENSOR_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/

#define PIR_PORT_CONNECTION     PORTC_ID
#define PIN_CONNECTION          PIN2_ID

/*******************************************************************************
 *                             Function Prototypes                             *
 *******************************************************************************/

/*
 * Initializes the PIR sensor by configuring its pin as input.
 */
void PIR_init(void);

/*
 * Reads and returns the current state of the PIR sensor (0 or 1).
 */
uint8 PIR_getState(void);

#endif /* HAL_PIR_SENSOR_H_ */
