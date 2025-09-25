/***************************************************************************************************************
 * File: motor.c
 * Description: Source file for DC motor control using GPIO and PWM.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#include "motor.h"
#include "../MCAL/gpio.h"
#include "../MCAL/pwm.h"

/*******************************************************************************
 *                             Function Definitions                             *
 *******************************************************************************/

/*
 * Initializes the motor control pins and stops the motor.
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(MOTOR_PORT_CONNECTION, PIN_INT1, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_CONNECTION, PIN_INT2, PIN_OUTPUT);
	GPIO_setupPinDirection(ENABLE_PORT_CONNECTION, ENABLE_PIN, PIN_OUTPUT);

	GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT1, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT2, LOGIC_LOW);
}

/*
 * Rotates the motor in the specified direction (CW/CCW/STOP)
 * and sets speed using PWM on the enable pin.
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	PWM_Timer0_Start(speed);

	switch (state)
	{
	case STOP:
		GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT1, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT2, LOGIC_LOW);
		break;

	case CW:
		GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT1, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT2, LOGIC_LOW);
		break;

	case CCW:
		GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT1, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_CONNECTION, PIN_INT2, LOGIC_HIGH);
		break;
	}
}
