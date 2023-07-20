// Walk_Man.c
// Runs on TM4C123
// Uses ST7735.c LCD.
// Jonathan Valvano
// August 5, 2015
// Possible main program to test the lab
// Feel free to edit this to match your specifications

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected 
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO)
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdio.h>
#include <stdint.h>
#include "string.h"
#include "ST7735.h"
#include "PLL.h"
#include "walking.h"
#include "tm4c123gh6pm.h"
//void DelayWait10ms(uint32_t n);
// const will place these structures in ROM

/**
 * Initializes SysTick hardware timer to pre-configured parameters.
 * Assumes an 80 MHz system clock.
 * @author Rodrigo Becerril Ferreyra
 */
void systickInit(void);

/**
 * Delay the program by the desired time.
 * @param ms The amount of milliseconds to wait.
 * @author Rodrigo Becerril Ferreyra
 */
void systickWait(const uint32_t ms);

int main(void){
	uint32_t x = 40, ht = 0;	
	int32_t l = 15, h = 15;
	
  PLL_Init(12);
  ST7735_InitR(INITR_REDTAB);
	
	// DRAW THE GROUND
	ST7735_FillScreen(ST7735_CYAN);
	ST7735_FillRect(0, 150,128, 30, ST7735_GREEN);
	  
	// DRAW THE SUN
	ST7735_FillCircle(100, 30, 15,ST7735_YELLOW);
	
  while(1){
		
  // DRAW THE MAN
	ST7735_XYPlotMan( x, l, h, ST7735_RED);
	
  //DelayWait10ms(10);
    systickWait(100);
		
	// REMOVE THE MAN
	ST7735_XYPlotMan( x, l, h, ST7735_CYAN);
 
	// MOVE THE COORDINATES OF THE MAN
	x++;
 
	// CODE for MOVING the LEG
	l--;
	if (l == -15)
	    l = 15;
 
	// CODE for MOVING the HAND    
	if (ht == 1)
	    h++;
	else
	    h--;
 
	if (h == 15)
	   ht = 0;
	else if (h == -15)   
		ht = 1;
 
	//Reset parameters
	  if(x>170){
			x = 40, ht = 0,l = 15, h = 15;
    }
	}

  
} 

void systickInit(void)
{
    // stop the timer before setting registers
    NVIC_ST_CTRL_R &= ~0x1;
    // set reload to 1 ms
    // 80 MHz / (1/1 ms) = 80000
    NVIC_ST_RELOAD_R = 80000 - 1;
    // clear the current value
    NVIC_ST_CURRENT_R = 0;
    // use system clock and no interrupt
    NVIC_ST_CTRL_R |= 0x4;
    // note that the timer is not started in this function
}

void systickWait(const uint32_t ms)
{
    for(uint32_t i = 0; i < ms; ++i)
    {
        // clear count and start the timer
        NVIC_ST_CURRENT_R = 0;
        NVIC_ST_CTRL_R |= 0x01;
        // wait until the timer is finished
        while(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT);
        // stop the timer and clear count
        NVIC_ST_CTRL_R &= ~0x01;
        NVIC_ST_CURRENT_R = 0;
    }
}

// Subroutine to wait 10 msec
// Inputs: None
// Outputs: None
// Notes: ...
//void DelayWait10ms(uint32_t n){uint32_t volatile time;
//  while(n){
////    time = 727240*2/91;  // 10msec for launchpad
//    time = 7272/91;  // for simulation
//    while(time){
//	  	time--;
//    }
//    n--;
//  }
//}
