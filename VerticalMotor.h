#include "init.h"

void StartVerticalMotor();
void stopVerStepper(void);
void stepUp(double mm);
void stepDown(double mm);

void StartVerticalMotor() {
    volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 83;
    ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_1); // SET PWM CLOCK BY: CLOCK_CPU
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // ENABLES PWM
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); // ENABLES PD
    ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0); // DEFINE PWM IN PIN PD0
    ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0); // CONFIGS PD0 AS M1PWM0
    ui32PWMClock = SysCtlClockGet() / 64; // PUT IN A VARIABLE THE PWM's CLOCK
	// TRANSFORMS THE CLOCK WHO WANTS TO WORK IN A COUNTER THAT INITIALIZE AT 0 (THIS IS WHY "-1")
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1; 
    PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN); // CONFIGS THE COUNTER AS DESCENT
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load); // SET THE COUNTER
    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true); // CONFIGS THE PWM MODULE 1 AS OUT
    ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0); // ENABLES THE PWM GENERATION
}
void stopVerStepper(void) {
	ROM_PWMGenDisable(PWM1_BASE, PWM_GEN_0);
	GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0,0);
}
void stepUp(double mm) {
	int n;
	double rev;
	rev=mm/14.4;
	rev=rev*1200;
	GPIOPinWrite(GPIO_Direction,VerDIR,~VerDIR);
	for (n=0; n<rev; n++) {
		ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);
		SysCtlDelay(10000);
	}
	stopVerStepper();
}
void stepDown(double mm) {
	int n;
	double rev;
	rev=mm/14.4;
	rev=rev*1200;
	GPIOPinWrite(GPIO_Direction,VerDIR,VerDIR);
	for (n=0; n<rev; n++) {
		ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);
		SysCtlDelay(10000);
	}
	stopVerStepper();
}