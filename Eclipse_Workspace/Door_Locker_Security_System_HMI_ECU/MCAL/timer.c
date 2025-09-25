/***************************************************************************************************************
 * timer.c
 * Author: Youssef Alaa
 * Description: Source file for AVR Timer driver supporting Timer0, Timer1, and Timer2 in Normal and Compare modes.
 ***************************************************************************************************************/

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Global variables to hold the callback function pointers
static volatile void (*g_callBackPtr_timer0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr_timer1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr_timer2)(void) = NULL_PTR;

// Timer0 ISR
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr_timer0 != NULL_PTR)
		(*g_callBackPtr_timer0)();
}
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr_timer0 != NULL_PTR)
		(*g_callBackPtr_timer0)();
}

// Timer1 ISR
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr_timer1 != NULL_PTR)
		(*g_callBackPtr_timer1)();
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr_timer1 != NULL_PTR)
		(*g_callBackPtr_timer1)();
}

// Timer2 ISR
ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr_timer2 != NULL_PTR)
		(*g_callBackPtr_timer2)();
}
ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr_timer2 != NULL_PTR)
		(*g_callBackPtr_timer2)();
}

// Initialize the selected Timer
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	switch(Config_Ptr->timer_ID)
	{
	case TIMER0_ID:
		TCCR0 = (1<<FOC0) | ((Config_Ptr->timer_mode)<<WGM01) | ((Config_Ptr->timer_clock)<<CS00);
		TCNT0 = Config_Ptr->timer_InitialValue;
		if(Config_Ptr->timer_mode == COMPARE_MODE)
			OCR0 = Config_Ptr->timer_compare_MatchValue;
		if(Config_Ptr->timer_mode == NORMAL_MODE)
			TIMSK |= (1<<TOIE0);
		else
			TIMSK |= (1<<OCIE0);
		break;

	case TIMER1_ID:
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);
		TCCR1B = ((Config_Ptr->timer_mode)<<WGM12) | ((Config_Ptr->timer_clock)<<CS10);
		TCNT1 = Config_Ptr->timer_InitialValue;
		if(Config_Ptr->timer_mode == COMPARE_MODE)
			OCR1A = Config_Ptr->timer_compare_MatchValue;
		if(Config_Ptr->timer_mode == NORMAL_MODE)
			TIMSK |= (1<<TOIE1);
		else
			TIMSK |= (1<<OCIE1A);
		break;

	case TIMER2_ID:
		TCCR2 = (1<<FOC2) | ((Config_Ptr->timer_mode)<<WGM21) | ((Config_Ptr->timer_clock)<<CS20);
		TCNT2 = Config_Ptr->timer_InitialValue;
		if(Config_Ptr->timer_mode == COMPARE_MODE)
			OCR2 = Config_Ptr->timer_compare_MatchValue;
		if(Config_Ptr->timer_mode == NORMAL_MODE)
			TIMSK |= (1<<TOIE2);
		else
			TIMSK |= (1<<OCIE2);
		break;
	}
}

// Deinitialize the selected Timer
void Timer_deInit(Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	case TIMER0_ID:
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;
		TIMSK &= ~(1<<TOIE0);
		TIMSK &= ~(1<<OCIE0);
		g_callBackPtr_timer0 = NULL_PTR;
		break;

	case TIMER1_ID:
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		OCR1A = 0;
		TIMSK &= ~(1<<TOIE1);
		TIMSK &= ~(1<<OCIE1A);
		g_callBackPtr_timer1 = NULL_PTR;
		break;

	case TIMER2_ID:
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		TIMSK &= ~(1<<TOIE2);
		TIMSK &= ~(1<<OCIE2);
		g_callBackPtr_timer2 = NULL_PTR;
		break;
	}
}

// Return the current timer counter value
uint16 Timer_getTimerValue(Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	case TIMER0_ID:
		return TCNT0;
	case TIMER1_ID:
		return TCNT1;
	case TIMER2_ID:
		return TCNT2;
	default:
		return 0;
	}
}

// Set the callback function for a specific timer
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	case TIMER0_ID:
		g_callBackPtr_timer0 = a_ptr;
		break;
	case TIMER1_ID:
		g_callBackPtr_timer1 = a_ptr;
		break;
	case TIMER2_ID:
		g_callBackPtr_timer2 = a_ptr;
		break;
	}
}
