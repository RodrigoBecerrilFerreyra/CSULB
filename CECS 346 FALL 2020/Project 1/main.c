/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: Project 1
    Date: 21 October 2020
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

#define GPIO_PORTB_IS_R    *((volatile unsigned long *) 0x40005404)
#define GPIO_PORTB_IBE_R   *((volatile unsigned long *) 0x40005408)
#define GPIO_PORTB_IEV_R   *((volatile unsigned long *) 0x4000540C)
#define GPIO_PORTB_IM_R    *((volatile unsigned long *) 0x40005410)
#define GPIO_PORTB_RIS_R   *((volatile unsigned long *) 0x40005414)
#define GPIO_PORTB_MIS_R   *((volatile unsigned long *) 0x40005418)
#define GPIO_PORTB_ICR_R   *((volatile unsigned long *) 0x4000541C)

// Port F definitions
#define GPIO_PORTF_DATA_R    (volatile unsigned long *) 0x40025000 // not dereferencing
#define GPIO_PORTF_DIR_R   *((volatile unsigned long *) 0x40025400)
#define GPIO_PORTF_AFSEL_R *((volatile unsigned long *) 0x40025420)
#define GPIO_PORTF_DEN_R   *((volatile unsigned long *) 0x4002551C)

// system clock definition
#define SYSCTL_RCGC2_R     *((volatile unsigned long *) 0x400FE108)

// SysTick Timer definitions
// Base Core Peripherals register: 0xE000_E0000
#define STCTRL    *((volatile unsigned long *) 0xE000E010)
#define STRELOAD  *((volatile unsigned long *) 0xE000E014)
#define STCURRENT *((volatile unsigned long *) 0xE000E018)

// state definitions
#define GoS   0
#define WaitS 1
#define GoW   2
#define WaitW 3
#define GoP   4
#define WPOn1 5 // WaitPOn1
#define WPOf1 6 // WaitPOff1
#define WPOn2 7
#define WPOf2 8

// read/write masks
#define F3mask 0x08 //   1000
#define F1mask 0x02 //   0010

// function prototypes
void delay(uint32_t);
void systick_init(void);
void PortE_init(void);
void PortB_init(void);
void PortF_init(void);
extern void EnableInterrupts(void);

volatile uint8_t flag;

// FSM skeleton
typedef const struct
{//                               Green  Red   South   West
    uint32_t output[4]; // organized {F[3], F[1], E[5:3] E[2:0], flag_setter} // E[2:0] = {green, yellow, red}
    uint32_t delay_time;
    uint8_t next_state[9]; // organized {P, S, W} = B[2:0]
}
Engine;

int main(void)
{
    // initialization
    PortE_init();
    PortB_init();
    PortF_init();
    systick_init();
    
    // FSM initialization
    Engine fsm[9] =
    {
        {// State 0: GoS
            .output = {0, 1, 041, 1}, // 0,1,100_001,don't_clear
            .delay_time = 6000,
            .next_state = {GoS, WaitS, GoS, WaitS, WaitS, WaitS, WaitS, WaitS}
        },
        {// State 1: WaitS
            .output = {0, 1, 021, 1}, // 0,1,010_001,don't_clear
            .delay_time = 2000,
            .next_state = {GoW, GoW, GoS, GoW, GoP, GoW, GoP, GoW}
        },
        {// State 2: GoW
            .output = {0, 1, 014, 1}, // 0,1,001_100,don't_clear
            .delay_time = 6000,
            .next_state = {GoW, GoW, WaitW, WaitW, WaitW, WaitW, WaitW, WaitW}
        },
        {// State 3: WaitW
            .output = {0, 1, 012, 1}, // 0,1,001_010,don't_clear
            .delay_time = 2000,
            .next_state = {GoS, GoW, GoS, GoS, GoP, GoP, GoP, GoP}
        },
        {// State 4: GoP
            .output = {1, 0, 011, 1}, // 1,0,001_001,don't_clear
            .delay_time = 6000,
            .next_state = {GoP, WPOn1, WPOn1, WPOn1, GoP, WPOn1, WPOn1, WPOn1}
        },
        {// State 5: WPOn1
            .output = {0, 1, 011, 1}, // 0,1,001_001,don't_clear
            .delay_time = 500,
            .next_state = {WPOf1, WPOf1, WPOf1, WPOf1, WPOf1, WPOf1, WPOf1, WPOf1}
        },
        {// State 6: WPOf1
            .output = {0, 0, 011, 1}, // 0,0,001_001,don't_clear
            .delay_time = 500,
            .next_state = {WPOn2, WPOn2, WPOn2, WPOn2, WPOn2, WPOn2, WPOn2, WPOn2}
        },
        {// State 7: WPOn2
            .output = {0, 1, 011, 1}, // 0,1,001_001, dont_clear
            .delay_time = 500,
            .next_state = {WPOf2, WPOf2, WPOf2, WPOf2, WPOf2, WPOf2, WPOf2, WPOf2}
        },
        {// State 8: WPOf2
            .output = {0, 0, 011, 0}, // 0,0,001_001,clear
            .delay_time = 500,
            .next_state = {GoS, GoW, GoS, GoS, GoP, GoW, GoS, GoS}
        }
    };

    
    uint8_t CS = GoS;
    uint8_t input;
        
    // superloop
    
    while(1)
    {
        // set outputs based on current state
        *(GPIO_PORTF_DATA_R + F3mask) = fsm[CS].output[0] << 3; // Modifying only F[3]
        *(GPIO_PORTF_DATA_R + F1mask) = fsm[CS].output[1] << 1; // Modifying only F[1]
        GPIO_PORTE_DATA_R = fsm[CS].output[2];
        
        // delay for amount of time
        delay(fsm[CS].delay_time);
        
        // read input from (flag << 2) | B[1:0]
        input = (flag << 2) | GPIO_PORTB_DATA_R;
        
        // clear or leave flag
        flag &= fsm[CS].output[3];
        
        // go to next state based on current state's inputs
        CS = fsm[CS].next_state[input];
    }
}

