#include "GPIO.h"

//initialize the board clock
void initClock(void){
	SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
}

//GPIO initialization and interrupt enabling
void initGPIO(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
		GPIOPinTypeGPIOOutput(GPIO_LED, WHITE);
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R = 0x1F;
		GPIO_PORTF_DIR_R = 0x0E;
		GPIO_PORTF_PUR_R = 0x11;
		GPIO_PORTF_DEN_R = 0x1F;

	  IntMasterEnable();
		SysTickPeriodSet(SysCtlClockGet()/20);
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

void SimpleDelay(void){
    SysCtlDelay(16000000 / 600);
}

//return the input switch reading from the portF data register
uint32_t SW_Input(void){
   return (GPIO_PORTF_DATA_R&0x11);
}

//systick isr taking the input of the on board switches and rasing their respective flags
void SysTickIntHandler(void){
	  switch(SW_Input()){
        case SW1:
                LeftSwitchFlag=true;
								//stateChange(WHITE);
                break;    
        case SW2:
                RightSwitchFlag=true;
                break;     
		}
}

//light a certain LED color
void stateChange(uint32_t Color){
	  GPIOPinWrite(GPIO_LED, RED, ~RED);
    GPIOPinWrite(GPIO_LED, BLUE, ~BLUE);
    GPIOPinWrite(GPIO_LED, GREEN, ~GREEN);
    GPIOPinWrite(GPIO_LED, Color, Color);
}
