/*
Engineer: Rodrigo Becerril Ferreyra
Company: California State University, Long Beach
Project: Lab 3
Date Completed: 23 April 2021
*/

/*
P6 and P7 are PWM outputs
P4 and P5 are direction outputs
F1, F2, and F3 are lights (outputs)
F4 and F0 are buttons (inputs)
*/

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"
#include "Nokia5110.h"

#define duty30 4800
#define duty60 9600
#define duty80 12800
#define duty98 15680
#define duty0 0

typedef const struct
{
    uint8_t direction;
    uint16_t gena; uint16_t genb;
    uint8_t lights;
    uint32_t duty_cycle;
    char outstring[73];
    uint8_t nextstate[4];
} Engine;

uint8_t leftbutton = 0;
uint8_t rightbutton = 0;
uint8_t state = 0;

void systick_delay(uint16_t);
void EnableInterrupts(void);

int main(void){
    // SysTick enable
    STCTRL = 0;
    STRELOAD = 16000 - 1; // 1 ms * 16 MHz
    STCURRENT = 0;
    STCTRL = 0x4;

    // FSM initialization
    Engine fsm[10] =
    {
        {// State 0
            .direction = 1, // forward
            .gena = 0x8C, .genb = 0x80C,
            .lights = 0x8, // 1000, green
            .duty_cycle = duty30,
            .nextstate = {0, 5, 1, 0},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 30%      F "
        },
        {// State 1
            .direction = 1, // forward
            .gena = 0x8C, .genb = 0x80C,
            .lights = 0x8, // 1000, green
            .duty_cycle = duty60,
            .nextstate = {1, 6, 2, 1},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 60%      F "
        },
        {// State 2
            .direction = 1, // forward
            .gena = 0x8C, .genb = 0x80C,
            .lights = 0x8, // 1000, green
            .duty_cycle = duty80,
            .nextstate = {2, 7, 3, 2},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 80%      F "
        },
        {// State 3
            .direction = 1, // forward
            .gena = 0x8C, .genb = 0x80C,
            .lights = 0x8, // 1000, green
            .duty_cycle = duty98,
            .nextstate = {3, 8, 4, 3},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 98%      F "
        },
        {// State 4
            .direction = 1, // forward
            .gena = 0x8C, .genb = 0x80C,
            .lights = 0x2, // 0010, red
            .duty_cycle = duty0,
            .nextstate = {4, 9, 0, 4},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    ---  0%      F "
        },
        {// State 5
            .direction = 0, // backward
            .gena = 0xC8, .genb = 0xC08,
            .lights = 0x4, // 0100, blue
            .duty_cycle = duty30,
            .nextstate = {5, 0, 6, 5},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 30%      B "
        },
        {// State 6
            .direction = 0, // backward
            .gena = 0xC8, .genb = 0xC08,
            .lights = 0x4, // 0100, blue
            .duty_cycle = duty60,
            .nextstate = {6, 1, 7, 6},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 60%      B "
        },
        {// State 7
            .direction = 0, // backward
            .gena = 0xC8, .genb = 0xC08,
            .lights = 0x4, // 0100, blue
            .duty_cycle = duty80,
            .nextstate = {7, 2, 8, 7},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 80%      B "
        },
        {// State 8
            .direction = 0, // backward
            .gena = 0xC8, .genb = 0xC08,
            .lights = 0x4, // 0100, blue
            .duty_cycle = duty98,
            .nextstate = {8, 3, 9, 8},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 98%      B "
        },
        {// State 9
            .direction = 0, // backward
            .gena = 0xC8, .genb = 0xC08,
            .lights = 0x2, // 0010, red
            .duty_cycle = duty0,
            .nextstate = {9, 4, 5, 9},
            .outstring = "************CECS347 LAB3************Speed    Dir-----    --- 0%      B "
        }
    };

    // Port F enable
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_RCGCGPIO_R&0x20)!=0x20);
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x01;
    GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_AFSEL_R &= ~0x1F;
    GPIO_PORTF_PUR_R |= 0x11;
    GPIO_PORTF_DEN_R |= 0x1F;
    GPIO_PORTF_DATA_R = 0xE;

    GPIO_PORTF_IM_R &= ~0x11;
    GPIO_PORTF_ICR_R = 0x11;
    GPIO_PORTF_IM_R |= 0x11;
    NVIC_EN0_R |= 0x40000000;
    EnableInterrupts();

    // LCD enable
    SYSCTL_RCGCGPIO_R |= 0x1;
    while((SYSCTL_RCGCGPIO_R & 0x1) != 0x1);
    Nokia5110_Init();
    //Nokia5110_Clear();

    // Port B enable
    SYSCTL_RCGCGPIO_R |= 0x02;
    while((SYSCTL_RCGCGPIO_R & 0x02) != 0x02);
    GPIO_PORTB_DIR_R |= 0xF0;
    GPIO_PORTB_AFSEL_R &= ~0xF0; GPIO_PORTB_AFSEL_R |= 0xC0;
    GPIO_PORTB_PCTL_R &= ~0xFF000000; GPIO_PORTB_PCTL_R |= 0x44000000;
    GPIO_PORTB_DEN_R |= 0xF0;
    
    // PWM enable
    SYSCTL_RCGCPWM_R |= 0x1;
    while((SYSCTL_RCGCPWM_R & 0x1) != 0x1);
    PWM0_0_CTL_R = 0;
    PWM0_0_CMPA_R = PWM0_0_CMPB_R = fsm[state].duty_cycle;
    PWM0_0_GENA_R = fsm[state].gena; PWM0_0_GENB_R = fsm[state].genb;
    PWM0_0_LOAD_R = 16000 - 1;
    PWM0_0_CTL_R = 0x281;
    PWM0_ENABLE_R |= 0x03;

    while(1)
    {
        Nokia5110_Clear(); Nokia5110_OutString(fsm[state].outstring);
        GPIO_PORTB_DATA_R &= ~0x30; GPIO_PORTB_DATA_R |= ((fsm[state].direction << 4) | (fsm[state].direction << 5));
        GPIO_PORTF_DATA_R = fsm[state].lights;
        PWM0_0_CMPA_R = PWM0_0_CMPB_R = fsm[state].duty_cycle;
        PWM0_0_GENA_R = fsm[state].gena; PWM0_0_GENB_R = fsm[state].genb;
        systick_delay(1000);
        state = fsm[state].nextstate[leftbutton | rightbutton];
        leftbutton = rightbutton = 0;
    }
}

/**
Stops the program for the given number of milliseconds.
*/
void systick_delay(uint16_t milliseconds)
{
    uint16_t i;
    for(i = 0; i < milliseconds; i++)
    {
        STCTRL |= 0x1; // start timer
        while(!(STCTRL >> 16)); // while count flag is 0
        STCTRL &= ~0x01; // stop timer
        STCURRENT = 0; // clear counter
    }
}

void GPIOPortF_Handler(void)
{
    switch(GPIO_PORTF_MIS_R)
    {
        case 0x10:
            GPIO_PORTF_ICR_R = 0x10;
            leftbutton = 0x2;
            break;
        case 0x01:
            GPIO_PORTF_ICR_R = 0x01;
            rightbutton = 0x1;
            break;
        default:
            GPIO_PORTF_ICR_R = 0x1F;
    }
}
