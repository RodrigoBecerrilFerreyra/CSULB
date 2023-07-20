// StepperTestMain.c
// Runs on LM4F120/TM4C123
// Test the functions provided by Stepper.c,
// 
// Before connecting a real stepper motor, remember to put the
// proper amount of delay between each CW() or CCW() step.
// Daniel Valvano
// September 12, 2013
// Modified by Min HE

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   Example 4.1, Programs 4.4, 4.5, and 4.6
   Hardware circuit diagram Figure 4.27

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// PD3 connected to driver for stepper motor coil A/In1
// PD2 connected to driver for stepper motor coil A'/In2
// PD1 connected to driver for stepper motor coil B/In3
// PD0 connected to driver for stepper motor coil B'/In4
#include <stdint.h>
#include "stepper.h"
#include "systick.h"

#define T1ms 16000    // assumes using 16 MHz PIOSC (default setting for clock source)
int main(void){
	unsigned int i=0;
	
  Stepper_Init();
  while(1){
		// turn clockwise 180 degrees:0.18 degree for each step
		for (i=0;i<1000; i++) {
      Stepper_CW(10*T1ms);   // output every 10ms, frequency for the stepper motor is 100Hz.
		}
		
	  SysTick_Wait(500*T1ms);  // wait for 0.5s
		
		// turn counter clockwise 180 degrees
		for (i=0;i<1000; i++) {
      Stepper_CCW(10*T1ms);   // output every 10ms
		}
  }
}
