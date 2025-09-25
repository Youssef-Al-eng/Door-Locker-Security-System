/***************************************************************************************************************
 * File: buzzer.h
 * Description: Header file for buzzer control functions and pin configuration.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/

#define BUZZER_PORT_CONNECTION      PORTC_ID
#define BUZZER_PIN_CONNECION        PIN7_ID

/*******************************************************************************
 *                             Function Prototypes                             *
 *******************************************************************************/

/*
 * Initializes the buzzer pin as output and turns it off.
 */
void Buzzer_init(void);

/*
 * Turns on the buzzer.
 */
void Buzzer_on(void);

/*
 * Turns off the buzzer.
 */
void Buzzer_off(void);

#endif /* HAL_BUZZER_H_ */
