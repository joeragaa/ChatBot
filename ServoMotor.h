#include "init.h"

void initServoMotor();
void closeGripper();
void openGripper();

void initServoMotor() {
	  volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 56;
    ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64); // SET PWM CLOCK BY: CLOCK_CPU
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); // ENABLES PWM
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // ENABLES PD
    ROM_GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6); // DEFINE PWM IN PIN PD0
    ROM_GPIOPinConfigure(GPIO_PB6_M0PWM0); // CONFIGS PD0 AS M1PWM0
    ui32PWMClock = SysCtlClockGet() / 64; // PUT IN A VARIABLE THE PWM's CLOCK
	// TRANSFORMS THE CLOCK WHO WANTS TO WORK IN A COUNTER THAT INITIALIZE AT 0 (THIS IS WHY "-1")
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1; 
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN); // CONFIGS THE COUNTER AS DESCENT
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, ui32Load); // SET THE COUNTER
	// SPLIT THE COUNTER BY 1000 AND MULTIPLIES BY THE ADJUST FOR PUT THE SERVO IN THE MIDDLE POSITION: 1.51ms (1/55HZ * ADJUST /1000)
    ROM_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000); 
	// CONFIGS THE PWM MODULE 1 AS OUT
    ROM_PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true); 
	// ENABLES THE PWM GENERATION
    ROM_PWMGenEnable(PWM0_BASE, PWM_GEN_0); 
}
void closeGripper(){
		volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 70;
		ui32PWMClock = SysCtlClockGet() / 64;
		ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1; 
		ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
}
void openGripper(){
		volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 56;
		ui32PWMClock = SysCtlClockGet() / 64; 
		ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1; 
		ROM_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);	
}