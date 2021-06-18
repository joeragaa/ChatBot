#include "GPIO_Init.h"
#include "Sorting.h"

//Main routine
int main(void) {
	GPIO_Init();
	IntMasterEnable();
	returnToHome();
	while(1){
		StoringDecision();
		}
}

//Interrupt service routine
void VerLimit(void){
	GPIOIntClear(GPIO_PORTB_BASE, PINS);	
	GPIOIntDisable(GPIO_PORTB_BASE, PINS);
	SysCtlDelay(1000000);
	stopVerStepper();
	verticalLimit=1;
	GPIOIntEnable(GPIO_PORTB_BASE, PINS);
}
//Interrupt service routine
void HorLimit(void){
	GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_7);
	GPIOIntDisable(GPIO_PORTA_BASE, GPIO_PIN_7);
	SysCtlDelay(1000000);
	stopHorStepper();
	horizontalLimit=1;
	GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_7);
}
//Interrupt service routine
void TopIR(void){
	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_1);	
	GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_1);
	SysCtlDelay(1000000);
	upperIR=1;
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_1);
}
//Interrupt service routine
void BottomIR(void){
	GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_1);
	GPIOIntDisable(GPIO_PORTD_BASE, GPIO_PIN_1);
	SysCtlDelay(1000000);
	lowerIR=1;
	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_1);
}
void TallPartDone(void){
	  uint32_t status=0;
		status = TimerIntStatus(TIMER5_BASE,true);
		TimerIntClear(TIMER5_BASE,status);
		TimerDisable(TIMER5_BASE, TIMER_A);
		TallDone=1;
}
void ShortPartDone(void){
	  uint32_t status=0;
		status = TimerIntStatus(TIMER1_BASE,true);
		TimerIntClear(TIMER1_BASE,status);
		TimerDisable(TIMER1_BASE, TIMER_A);
		ShortDone=1;
}