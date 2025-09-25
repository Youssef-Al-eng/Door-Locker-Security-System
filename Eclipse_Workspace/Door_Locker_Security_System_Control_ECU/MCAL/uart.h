/***************************************************************************************************************
 * uart.h
 * Author: Youssef Alaa
 * Module: UART
 **************************************************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
    UART_Parity_NONE, UART_Parity_EVEN = 2, UART_Parity_ODD = 3
} UART_Parity;

typedef enum
{
    UART_STOP_1_BIT, UART_STOP_2_BIT
} UART_StopBit;

typedef enum
{
    MODE_FIVE_BIT, MODE_SIX_BIT, MODE_SEVEN_BIT, MODE_EIGHT_BIT
} UART_BitDataType;

typedef struct
{
    uint32 baudRate;
    UART_Parity Parity_Configurations;
    UART_StopBit StopBit_Configurations;
    UART_BitDataType bit_data;
} UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

/*
 * Description :
 * Send the required array through UART to the other UART device.
 */
void UART_sendArray(const uint8 *a_ptr, uint8 size);

/*
 * Description :
 * Receive the required array until the '#' symbol through UART from the other UART device.
 */
void UART_receiveArray(uint8 *a_ptr);

#endif /* UART_H_ */
