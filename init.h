#ifndef INT_H
#define INT_H

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "math.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "utils/uartstdio.h"
#include "driverlib/systick.h"

#define caesar_key 3
#define GPIO_LED  GPIO_PORTF_BASE
#define RED  GPIO_PIN_1
#define BLUE  GPIO_PIN_2
#define GREEN  GPIO_PIN_3
#define WHITE  RED | BLUE | GREEN 

#define SW1 0x01
#define SW2 0x10

//the ids for the sending and receiving message objects
#define CAN0RXID                2
#define RXOBJECT                2
#define CAN0TXID                0
#define TXOBJECT                1

#define MAX_NUM_UART_DATA    		200

extern volatile bool errFlag ; 
extern tCANMsgObject RXmsg; 
extern unsigned char RXmsg_Data[8];

extern tCANMsgObject TXmsg; 
extern unsigned char TXmsg_Data[8];


extern volatile bool rxFlag;
extern volatile bool uartFlag;
extern volatile bool LeftSwitchFlag;
extern volatile bool RightSwitchFlag;

extern void initClock(void);
extern void initGPIO(void);
extern void stateChange(uint32_t Color);
extern void SimpleDelay(void);
extern void SysTickIntHandler(void);
extern uint32_t SW_Input(void);
extern void uart_init(void);
extern void UARTClear(unsigned char buff[]);
extern void UARTSend(uint32_t ui32UARTBase, const uint8_t *pui8Buffer, uint32_t ui32Count);
extern void UART0IntHandler(void);
extern void UARTRecieve(void);
extern void CANIntHandler(void);
extern void CAN_Init(void);
extern void CAN_Send(void);
extern void CAN_recieve(void);
extern void Partition(unsigned char Buffer[]);
extern void sendingDone(void);
extern void encrypt_caesar(char* plainText, int key);
extern void decrypt_caesar(char* cipherText,int key);
extern void decrypt_vigenere(char* cipherText, char* key);
extern void encrypt_vigenere(char* plainText, char* key);
extern void vigenere_key(char* plainText, char* key, char* cyclic_key);
#endif
