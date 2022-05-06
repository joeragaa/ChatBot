#ifndef UART_H
#define UART_H
#include "init.h"
/*
this file defines the declarations for the uart communication
between each tiva and the PC.
the uartFlag is raised by the uart isr and allows the uartRecieve 
function to take place.
*/
volatile bool uartFlag=0;

void uart_init(void);
void UARTClear(unsigned char buff[]);
void UARTSend(uint32_t ui32UARTBase, const uint8_t *pui8Buffer, uint32_t ui32Count);
void UART0IntHandler(void);
void UARTRecieve(void);

#endif
