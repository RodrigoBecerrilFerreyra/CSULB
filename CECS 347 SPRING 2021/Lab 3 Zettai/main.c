/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: CECS 347 Project 1
    Date completed: 16 April 2021
*/

/*
I/O:
B[7:4] are PWM outputs, B[3:0] are direction outputs
F[3:1] are LED outputs; F[4] and F[1] are button inputs
A[2:3], A[5:7] are LCD outputs:
    A[2] -> CLK
    A[3] -> CE
    A[5] -> DIN
    A[6] -> DC
    A[7] -> RST
*/

#include <stdint.h> // for data types
#include "tm4c123gh6pm.h" // for port addresses
#include "Nokia5110.h" // LCD code

// for SysTick timer
#define STCTRL (*((volatile unsigned long *) 0xE000E010))
#define STCURRENT (*((volatile unsigned long *) 0xE000E018))
// magic numbers
#define duty30 120 - 1
#define duty60 180 - 1
#define duty80 240 - 1
#define duty98 294 - 1
#define duty0  1

// function prototypes
extern void EnableInterrupts(void);
//extern void WaitForInterrupt(void);

// global variables
uint8_t state;
uint8_t input = 0;
uint8_t interrputed = 0;

typedef const struct
{
    uint8_t direction;
    uint16_t generators[2]; // {gen a, gen b}
    uint8_t lights;
    uint32_t duty_cycle;
    uint8_t next_state[2];
    char LCD_output[8];
} Engine;

