/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: Lab 3
    Date: 02 October 2020
*/
// for data types
#include <stdint.h>
// Base Port Memory Locations (for reference)
/*

    GPIO Port A (APB) base: 0x4000_4000     GPIO Port A (AHB) base: 0x4005_8000
    GPIO Port B (APB) base: 0x4000_5000     GPIO Port B (AHB) base: 0x4005_9000
    GPIO Port C (APB) base: 0x4000_6000     GPIO Port C (AHB) base: 0x4005_A000
    GPIO Port D (APB) base: 0x4000_7000     GPIO Port D (AHB) base: 0x4005_B000
    GPIO Port E (APB) base: 0x4002_4000     GPIO Port E (AHB) base: 0x4005_C000
    GPIO Port F (APB) base: 0x4002_5000     GPIO Port F (AHB) base: 0x4005_D000

*/

// Port E definitions
#define GPIO_PORTE_DATA_R  *((volatile unsigned long *) 0x400243FC)
#define GPIO_PORTE_DIR_R   *((volatile unsigned long *) 0x40024400)
#define GPIO_PORTE_AFSEL_R *((volatile unsigned long *) 0x40024420)
#define GPIO_PORTE_DEN_R   *((volatile unsigned long *) 0x4002451C)
// Port B definitions
#define GPIO_PORTB_DATA_R  *((volatile unsigned long *) 0x400053FC)
#define GPIO_PORTB_DIR_R   *((volatile unsigned long *) 0x40005400)
#define GPIO_PORTB_AFSEL_R *((volatile unsigned long *) 0x40005420)
#define GPIO_PORTB_DEN_R   *((volatile unsigned long *) 0x4000551C)
// system clock definition
#define SYSCTL_RCGC2_R     *((volatile unsigned long *) 0x400FE108)

// SysTick Timer definitions
// Base Core Peripherals register: 0xE000_E0000
#define STCTRL    *((volatile unsigned long *) 0xE000E010)
#define STRELOAD  *((volatile unsigned long *) 0xE000E014)
#define STCURRENT *((volatile unsigned long *) 0xE000E018)

// state definitions
#define NSredEWgreen  0
#define NSredEWyellow 1
#define NSgreenEWred  2
#define NSyellowEWred 3

// function prototypes
void delay(uint32_t);
void systick_init(void);
void PortE_init(void);
void PortB_init(void);

// FSM skeleton
typedef const struct
{
    uint32_t output;
    uint32_t delay_time;
    uint8_t next_state[4]; // organized {NS, EW} = {B[1], B[0]}
}
Engine;

int main(void)
{
    // port initialization
    PortE_init();
    PortB_init();
    systick_init();
    
    // FSM initialization
    Engine fsm[4] =
    {
        {// state 0: NSredEWgreen
            .output = 014, // 001_100
            .delay_time = 2000000, // 2 s
            .next_state = {NSredEWgreen, NSredEWgreen, NSredEWyellow, NSredEWyellow}
        },
        {// state 1: NSredEWyellow
            .output = 024, // 010_100
            .delay_time = 1000000, // 1 s
            .next_state = {NSgreenEWred, NSgreenEWred, NSgreenEWred, NSgreenEWred}
        },
        {// state 2: NSgreenEWred
            .output = 041, // 100_001
            .delay_time = 2000000, //2 s
            .next_state = {NSgreenEWred, NSyellowEWred, NSgreenEWred, NSyellowEWred}
        },
        {//state 3: NSyellowEWred
            .output = 042, // 100_010
            .delay_time = 1000000, //1 s
            .next_state = {NSredEWgreen, NSredEWgreen, NSredEWgreen, NSredEWgreen}
        }
    };

    
    uint8_t CS = NSredEWgreen;
    uint8_t input;
        
    // superloop
    
    while(1)
    {
        GPIO_PORTE_DATA_R = fsm[CS].output; // set outputs based on current state
        delay(fsm[CS].delay_time);          // delay for amount of time
        input = GPIO_PORTB_DATA_R;          // read input from two switches B[1:0]
        CS = fsm[CS].next_state[input];     // go to next state based on current state's logic
    }
}

void PortE_init(void)
{
    SYSCTL_RCGC2_R |= 0x10;                 // 01_0000
    while((SYSCTL_RCGC2_R & 0x10) != 0x10); // wait for clock to be ready
    GPIO_PORTE_AFSEL_R = 0;
    GPIO_PORTE_DIR_R   = 0xFF;              // all pins are outputs
    GPIO_PORTE_DEN_R   = 0x3F;              // enable pins E[5:0]
}

void PortB_init(void)
{
    SYSCTL_RCGC2_R |= 0x02;                 // 00_0010
    while((SYSCTL_RCGC2_R & 0x02) != 0x02); // wait for clock to be ready
    GPIO_PORTB_AFSEL_R = 0;
    GPIO_PORTB_DIR_R   = 0x00;              // B[1:0] are inputs //0000_0011
    GPIO_PORTB_DEN_R   = 0x03;              // enable pins B[1:0]
}

void systick_init(void)
{
    STCTRL    = 0x00; // clear all
    STCURRENT = 0x00; // clear current and count values
    STCTRL    = 0x04; // enable system clock
}

void delay(uint32_t microseconds)
{
    uint32_t i;
    
    STRELOAD = 16 - 1; // 1 us @ 16 MHz
    STCURRENT = 0x00; // clear count and current
    STCTRL |= 0x01; // start timer
    
    for(i = 0; i < microseconds; i++)
        while((STCTRL & 0x10000) == 0); // wait for timer to finish
    
    STCTRL &= ~0x01; //stop timer
}
