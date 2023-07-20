// SoftwarePWM.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a software PWM: this PWM signal can be used 
// to control the brightness of an LED or to drive and change the speed of a DC motor
// The onboard puch button SW1 increases the delivered power, and SW2 decreases the delivered power.
// The original design comes from DCMotor written by Daniel Valvano, Jonathan Valvano, August 6, 2013
// Modified by Min He on 08/14/2020: removed PLL, modified some code and migrate to keil5.
// Further modified for CECS 347 Lab 1 by:
//   Rodrigo Becerril Ferreyra
//   Student ID 017584071
//   California State University, Long Beach
//   22 January 2021

#include "tm4c123gh6pm.h"

// Constants
#define PERIOD 	    160000  // number of machine cycles for 10ms, value is based on 16MH system clock
#define MIN_DUTY    16000	// minimum duty cycle 10%
#define MAX_DUTY    144000	// maximum duty cycle 90%
#define HALF_DUTY   80000	// 50% duty cycle
#define DUTY_STEP	16000	// duty cycle change for each button press

// Function prototypes
// External functions for interrupt control defined in startup.s
extern void DisableInterrupts(void); // Disable interrupts
extern void EnableInterrupts(void);  // Enable interrupts
extern void WaitForInterrupt(void);  // low power mode

// This function initializes SysTick timer.
void sysTick_Init(void);

// This function initilizes port F and arm PF4, PF0 for falling edge interrupts
// while also setting PF2 as an output
void portF_Init(void);

// Global variables: 
// H: number of clocks cycles for duty cycle
// L: number of clock cycles for non-duty cycle
unsigned long H,L;

int main(void){
  DisableInterrupts();  // disable interrupts to allow initializations
  sysTick_Init();    // output from F[2], SysTick interrupts
  portF_Init();        // arm PF4, PF0 for falling edge interrupts
  EnableInterrupts();   // enable after initializations are done
  while(1){
    // main program is free to perform other tasks
    WaitForInterrupt(); // low power mode
  }
}

// Initializes SysTick (with inturrupt)
void sysTick_Init(void)
{
    NVIC_ST_CTRL_R = 0;                     // disable SysTick during setup
    NVIC_ST_RELOAD_R = L-1;                 // reload value for 50% duty cycle
    NVIC_ST_CURRENT_R = 0;                  // any write to current clears it
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x1FFFFFFF)|0x40000000; // bit 31-29 for SysTick, set priority to 2
    NVIC_ST_CTRL_R |= 0x00000007;           // enable with core clock and interrupts, start systick timer
}

// Initializes Port F
// F[0] and F[4] are set as inputs that trigger an interrupt
// F[2] is an output
void portF_Init(void)
{
    SYSCTL_RCGC2_R |= 0x20;                 // start clock for Port F
    while((SYSCTL_RCGC2_R & 0x20) != 0x20); // wait for clock to start
    
    // data initialization
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock Port F
    GPIO_PORTF_CR_R |= 0x15;        // unlock CR for F[4], F[2], and F[0]
    GPIO_PORTF_DIR_R |= 0x04;       // F[2] is an output
    GPIO_PORTF_DIR_R &= ~0x11;      // F[4] and F[0] are inputs
    GPIO_PORTF_PUR_R |= 0x11;       // F[4] | F[0]
    GPIO_PORTF_DEN_R |= 0x15;       // enable F[4], F[2], and F[0]
    
    // interrupt initialization
    GPIO_PORTF_IM_R &= ~0x11;     // mask PF4, PF0
    GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4,PF0 is edge-sensitive
    GPIO_PORTF_IBE_R &= ~0x11;    //     PF4,PF0 is not both edges
    GPIO_PORTF_IEV_R &= ~0x11;    //     PF4,PF0 falling edge event
    GPIO_PORTF_ICR_R = 0x11;      // (e) clear flags 4,0
    GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4,PF0
    NVIC_PRI7_R = (NVIC_PRI7_R&0xFF1FFFFF)|0x00400000; // (g) bits:23-21 for PORTF, set priority to 2
    NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
}

// SysTick ISR:
// 1. Implement timing control for duty cycle and non-duty cycle
// 2. Output a waveform based on current duty cycle
void SysTick_Handler(void){
	NVIC_ST_CTRL_R &= ~0x00000001;// turn off SysTick to reset reload value
  if(GPIO_PORTF_DATA_R&0x04){   // if F[2] is high
    GPIO_PORTF_DATA_R &= ~0x04; // make F[2] low
    NVIC_ST_RELOAD_R = L-1;     // reload value for low phase
  } else{
    GPIO_PORTF_DATA_R |= 0x04;  // make F[2] high
    NVIC_ST_RELOAD_R = H-1;     // reload value for high phase
  }
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R |= 0x00000001; // turn on systick to continue
}

// PORTF ISR:
// Change delivered power based on switch press: 
// sw1: increase 10% until reach 90%
// sw2: decrease 10% until reach 10%
void GPIOPortF_Handler(void){ // called on touch of either SW1 or SW2
  if(GPIO_PORTF_RIS_R&0x01){  // SW2 touched 
    GPIO_PORTF_ICR_R = 0x01;  // acknowledge flag0
    if(H>MIN_DUTY) H = H-DUTY_STEP;    // reduce delivered power
  }
  if(GPIO_PORTF_RIS_R&0x10){  // SW1 touch
    GPIO_PORTF_ICR_R = 0x10;  // acknowledge flag4
    if(H<MAX_DUTY) H = H+DUTY_STEP;   // increase delivered power
  }
  L = PERIOD-H; // constant period of 10ms, variable duty cycle
}
