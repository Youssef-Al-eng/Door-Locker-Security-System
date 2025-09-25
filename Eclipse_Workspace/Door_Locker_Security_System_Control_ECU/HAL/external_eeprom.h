/***************************************************************************************************************
 * File: external_eeprom.h
 * Description: Header file for external EEPROM read/write operations using I2C (TWI).
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ERROR      0
#define SUCCESS    1

/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/

/*
 * Writes a byte to a specified address in the external EEPROM.
 * Returns SUCCESS (1) or ERROR (0).
 */
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);

/*
 * Reads a byte from a specified address in the external EEPROM.
 * The read value is stored in the pointer u8data.
 * Returns SUCCESS (1) or ERROR (0).
 */
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);

#endif /* EXTERNAL_EEPROM_H_ */
