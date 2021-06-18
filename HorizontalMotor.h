#include "init.h"

void StartHorizontalMotor();
void stopHorStepper(void);
void stepRight(double mm);
void stepLeft(double mm);

void StartHorizontalMotor() {
    volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 83;
    ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_1); // SET PWM CLOCK BY: CLOCK_CPU
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // ENABLES PWM
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // ENABLES PF
    ROM_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3); // DEFINE PWM IN PIN PF3
    ROM_GPIOPinConfigure(GPIO_PF3_M1PWM7); // CONFIGS PF3 AS M1PWM7
    ui32PWMClock = SysCtlClockGet() / 64; // PUT IN A VARIABLE THE PWM's CLOCK
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1; 
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN); // CONFIGS THE COUNTER AS DESCENT
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load); // SET THE COUNTER
    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, ui8Adjust * ui32Load / 1000); 
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true); // CONFIGS THE PWM MODULE 1 AS OUT
    ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_3); // ENABLES THE PWM GENERATION
}
void stopHorStepper(void) {	
	ROM_PWMGenDisable(PWM1_BASE, PWM_GEN_3);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0);
}
void stepRight(double mm) {
	int n;
	double rev;
	rev=mm/(PWM_FREQUENCY*1.3);
	rev=rev*1200;
	GPIOPinWrite(GPIO_Direction,HorDIR,~HorDIR);
	for (n=0; n<rev; n++) {
		ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_3);
		SysCtlDelay(10000);
	}
	stopHorStepper();
}
void stepLeft(double mm) {	
	int n;
	double rev;
	rev=mm/(PWM_FREQUENCY*1.3);
	rev=rev*1200;
	GPIOPinWrite(GPIO_Direction,HorDIR,HorDIR);
	for (n=0; n<rev; n++) {
		ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_3);
		SysCtlDelay(10000);
	}
	stopHorStepper();
}