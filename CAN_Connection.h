#include "init.h"

// transmission error flag
volatile bool errFlag = 0; 
// the CAN message object
tCANMsgObject msg; 
// the message data is four bytes long which we can allocate as an int32
unsigned int msgData;
// make a pointer to msgData so we can access individual bytes
unsigned char *msgDataPtr = (unsigned char *)&msgData; 

void CANIntHandler(void);
void canConnection(void);

// CAN interrupt handler
void CANIntHandler(void) {
	unsigned long status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); // read interrupt status
	// controller status interrupt
	if(status == CAN_INT_INTID_STATUS) { 
		status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
		errFlag = 1;
	} else if(status == 1) { // message object 1
		CANIntClear(CAN0_BASE, 1); // clear interrupt
		errFlag = 0; // clear any error flags
	} 
}
void CAN_Init(void){
	// Set up CAN0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // enable CAN0 GPIO peripheral
	GPIOPinConfigure(GPIO_PB4_CAN0RX);
	GPIOPinConfigure(GPIO_PB5_CAN0TX);
	GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	CANInit(CAN0_BASE);
	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
	CANIntRegister(CAN0_BASE, CANIntHandler);
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	IntEnable(INT_CAN0);
	CANEnable(CAN0_BASE);
}
void CAN_Send(){
	// Set up msg object
	msgData = 0;
	msg.ui32MsgID = 1;
	msg.ui32MsgIDMask = 0;
	msg.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
	msg.ui32MsgLen = sizeof(msgDataPtr);
	msg.pui8MsgData = msgDataPtr;
	// send as msg object 1
	CANMessageSet(CAN0_BASE, 1, &msg, MSG_OBJ_TYPE_TX); 
}
void startAssemblyConveyer(void){
		msgDataPtr[0]=1;
		CAN_Send();
}
void stopAssemblyConveyer(void){
		msgDataPtr[0]=0;
		CAN_Send();
}
void startDisassemblyConveyer(void){
		msgDataPtr[2]=1;
		CAN_Send();
}
void stopDisssemblyConveyer(void){
		msgDataPtr[2]=0;
		CAN_Send();
}