int main(void)
{
    // FSM declaration
    Engine fsm[10] =
    {
        {// State 0
            .direction = 0x0F,
            .generators = {0x8C, 0x80C},
            .lights = 0x08, // green
            .duty_cycle = duty30,
            .next_state = {5, 1},
            .LCD_output = "State 0"
        },
        {// State 1
            .direction = 0x0F,
            .generators = {0x8C, 0x80C},
            .lights = 0x08, // green
            .duty_cycle = duty60,
            .next_state = {6, 2},
            .LCD_output = "State 1"
        },
        {// State 2
            .direction = 0x0F,
            .generators = {0x8C, 0x80C},
            .lights = 0x08, // green
            .duty_cycle = duty80,
            .next_state = {7, 3},
            .LCD_output = "State 2"
        },
        {// State 3
            .direction = 0x0F,
            .generators = {0x8C, 0x80C},
            .lights = 0x08, // green
            .duty_cycle = duty98,
            .next_state = {8, 4},
            .LCD_output = "State 3"
        },
        {// State 4
            .direction = 0x0F,
            .generators = {0x8C, 0x80C},
            .lights = 0x02, // red
            .duty_cycle = duty0,
            .next_state = {9, 0},
            .LCD_output = "State 4"
        },
        {// State 5
            .direction = 0x00,
            .generators = {0xC8, 0xC08},
            .lights = 0x04, // blue
            .duty_cycle = duty30,
            .next_state = {0, 6},
            .LCD_output = "State 5"
        },
        {// State 6
            .direction = 0x00,
            .generators = {0xC8, 0xC08},
            .lights = 0x04, // blue
            .duty_cycle = duty60,
            .next_state = {1, 7},
            .LCD_output = "State 6"
        },
        {// State 7
            .direction = 0x00,
            .generators = {0xC8, 0xC08},
            .lights = 0x04, // blue
            .duty_cycle = duty80,
            .next_state = {2, 8},
            .LCD_output = "State 7"
        },
        {// State 8
            .direction = 0x00,
            .generators = {0xC8, 0xC08},
            .lights = 0x04, // blue
            .duty_cycle = duty98,
            .next_state = {3, 9},
            .LCD_output = "State 8"
        },
        {// State 9
            .direction = 0x00,
            .generators = {0xC8, 0xC08},
            .lights = 0x02, // red
            .duty_cycle = duty0,
            .next_state = {4, 5},
            .LCD_output = "State 9"
        }
    };

    state = 0;

    // turning on clocks
    SYSCTL_RCGC0_R |= 0x100000; // enable PWM
    while((SYSCTL_RCGC0_R & 0x100000) != 0x100000);

    SYSCTL_RCGC2_R |= 0x22;     // enable Port B and Port F clocks
    while((SYSCTL_RCGC2_R & 0x22) != 0x22);

    //SYSCTL_RCGCPWM_R |= 0x1; // enable Module 0
    SYSCTL_RCGC0_R |= SYSCTL_RCGC0_PWM0;
    //while((SYSCTL_RCGCPWM_R & 0x1) != 0x1);
    while((SYSCTL_RCGC0_R & 0x100000) != 0x100000);

    // LCD init
    Nokia5110_Init();

    // unlocking and relocking Port F
    do{GPIO_PORTF_LOCK_R = 0x4C4F434B;}while(GPIO_PORTF_LOCK_R != 0); // unlock port f
    GPIO_PORTF_CR_R |= 0x01; // unlock CR for F[0]
    do{GPIO_PORTF_LOCK_R = 0x0;}while(GPIO_PORTF_LOCK_R == 0); // relock port f

    // using B[4:7] for M0PWM2, M0PWM3, M0PWM0, and M0PWM1 respectively.
    //GPIO_PORTB_AFSEL_R &= ~0xFF; GPIO_PORTB_AFSEL_R |= 0xF0; // also clearing B[3:0]
    GPIO_PORTB_AFSEL_R = 0xF0;
    //GPIO_PORTB_PCTL_R &= ~0xFFFF0000; GPIO_PORTB_PCTL_R |= 0x44440000;
    GPIO_PORTB_PCTL_R = 0x44440000;

    // using B[3:0] for direction control
    GPIO_PORTB_DIR_R |= 0x0F; // B[3:0] output
    GPIO_PORTB_DEN_R |= 0xFF;

    // initialize PWM (Module 0, Generators 0 and 1)
    PWM0_0_CTL_R  = PWM0_1_CTL_R  = 0;         // cound-down mode
    PWM0_0_GENA_R = PWM0_1_GENA_R = fsm[state].generators[0];
    PWM0_0_GENB_R = PWM0_1_GENB_R = fsm[state].generators[1];
    PWM0_0_LOAD_R = PWM0_1_LOAD_R = 300 - 1;
    PWM0_0_CMPA_R = PWM0_0_CMPB_R = PWM0_1_CMPA_R = PWM0_1_CMPB_R = fsm[state].duty_cycle;
    PWM0_0_CTL_R |= 0x1; PWM0_1_CTL_R |= 0x1;// start timer
    PWM0_ENABLE_R |= 0x0F; // enable

    // set up LEDs and buttons
    GPIO_PORTF_DIR_R &= ~0x1F; GPIO_PORTF_DIR_R |= 0xE; // 0_1110
    GPIO_PORTF_PUR_R |= 0x11;
    GPIO_PORTF_DEN_R |= 0x1F; // 1_1111

    // enable interrupts from F[0] and F[4]
    GPIO_PORTF_IM_R &= ~0x11;  // mask pins
    GPIO_PORTF_ICR_R = 0x11;   // clearing RIS
    GPIO_PORTF_IM_R |= 0x11;   // unmask pins
    NVIC_PRI7_R &= ~0xE00000;  // Priority 0 for Interrupt 30 (Port F)
    NVIC_EN0_R |= 0x40000000;  // Enable Interrupt 30 (Port F)

    // enable systick (clock = 16 MHz)
    *((volatile unsigned long *) 0xE000E014) = 4000000 - 1; // 250 ms @ 16 MHz
    STCURRENT = 0; // clear STCURRENT
    STCTRL |= 0x04; // set clock source (16 MHz)

    GPIO_PORTB_DATA_R &= ~0x0F; GPIO_PORTB_DATA_R |= fsm[state].direction;
    GPIO_PORTF_DATA_R &= ~0x0E; GPIO_PORTF_DATA_R |= fsm[state].lights;

    // set up LCD
    Nokia5110_Clear();
    Nokia5110_OutString(fsm[state].LCD_output);
    
    while(1)
    {
        if(interrputed)
        {
            state = fsm[state].next_state[input];
            GPIO_PORTB_DATA_R &= ~0x0F; GPIO_PORTB_DATA_R |= fsm[state].direction;
            PWM0_0_GENA_R = PWM0_1_GENA_R = fsm[state].generators[0];
            PWM0_0_GENB_R = PWM0_1_GENB_R = fsm[state].generators[1];
            GPIO_PORTF_DATA_R &= ~0x0E; GPIO_PORTF_DATA_R |= fsm[state].lights;
            PWM0_0_CMPA_R = PWM0_0_CMPB_R = PWM0_1_CMPA_R = PWM0_1_CMPB_R = fsm[state].duty_cycle;

            Nokia5110_Clear();
            Nokia5110_OutString(fsm[state].LCD_output);

            interrputed = 0;
            input = 0;
        }
    }
}

void GPIOPortF_Handler(void)
{
    interrputed = 1;

    // delay for 1 s
    uint8_t i;
    for(i = 0; i < 4; i++)
    {
        STCTRL |= 0x01; // start timer
        while(STCTRL & 0x10000); // wait for COUNT flag
        STCTRL &= ~0x01; STCURRENT = 0; // stop timer, clear count
    }

    switch(GPIO_PORTF_MIS_R)
    {
        case 0x10: // SW1 (left)
            GPIO_PORTF_ICR_R = 0x10;
            input = 1;
            break;
        case 0x01: // SW2 (right)
            GPIO_PORTF_ICR_R = 0x01;
            input = 0;
            break;
        default:
            GPIO_PORTF_ICR_R = 0x11;
    }
}
