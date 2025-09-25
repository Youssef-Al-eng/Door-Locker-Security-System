/***************************************************************************************************************
 * File: pwm.h
 * Description: Header file for Timer0 PWM configuration using Fast PWM mode on AVR.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef MCAL_PWM_H_
#define MCAL_PWM_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                            Function Prototypes                              *
 *******************************************************************************/

/*
 * Initializes Timer0 in Fast PWM mode and starts generating PWM with the specified duty cycle.
 *
 * Parameters:
 *   duty_cycle - PWM duty cycle percentage (0 to 100)
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* MCAL_PWM_H_ */
