/***************************************************************************************************************
 * File: Door_Locker_Security_System_Control_ECU.h
 * Description: Header file for the control ECU in the door locker security system.
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_CONTROL_ECU_H_
#define APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_CONTROL_ECU_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASSWORD_SIZE            5
#define I_AM_READY               0x01
#define WRONG_PASS               1U
#define CORRECT_PASS             0U

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/*
 * Receives two passwords and checks if they match.
 * If identical, saves the password to EEPROM.
 * Otherwise, repeats the process.
 */
void receive2Password(uint8 *a_ptr1, uint8 *a_ptr2);

/*
 * Receives password input and verifies it.
 * Triggers an alarm if the password is entered incorrectly 3 times.
 */
void checkPassAndAlarm(void);

/*
 * Generates a 15-second delay.
 */
void delay_15s(void);

#endif /* APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_CONTROL_ECU_H_ */
