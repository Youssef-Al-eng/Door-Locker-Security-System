/***************************************************************************************************************
 * uart.h
 * Author: Youssef Alaa
 * Description: Header file for UART driver for AVR microcontrollers.
 *              Provides function declarations and configuration structures for UART initialization and communication.
 ***************************************************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../Standard_Types/standard_types.h"

// Parity bit configuration
typedef enum
{
    UART_Parity_NONE,
    UART_Parity_EVEN = 2,
    UART_Parity_ODD = 3
} UART_Parity;

// Stop bit configuration
typedef enum
{
    UART_STOP_1_BIT,
    UART_STOP_2_BIT
} UART_StopBit;

// Number of data bits in frame
typedef enum
{
    MODE_FIVE_BIT,
    MODE_SIX_BIT,
    MODE_SEVEN_BIT,
    MODE_EIGHT_BIT
} UART_BitDataType;

// UART configuration structure
typedef struct
{
    uint32 baudRate;
    UART_Parity Parity_Configurations;
    UART_StopBit StopBit_Configurations;
    UART_BitDataType bit_data;
} UART_ConfigType;

// Initialize UART with the given configuration
void UART_init(const UART_ConfigType * Config_Ptr);

// Send a single byte via UART
void UART_sendByte(const uint8 data);

// Receive a single byte via UART
uint8 UART_receiveByte(void);

// Send a null-terminated string via UART
void UART_sendString(const uint8 *Str);

// Receive a string until '#' character is received
void UART_receiveString(uint8 *Str);

// Send an array of bytes via UART
void UART_sendArray(const uint8 *a_ptr, uint8 size);

// Receive an array of bytes until '#' character is received
void UART_receiveArray(uint8 *a_ptr);

#endif /* UART_H_ */
