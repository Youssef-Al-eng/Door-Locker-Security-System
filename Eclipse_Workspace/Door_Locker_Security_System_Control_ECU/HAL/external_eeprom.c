/***************************************************************************************************************
 * File: external_eeprom.c
 * Description: Source file for interfacing with external EEPROM via I2C (TWI).
 * Author: Youssef Alaa
 ***************************************************************************************************************/

#include "external_eeprom.h"
#include "../MCAL/twi.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Writes a byte to a specific address in the external EEPROM using I2C.
 * Returns SUCCESS or ERROR based on the communication result.
 */
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700) >> 7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    TWI_writeByte(u8data);
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    TWI_stop();
    return SUCCESS;
}

/*
 * Reads a byte from a specific address in the external EEPROM using I2C.
 * The result is stored in the pointer u8data.
 * Returns SUCCESS or ERROR based on the communication result.
 */
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700) >> 7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;

    TWI_writeByte((uint8)((0xA0 | ((u16addr & 0x0700) >> 7) | 1)));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    *u8data = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    TWI_stop();
    return SUCCESS;
}
