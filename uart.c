#include "uart.h"

void uart_init(){
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		IntMasterEnable();
    // Set GPIO A0 and A1 as UART pins.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
    // Configure the UART for 115,200, 8-N-1 operation.
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
		IntEnable(INT_UART0);
		UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
		UARTIntRegister(UART0_BASE,UART0IntHandler);
		IntPrioritySet(INT_UART0,1);
}

//clear the argument array of all garbage data
void UARTClear(unsigned char buff[]){
		int count = 0;
		for(count = 0 ; count < MAX_NUM_UART_DATA ; count++){
        buff[count] = NULL;
    }
}

//send data buffer over uart base given
//count number of bytes
void UARTSend(uint32_t ui32UARTBase, const uint8_t *pui8Buffer, uint32_t ui32Count){
    
    while(ui32Count--){  // Loop while there are more characters to send.
        UARTCharPut(ui32UARTBase, *pui8Buffer++);
    }
}

//if the uartflag and left button are raised the function enters
//load all the data sent over uart into the buffer variable
//then pass the buffer to the partitioning function to send 
//overr the CAN bus
void UARTRecieve(void){
    if(uartFlag&&LeftSwitchFlag){
			stateChange(WHITE);
			unsigned char buffer[MAX_NUM_UART_DATA];
			int count = 0;
			UARTClear(buffer);
			UARTSend(UART0_BASE, (uint8_t *)"me: ", strlen("me: "));
			strcpy((char *)TXmsg_Data, "other: ");
			CAN_Send();
			while(count<MAX_NUM_UART_DATA)
			{
				if(UARTCharsAvail(UART0_BASE))
				{
					buffer[count] = UARTCharGet(UART0_BASE);
					UARTCharPut(UART0_BASE, buffer[count]);
					//break out of the loop if enter or tab is pressed
					if( (buffer[count] == '\n') || (buffer[count] == '\r') )
						break;
					count++;
				}
				//break out if the right button is pressed
				if(RightSwitchFlag)
						break;
			}
			UARTSend(UART0_BASE, (uint8_t *)"\n\r", strlen("\n\r"));
			Partition(buffer);
			uartFlag = false;
			RightSwitchFlag=false;
			LeftSwitchFlag=false;
    }
}
//uart isr
void UART0IntHandler(void){
    uint32_t ui32Status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32Status);
		uartFlag = true;
}

