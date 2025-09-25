/***************************************************************************************************************
 * File: pwm.c
 * Description: Source file for generating PWM using Timer0 in Fast PWM mode on AVR.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#include "pwm.h"
#include <avr/io.h>

/*******************************************************************************
 *                          Function Definitions                               *
 *******************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0;  // Initialize Timer0 counter

	OCR0 = (duty_cycle * 255) / 100;  // Set output compare register value based on duty cycle

	// Configure PB3/OC0 as output
	DDRB |= (1 << PB3);

	/*
	 * Timer0 Configuration:
	 * - Fast PWM Mode: WGM01 = 1, WGM00 = 1
	 * - Non-Inverted Mode: COM01 = 1, COM00 = 0
	 * - Prescaler F_CPU/64: CS01 = 1, CS00 = 1
	 */
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01) | (1 << CS00);
}
