#include "init.h"
#include "CAN_Connection.h"
#include "ServoMotor.h"
#include "VerticalMotor.h"
#include "HorizontalMotor.h"

void storing(void);
void storingTall(void);
void storingShort(void);
void StoringDecision(void);
void PartTimeUp();
void Timer2Begin(int time);
void TimerBegin(int time);
void startTallTimer(void);
void startShortTimer(void);
void returnToHome(void);

void returnToHome(void){
	StartVerticalMotor();
	SysCtlDelay(10000000);
	StartHorizontalMotor();	
	initServoMotor();
}
void storing(void){
	stepLeft(LeftwardAss);
	openGripper();
	SysCtlDelay(10000000);
	stepDown(DownwardAss);
	SysCtlDelay(10000000);  
	startAssemblyConveyer();
	closeGripper();
	SysCtlDelay(10000000);
	stepUp(DownwardAss);
	SysCtlDelay(10000000);
}
void storingTall(void){
	storing();
	stepRight(TallHor);
	SysCtlDelay(10000000);
	stepDown(DownwardStor);
	SysCtlDelay(10000000);
	openGripper();
	SysCtlDelay(10000000);
	startTallTimer();
	stepUp(DownwardStor);
	stepRight(TallReturn);
}
void storingShort(void){
	storing();
	stepRight(ShortHor);
	SysCtlDelay(10000000);
	stepDown(DownwardStor);
	SysCtlDelay(10000000);
	openGripper();
	SysCtlDelay(10000000);
	startShortTimer();
	stepUp(DownwardStor);
	SysCtlDelay(10000000);
	stepRight(220);
}

void StoringDecision(void){
	if(upperIR==1 && lowerIR==1){
		//inform disassembly of the height of the part that is to be delivered
		msgDataPtr[1] = 4;
		stopAssemblyConveyer();
		upperIR=0;
		lowerIR=0;
		storingTall();
	}
	else if( lowerIR==1){
		msgDataPtr[1] = 8;
		stopAssemblyConveyer();
		lowerIR=0;
		storingShort();		
	}
	PartTimeUp();
}
void PartTimeUp(){
	if(ShortDone==1){
		stepLeft(220);
		SysCtlDelay(10000000);
		stepDown(DownwardStor);
		SysCtlDelay(10000000);
		closeGripper();
		SysCtlDelay(10000000);
		stepUp(DownwardStor);
		SysCtlDelay(10000000);
		stepRight(190);
		SysCtlDelay(10000000);
		stopDisssemblyConveyer();
		SysCtlDelay(10000000);
		stepDown(DownwardDis);
		SysCtlDelay(10000000);
		openGripper();
		SysCtlDelay(10000000);
		startDisassemblyConveyer();
		SysCtlDelay(10000000);
		stepUp(DownwardDis);
		stepRight(30);
		ShortDone=0;
	}
	else if(TallDone==1){
		stepLeft(TallReturn);
		SysCtlDelay(10000000);
		stepDown(DownwardStor);
		SysCtlDelay(10000000);
		closeGripper();
		SysCtlDelay(10000000);
		stepUp(DownwardStor);
		SysCtlDelay(10000000);
		stepRight(310);
		SysCtlDelay(10000000);
		stopDisssemblyConveyer();
		SysCtlDelay(10000000);
		stepDown(DownwardDis);
		SysCtlDelay(10000000);
		openGripper();
		SysCtlDelay(10000000);
		startDisassemblyConveyer();
		SysCtlDelay(10000000);
		stepUp(DownwardDis);
		stepRight(30);
		TallDone=0;
	}
}
void Timer2Begin(int time){ 
  uint32_t Period;
	time=time*1000;
  Period = 40000 *time; 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  SysCtlDelay(3);
  TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER1_BASE, TIMER_A, Period -1);
  TimerIntRegister(TIMER1_BASE, TIMER_A, ShortPartDone); 
  TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);  
  TimerEnable(TIMER1_BASE, TIMER_A);
}
void TimerBegin(int time){
  uint32_t Period;
	time=time*1000;
  Period = 40000 *time; //1ms
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);
  SysCtlDelay(3);
  TimerConfigure(TIMER5_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER5_BASE, TIMER_A, Period -1);  
  TimerIntRegister(TIMER5_BASE, TIMER_A, TallPartDone); 
  TimerIntEnable(TIMER5_BASE, TIMER_TIMA_TIMEOUT);  
  TimerEnable(TIMER5_BASE, TIMER_A);
}
void startTallTimer(){
	TimerBegin(30);
}
void startShortTimer(){
	Timer2Begin(30);
}