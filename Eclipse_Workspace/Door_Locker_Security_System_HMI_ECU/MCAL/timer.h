/***************************************************************************************************************
 * timer.h
 * Author: Youssef Alaa
 * Description: Header file for AVR Timer driver configuration and API definitions.
 ***************************************************************************************************************/

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_

#include "../Standard_Types/standard_types.h"

// Timer ID options
typedef enum
{
	TIMER0_ID,
	TIMER1_ID,
	TIMER2_ID
} Timer_ID_Type;

// Clock source selection
typedef enum
{
	NO_CLOCK,
	F_CPU_CLOCK,
	F_CPU_8,
	F_CPU_64,
	F_CPU_256,
	F_CPU_1024,
	F_CPU_8_TIMER2 = 2,
	F_CPU_32_TIMER2,
	F_CPU_64_TIMER2,
	F_CPU_128_TIMER2,
	F_CPU_256_TIMER2,
	F_CPU_1024_TIMER2
} Timer_ClockType;

// Timer operating mode
typedef enum
{
	NORMAL_MODE,
	COMPARE_MODE
} Timer_ModeType;

// Timer configuration structure
typedef struct
{
	uint16 timer_InitialValue;
	uint16 timer_compare_MatchValue; // Used in compare mode only
	Timer_ID_Type timer_ID;
	Timer_ClockType timer_clock;
	Timer_ModeType timer_mode;
} Timer_ConfigType;

// Initialize timer with given configuration
void Timer_init(const Timer_ConfigType * Config_Ptr);

// Deinitialize a timer by ID
void Timer_deInit(Timer_ID_Type timer_type);

// Get the current value of a timer
uint16 Timer_getTimerValue(Timer_ID_Type timer_type);

// Register a callback function for a specific timer
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

#endif /* MCAL_TIMER_H_ */
