/***************************************************************************************************************
 * File: timer.h
 * Module: Timer Driver (Timer0, Timer1, Timer2)
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                            Types Declaration                                *
 *******************************************************************************/

typedef enum {
	TIMER0_ID, TIMER1_ID, TIMER2_ID
} Timer_ID_Type;

typedef enum {
	NO_CLOCK,
	F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024,
	F_CPU_8_TIMER2 = 2, F_CPU_32_TIMER2, F_CPU_64_TIMER2,
	F_CPU_128_TIMER2, F_CPU_256_TIMER2, F_CPU_1024_TIMER2
} Timer_ClockType;

typedef enum {
	NORMAL_MODE, COMPARE_MODE
} Timer_ModeType;

typedef struct {
	uint16 timer_InitialValue;
	uint16 timer_compare_MatchValue;  // Used in COMPARE_MODE only
	Timer_ID_Type timer_ID;
	Timer_ClockType timer_clock;
	Timer_ModeType timer_mode;
} Timer_ConfigType;

/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/

/* Initialize timer based on configuration */
void Timer_init(const Timer_ConfigType *Config_Ptr);

/* Disable and reset the specified timer */
void Timer_deInit(Timer_ID_Type timer_type);

/* Get the current counter value of the timer */
uint16 Timer_getTimerValue(Timer_ID_Type timer_type);

/* Register a callback function for the specified timer */
void Timer_setCallBack(void (*a_ptr)(void), Timer_ID_Type timer_type);

#endif /* MCAL_TIMER_H_ */
