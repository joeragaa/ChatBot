#ifndef CAN_H
#define CAN_H
#include "init.h"
/*
this file defines the declarations for the CAN coomunication 
between the two tivas 
*/
volatile bool errFlag=0; //error flag for any errors in the CAN bus
tCANMsgObject TXmsg; //message object for the sent message
tCANMsgObject RXmsg; //message object for the recieved message
//message data of maximum size 8 bytes (64 bits) as per CAn protocol
unsigned char TXmsg_Data[8]; 
unsigned char RXmsg_Data[8];

//rx flag raised by the CAN isr
volatile bool rxFlag=0;

void CANIntHandler(void);
void CAN_Init(void);
void CAN_Send(void);
void CAN_recieve(void);
void Partition(unsigned char Buffer[]);
void sendingDone(void);
void Error_Handling (void);

#endif
