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

volatile uint32_t flag;

// Port F definitions
#define GPIO_PORTF_DATA_R  *((volatile unsigned long *) 0x400253FC)
#define GPIO_PORTF_DIR_R   *((volatile unsigned long *) 0x40025400)
#define GPIO_PORTF_AFSEL_R *((volatile unsigned long *) 0x40025420)
#define GPIO_PORTF_DEN_R   *((volatile unsigned long *) 0x4002551C)
#define GPIO_PORTF_PUR_R   *((volatile unsigned long *) 0x40025510)

#define GPIO_PORTF_IS_R    *((volatile unsigned long *) 0x40025404)
#define GPIO_PORTF_IBE_R   *((volatile unsigned long *) 0x40025408)
#define GPIO_PORTF_IEV_R   *((volatile unsigned long *) 0x4002540C)
#define GPIO_PORTF_IM_R    *((volatile unsigned long *) 0x40025410)
#define GPIO_PORTF_RIS_R   *((volatile unsigned long *) 0x40025414)
#define GPIO_PORTF_MIS_R   *((volatile unsigned long *) 0x40025418)
#define GPIO_PORTF_ICR_R   *((volatile unsigned long *) 0x4002541C)
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

// function prototypes
void delay(uint32_t);
void systick_init(void);
void PortF_init(void);
void PortB_init(void);
extern void EnableInterrupts(void);

typedef const struct
{
    uint8_t output;
    uint32_t delay_time;
    uint8_t next_state[2];
}
Engine;

int main(void)
{
    // port initialization
    systick_init();
    PortF_init();
    PortB_init();

    Engine fsm[2] =
    {
        {// red (state 0)
            .output = 0x02, //0_0010
            .delay_time = 2000,
            .next_state = {0, 1}
        },
        {// green (state 1)
            .output = 0x08,
            .delay_time = 2000,
            .next_state = {0, 1}
        }
    };

    uint8_t cs = 0;
    uint8_t input;

    while(1)
    {
        // set outputs based on current state
        GPIO_PORTF_DATA_R = fsm[cs].output;
        
        // delay for set amount of time
        delay(fsm[cs].delay_time);
        
        // read inputs
        //input = (~GPIO_PORTF_DATA_R & 0x10) >> 4;//1_0000
        input = flag;
        flag = 0;
        
        // go to next state based on inputs
        cs  = fsm[cs].next_state[input];
        
    }
}

void GPIOPortF_Handler(void)
{
    GPIO_PORTF_ICR_R = 0x10;
    flag = 1;
}

void systick_init(void)
{
    STCTRL    = 0x00; // clear all
    STCURRENT = 0x00; // clear current and count values
    STCTRL    = 0x04; // enable system clock
}

void PortF_init(void) // also sets up interrupt
{
    // GPIO setup
    SYSCTL_RCGC2_R |= 0x20;                 // 10_0000
    while((SYSCTL_RCGC2_R & 0x20) != 0x20); // wait for clock to be ready
    GPIO_PORTF_AFSEL_R = 0;
    GPIO_PORTF_DIR_R = 0x0E;                // 0_1110
    GPIO_PORTF_PUR_R = 0x10;                // 1_0000
    GPIO_PORTF_DEN_R = 0x1E;                // 1_1110
    
    // Interrupt setup (for F[4])
    GPIO_PORTF_IM_R &= ~0x10;               // mask F[4] (recommended by datasheet)
    GPIO_PORTF_IS_R &= ~0x10;               // edge-triggered
    GPIO_PORTF_IBE_R &= ~0x10;              // not both edge triggered
    GPIO_PORTF_IEV_R &= ~0x10;              // falling edge
    GPIO_PORTF_ICR_R = 0x10;                // clear GPIORIS
    GPIO_PORTF_IM_R |= 0x10;                // unmask F[4]

    // setting NVIC registers; see pp.  104, 152, 142 of datasheet
    // Port F interrupt = 30
    *((volatile unsigned long *) 0xE000E41C) &= ~0xE00000; // Set PRI7 to priority 0, 4(7)+2=30
    *((volatile unsigned long *) 0xE000E100) |= 0x40000000; // EN0 enabling Interrupt 30         

    EnableInterrupts();
}

void PortB_init(void)
{
    SYSCTL_RCGC2_R |= 0x02;                 // 00_0010
    while((SYSCTL_RCGC2_R & 0x02) != 0x02); // wait for clock to be ready
    GPIO_PORTB_AFSEL_R = 0;
    GPIO_PORTB_DIR_R   = 0x00;              // B[2] are inputs //0000_0000
    GPIO_PORTB_DEN_R   = 0x04;              // enable pins B[2]
}

void delay(uint32_t milliseconds)
{
    uint32_t i;
    
    STRELOAD = 16000 - 1; // 1 us @ 16 MHz
    STCURRENT = 0x00; // clear count and current
    STCTRL |= 0x01; // start timer
    
    for(i = 0; i < milliseconds; i++)
        while((STCTRL & 0x10000) == 0); // wait for timer to finish
    
    STCTRL &= ~0x01; //stop timer
}
