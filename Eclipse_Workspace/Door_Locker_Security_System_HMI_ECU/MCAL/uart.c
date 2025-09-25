/***************************************************************************************************************
 * uart.c
 * Author: Youssef Alaa
 * Description: Source file for UART driver for AVR microcontrollers (supports send/receive of bytes, strings, arrays).
 ***************************************************************************************************************/

#include "uart.h"
#include <avr/io.h>
#include "../Common_Macros/common_macros.h"

// Initialize UART peripheral with user-defined settings
void UART_init(const UART_ConfigType * Config_Ptr)
{
    uint16 ubrr_value = 0;

    // Enable double speed mode
    UCSRA = (1 << U2X);

    // Enable transmitter and receiver, 8-bit data mode (UCSZ2 = 0)
    UCSRB = (1 << RXEN) | (1 << TXEN);

    // Set frame format: data bits, parity, stop bits
    UCSRC = (1 << URSEL)
           | ((Config_Ptr->bit_data) << UCSZ0)
           | ((Config_Ptr->Parity_Configurations) << UPM0)
           | ((Config_Ptr->StopBit_Configurations) << USBS);

    // Calculate and set baud rate
    ubrr_value = (uint16)((F_CPU / (Config_Ptr->baudRate * 8UL)) - 1);
    UBRRH = ubrr_value >> 8;
    UBRRL = ubrr_value;
}

// Send one byte via UART
void UART_sendByte(const uint8 data)
{
    while (BIT_IS_CLEAR(UCSRA, UDRE)) {}
    UDR = data;
}

// Receive one byte via UART
uint8 UART_receiveByte(void)
{
    while (BIT_IS_CLEAR(UCSRA, RXC)) {}
    return UDR;
}

// Send a null-terminated string via UART
void UART_sendString(const uint8 *Str)
{
    uint8 i = 0;
    while (Str[i] != '\0')
    {
        UART_sendByte(Str[i]);
        i++;
    }
}

// Receive a string until '#' is received
void UART_receiveString(uint8 *Str)
{
    uint8 i = 0;
    Str[i] = UART_receiveByte();
    while (Str[i] != '#')
    {
        i++;
        Str[i] = UART_receiveByte();
    }
    Str[i] = '\0';
}

// Send an array of known size and terminate with '#'
void UART_sendArray(const uint8 *a_ptr, uint8 size)
{
    for (uint8 i = 0; i < size; i++)
    {
        UART_sendByte(a_ptr[i]);
    }
    UART_sendByte('#');
}

// Receive an array until '#' is detected
void UART_receiveArray(uint8 *a_ptr)
{
    uint8 i = 0;
    a_ptr[i] = UART_receiveByte();
    while (a_ptr[i] != '#')
    {
        i++;
        a_ptr[i] = UART_receiveByte();
    }
}
