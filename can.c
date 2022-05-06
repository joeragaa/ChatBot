#include "can.h"

// CAN interrupt handler
void CANIntHandler(void) {
	// read interrupt status
	unsigned long status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); 
	// controller status interrupt
	if(status == CAN_INT_INTID_STATUS) { 
		status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
		errFlag = 1;
	} 
	// msg object 1
	else if(status == RXOBJECT) { 
		// clear interrupt
		CANIntClear(CAN0_BASE, RXOBJECT);
		// set rx flag
		rxFlag = 1; 
		// clear any error flags	
		errFlag = 0; 
	}

	else if(status == TXOBJECT) { 
		// clear interrupt
		CANIntClear(CAN0_BASE, TXOBJECT);
		// clear any error flags	
		errFlag = 0; 
	}
}

void CAN_Init(void){
		// Set up CAN0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinConfigure(GPIO_PB4_CAN0RX);
	GPIOPinConfigure(GPIO_PB5_CAN0TX);
	GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	CANInit(CAN0_BASE);
	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
	CANIntRegister(CAN0_BASE, CANIntHandler); 
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS );
	IntEnable(INT_CAN0);
	CANEnable(CAN0_BASE);
	RXmsg.ui32MsgID = CAN0RXID;
	RXmsg.ui32MsgIDMask = 0;
	RXmsg.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	RXmsg.ui32MsgLen = 8; // allow up to 8 bytes
	// Load msg into CAN peripheral message object 1 
	//so it can trigger interrupts on any matched rx messages
	CANMessageSet(CAN0_BASE, RXOBJECT, &RXmsg, MSG_OBJ_TYPE_RX);
	
	TXmsg.ui32MsgID = CAN0TXID;
	TXmsg.ui32MsgIDMask = 0;
	TXmsg.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
	TXmsg.ui32MsgLen = sizeof(TXmsg_Data);
}

//encrypt the message, set the message object
//to the encrypted data andn send iver the can bus
void CAN_Send(void){
	
	// Set up msg object
	encrypt_caesar((char *)TXmsg_Data, caesar_key);
	TXmsg.pui8MsgData = (uint8_t*)&TXmsg_Data;
	Error_Handling();
	// send as msg object 1
	CANMessageSet(CAN0_BASE, TXOBJECT, &TXmsg, MSG_OBJ_TYPE_TX); 
}

//partition the buffer string into 8 byte parts and send 
//incrementally over the can bus
void Partition(unsigned char Buffer[])
{
	stateChange(GREEN);
	int count = 0;
	for(count = 0 ; count < MAX_NUM_UART_DATA ; count++){
		//send data every 8 characters
		if( count%8==0 && count!=0 ){
			CAN_Send();
			SimpleDelay(); //delay to account for the time taken for data to transfer over the CAN bus
			UARTClear(TXmsg_Data);
		}
		TXmsg_Data[count%8] = Buffer[count];
		
		//if enter or tab are pressed before 8 characters send the current buffer
		if(TXmsg_Data[count%8] == '\n' || TXmsg_Data[count%8] == '\r'){
			CAN_Send();
			SimpleDelay();
			UARTClear(TXmsg_Data);
			break;
		}
	}
	TXmsg_Data[0]='\n';
	CAN_Send();
}

//if the can flag is raised receive the message
//decrypt the message and display it on pc over uart
void CAN_recieve(void){
			if(rxFlag){ 
				stateChange(RED);
				 // set pointer to rx buffer
				RXmsg.pui8MsgData = RXmsg_Data ; 
				// read CAN message object 1 from CAN peripheral
				CANMessageGet(CAN0_BASE, RXOBJECT, &RXmsg, 0); 
				// clear rx flag
				decrypt_caesar((char *)RXmsg_Data,caesar_key);
				Error_Handling();
				UARTSend(UART0_BASE, (uint8_t *)RXmsg_Data, strlen((char *)RXmsg_Data));
				rxFlag = 0; 
				}
}

void sendingDone(void){
	unsigned long status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
	while(status != CAN_STS_TXOK);
}


void Error_Handling (void)
{
	if (errFlag == 1)
	{
		UARTSend(UART0_BASE, (uint8_t *)"Error - Check the Cable", strlen("Error - Check the Cable"));
	}
}
