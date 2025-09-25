/***************************************************************************************************************
 * File: motor.h
 * Description: Header file for controlling a DC motor with direction and speed control.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/

#define MOTOR_STOP               (0)
#define MOTOR_MINIMUM_SPEED      (25)
#define MOTOR_SECOND_SPEED       (50)
#define MOTOR_THIRD_SPEED        (75)
#define MOTOR_MAX_SPEED          (100)

#define MOTOR_PORT_CONNECTION    PORTD_ID
#define PIN_INT1                 PIN6_ID
#define PIN_INT2                 PIN7_ID
#define ENABLE_PORT_CONNECTION   PORTB_ID
#define ENABLE_PIN               PIN3_ID

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

typedef enum {
	STOP,
	CW,
	CCW
} DcMotor_State;

/*******************************************************************************
 *                             Function Prototypes                             *
 *******************************************************************************/

/*
 * Initializes the DC motor control pins and sets initial state to STOP.
 */
void DcMotor_Init(void);

/*
 * Rotates the DC motor in the specified direction and speed using PWM.
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* HAL_MOTOR_H_ */
