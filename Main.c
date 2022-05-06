/*
the main body of the program contains the initilizations defined in
their respective header files and referenced in the init head file.
the program then enters an infinite loop which designates the idle state.
if a can interrupt or a uart interrupt triggers, their flags are raised and
the program enters these functions and the state dependant leds are
activated accordingly inside the bodies of each function.
///////////////////////////////////////
How to use:
Connect the two tivas with the USB cables and the CAN transceivers.
Open Putty and connect to the respective COM with baudrate 115200
press the left switch to start accepting data from the pc to the tiva (data collection state)
press enter or the right switch to send the data and enter data transmission state state
///////////////////////////////////////
Color Legend:
Blue for idle state
White for data collection state (PC to Tiva)
Green for data transmission state (Tiva to Tiva)
Red for data collection state (Tiva to Tiva)
Note: the Red and Green lights are not usually visible due to high speed transmission
but can be viewed if the provided delay period is increased.
*/
#include "init.h"

int main(void) {	
	initClock();
	initGPIO();
	CAN_Init();
	uart_init();
	for(;;){
		stateChange(BLUE);   
		UARTRecieve();
		CAN_recieve();
	}

}
