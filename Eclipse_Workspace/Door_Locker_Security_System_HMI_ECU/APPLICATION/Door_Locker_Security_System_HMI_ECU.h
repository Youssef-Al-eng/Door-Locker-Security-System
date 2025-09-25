/***************************************************************************************************************
 * Door_Locker_Security_System_HMI_ECU.h
 * Author: Team TKH Embedded
 * Module: APPLICATION
 **************************************************************************************************************/

#ifndef APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_HMI_ECU_H_
#define APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_HMI_ECU_H_

#include "../Standard_Types/standard_types.h"

#define KEYPAD_DELAY			250
#define MESSAGE_DELAY			750
#define PASSWORD_SIZE			5
#define I_AM_READY				0x01

void takePassFromUser(uint8 * a_ptr);
void creatingPassword(void);
void checkPassAndAlarm(void);
void delay_15s(void);

#endif /* APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_HMI_ECU_H_ */
