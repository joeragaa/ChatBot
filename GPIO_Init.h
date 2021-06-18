#include "init.h"

void initClock(void);
void initGPIOA(void);
void initGPIOB(void);
void initGPIOD(void);
void initGPIOE(void);
void initGPIOF(void);

//Clock initialization
void initClock(void){
	SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
}
void initGPIOA(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_7);
	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_7);
	GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_LOW_LEVEL);
	IntPrioritySet(INT_GPIOA, 0);
	IntRegister(INT_GPIOA, HorLimit);
	IntEnable(INT_GPIOA);
}
void initGPIOB(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_0);
	GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_LOW_LEVEL);
	IntPrioritySet(INT_GPIOB, 0);
	IntRegister(INT_GPIOB, VerLimit);
	IntEnable(INT_GPIOB);
}
void initGPIOD(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1);
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_1);
	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_LOW_LEVEL);
	IntPrioritySet(INT_GPIOD, 1);
	IntRegister(INT_GPIOD, BottomIR);
	IntEnable(INT_GPIOD);
}
void initGPIOE(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOOutput(GPIO_Direction, DIR);
}
void initGPIOF(void){	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_1);
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_LOW_LEVEL);
	IntPrioritySet(INT_GPIOF, 1);
	IntRegister(INT_GPIOF, TopIR);
	IntEnable(INT_GPIOF);
}
//GPIO initialization and interrupt enabling
void GPIO_Init(void){
	initClock();
	initGPIOA();
	initGPIOB();
	initGPIOD();
	initGPIOE();
	initGPIOF();
}