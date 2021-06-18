#ifndef INIT_H
#define INIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "math.h"
#include "tm4c123gh6pm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "driverlib/can.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#define GPIO_Direction  GPIO_PORTE_BASE
#define PINS GPIO_PIN_0 
#define VerDIR  GPIO_PIN_0  
#define HorDIR  GPIO_PIN_1
#define DIR   HorDIR | VerDIR
#define TIR	GPIO_PIN_1 //port F
#define BIR	GPIO_PIN_7	//port D
#define PWM_FREQUENCY  100
#define DownwardAss  105
#define DownwardDis 80
#define DownwardStor 100
#define LeftwardAss 520
#define ShortHor 300
#define TallHor 180
#define TallReturn  340

volatile uint8_t upperIR=0;
volatile uint8_t lowerIR=0;
volatile uint8_t verticalLimit=0;
volatile uint8_t horizontalLimit=0;
volatile int TallDone=0;
volatile int ShortDone=0;

void VerLimit(void);
void HorLimit(void);
void TopIR(void);
void BottomIR(void);
void TallPartDone(void);
void ShortPartDone(void);

#endif