void GPIOPortB_Handler(void)
{
    GPIO_PORTB_ICR_R = 0x04;
    flag = 1;
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
    // GPIO setup
    SYSCTL_RCGC2_R |= 0x02;                 // 00_0010
    while((SYSCTL_RCGC2_R & 0x02) != 0x02); // wait for clock to be ready
    GPIO_PORTB_AFSEL_R &= ~0x07;            // no alternate function
    GPIO_PORTB_DIR_R   &= ~0x07;            // B[2:0] are inputs //0000_0000
    GPIO_PORTB_DEN_R   |= 0x07;             // enable pins B[2:0]
    
    // interrupt setup (for B[2])
    GPIO_PORTB_IM_R &= ~0x04;               // mask B[2] (recommended by datasheet)
    GPIO_PORTB_IS_R &= ~0x04;               // edge-triggered
    GPIO_PORTB_IBE_R &= ~0x04;              // not both edge triggered
    GPIO_PORTB_IEV_R |= 0x04;               // rising edge
    GPIO_PORTB_ICR_R = 0x04;                // clear GPIORIS
    GPIO_PORTB_IM_R |= 0x04;                // unmask B[2]
    
    // NVIC setup; see pp.  104, 152, 142 of datasheet
    // Port B is Interrupt 1
    *((volatile unsigned long *) 0xE000E400)/*PRI0*/ &= ~0xE000; // Priority 0, 4(0)+1=1
    *((volatile unsigned long *) 0xE000E100)/*EN0*/ |= 0x2;      // Enabling Interrupt 1
    
    EnableInterrupts();
}

void PortF_init(void)
{
    SYSCTL_RCGC2_R |= 0x20;                 // 10_0000
    while((SYSCTL_RCGC2_R & 0x20) != 0x20); // wait for clock to be ready
    GPIO_PORTF_AFSEL_R = 0;
    GPIO_PORTF_DIR_R = 0x0A;                // 0_1010
    GPIO_PORTF_DEN_R = 0x0A;                // 0_1010
}

void systick_init(void)
{
    STCTRL    = 0x00; // clear all
    STCURRENT = 0x00; // clear current and count values
    STCTRL    = 0x04; // enable system clock
}

void delay(uint32_t milliseconds)
{
    uint32_t i;
    
    STRELOAD = 16000 - 1; // 1 ms @ 16 MHz
    STCURRENT = 0x00; // clear count and current
    STCTRL |= 0x01; // start timer
    
    for(i = 0; i < milliseconds; i++)
        while((STCTRL & 0x10000) == 0); // wait for timer to finish
    
    STCTRL &= ~0x01; //stop timer
}
