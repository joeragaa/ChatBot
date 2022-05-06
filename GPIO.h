#ifndef GPIO_H
#define GPIO_H
#include "init.h"
/*
this file defines the declarations for the initilization function for GPIO and 
systick handler. the systick timer is used to periodically check on the button
input from the user and flags are raised accordingly.

*/
volatile bool LeftSwitchFlag=0;
volatile bool RightSwitchFlag=0;

void initClock(void);
void initGPIO(void);
void stateChange(uint32_t Color);
void SimpleDelay(void);
void SysTickIntHandler(void);
uint32_t SW_Input(void);

#endif
