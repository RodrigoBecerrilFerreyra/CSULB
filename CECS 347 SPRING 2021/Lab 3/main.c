/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: CECS 347 Project 1
    Date completed: 05 March 2021
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
#include "Nokia5110.h" // for SSI interface

#define STCTRL (*((volatile unsigned long *) 0xE000E010))
#define STCURRENT (*((volatile unsigned long *) 0xE000E018))

// function prototypes
extern void EnableInterrupts(void);
extern void WaitForInterrupt(void);

// global variables (flags)
uint8_t state = 0;

int main(void)
{
    // turning on clocks
    SYSCTL_RCGC0_R |= 0x100000; // enable PWM
    while((SYSCTL_RCGC0_R & 0x100000) != 0x100000);
    SYSCTL_RCGC2_R |= 0x22;     // enable Port B and Port F clocks
    while((SYSCTL_RCGC2_R & 0x22) != 0x22);
    SYSCTL_RCGCPWM_R |= 0x1; // enable Module 0
    while((SYSCTL_RCGCPWM_R & 0x1) != 0x1);

    Nokia5110_Init();
/*
    // PLL configuration (50 MHz output)
    SYSCTL_RCC2_R |= 0x80000000;  // use RCC2 instead of RCC
    SYSCTL_RCC2_R |= 0x800;       // bypass PLL circuit while initializing
    SYSCTL_RCC_R &= ~0x7C0;
    SYSCTL_RCC_R |= (0x15 << 6);  // specifying 16 MHz source freqency
    SYSCTL_RCC2_R &= ~0x70;       // use main osc
    SYSCTL_RCC2_R &= ~0x2000;     // activate PLL
    SYSCTL_RCC2_R |= (0x1 << 30); // use 400 MHz PLL output
    SYSCTL_RCC2_R &= ~0x1F800000;
    SYSCTL_RCC2_R |= (0x7 << 23); // set n = 7 for (400 MHz / (7 + 1)) = 50 MHz
    while((SYSCTL_RIS_R & 0x40) != 0x40); // wait for PLLRIS to be raised
    SYSCTL_RCC2_R &= ~0x800;       // don't bypass PLL circuit
*/
    // unlocking and relocking Port F
    do{GPIO_PORTF_LOCK_R = 0x4C4F434B;}while(GPIO_PORTF_LOCK_R != 0); // unlock port f
    GPIO_PORTF_CR_R |= 0x01; // unlock CR for F[0]
    do{GPIO_PORTF_LOCK_R = 0x0;}while(GPIO_PORTF_LOCK_R == 0); // relock port f

    // using B[4:7] for M0PWM2, M0PWM3, M0PWM0, and M0PWM1 respectively.
    GPIO_PORTB_AFSEL_R &= ~0xFF; GPIO_PORTB_AFSEL_R |= 0xF0; // also clearing B[3:0]
    GPIO_PORTB_PCTL_R &= ~0xFFFF0000; GPIO_PORTB_PCTL_R |= 0x44440000;

    // using B[3:0] for direction control
    GPIO_PORTB_DIR_R |= 0x0F; // B[3:0] output
    GPIO_PORTB_DEN_R |= 0xFF;

    // Set USEPWMDIV and set it to /2
    SYSCTL_RCC_R |= 0x100000; SYSCTL_RCC_R &= 0xFFF1FFFF;

    // set up parameters for PWM (Module 0, Generators 0 and 1)
    PWM0_0_CTL_R  = PWM0_1_CTL_R  = 0;         // cound-down mode
    PWM0_0_GENA_R = PWM0_1_GENA_R = 0x8C;      // high on LOAD, low on COMPAdown
    PWM0_0_GENB_R = PWM0_1_GENB_R = 0x80C;     // high on LOAD, low on COMPBdown
    PWM0_0_LOAD_R = PWM0_1_LOAD_R = 60000 - 1;
    PWM0_0_CMPA_R = PWM0_0_CMPB_R = PWM0_1_CMPA_R = PWM0_1_CMPB_R = 18000 - 1; // 0.3 duty cycle
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
    
    // enable systick (clock = 50 MHz)
    *((volatile unsigned long *) 0xE000E014) = 12500000 - 1; // 250 ms @ 50 MHz
    STCURRENT = 0; // clear STCURRENT
    STCTRL |= 0x04; // set clock source (50 MHz)

    GPIO_PORTB_DATA_R |= 0x0F; // forward
    GPIO_PORTF_DATA_R |= 0x08; // green
    
    Nokia5110_Clear();

    while(1)
    {
        //WaitForInterrupt();
    }
}

void GPIOPortF_Handler(void)
{
    // wait for 5 ms (debouncing)
    STCTRL |= 0x01; // start timer
    while((STCTRL & 0x10000) != 0x10000); // wait for count flag
    STCTRL &= ~0x01; // stop timer
    STCURRENT = 0; // clear count

    // this is necessary because forwards and backwards behave differently
    // on forward, the low PWM becomes the duty cycle
    // on backward, the high PWM becomes the duty cycle
    if((GPIO_PORTB_DATA_R & 0x0F) == 0x0F) // forward
    {
        PWM0_0_GENA_R = PWM0_1_GENA_R = 0x8C;  // high on LOAD, low on COMPAdown
        PWM0_0_GENB_R = PWM0_1_GENB_R = 0x80C; // high on LOAD, low on COMPBdown
    }else // backward
    {
        PWM0_0_GENA_R = PWM0_1_GENA_R = 0xC8;  // low on LOAD, high on COMPAdown
        PWM0_0_GENB_R = PWM0_1_GENB_R = 0xC08; // low on LOAD, high on COMPBdown
    }

    if(GPIO_PORTF_MIS_R == 0x10) // Pin 4 (Left switch)
    {
        GPIO_PORTF_ICR_R = 0x10;
        state++; if(state >= 5) {state = 0;}

        switch(state)
        {
            case 0: // 0.3
                PWM0_0_CMPA_R = PWM0_0_CMPB_R = PWM0_1_CMPA_R = PWM0_1_CMPB_R = 18000 - 1;
                break;
            case 1: // 0.6
                PWM0_0_CMPA_R = PWM0_0_CMPB_R = PWM0_1_CMPA_R = PWM0_1_CMPB_R = 36000 - 1;
                break;
            case 2: // 0.8
                PWM0_0_CMPA_R = PWM0_0_CMPB_R = PWM0_1_CMPA_R = PWM0_1_CMPB_R = 48000 - 1;
                break;
            case 3: // 0.98
                PWM0_0_CMPA_R = PWM0_0_CMPB_R = PWM0_1_CMPA_R = PWM0_1_CMPB_R = 58000 - 1;
                break;
            case 4: // 0 (stop)
                PWM0_0_CMPA_R = PWM0_0_CMPB_R = PWM0_1_CMPA_R = PWM0_1_CMPB_R = 1;
                break;
            default:
                state = 0;
        }

    }
    else if(GPIO_PORTF_MIS_R == 0x01) // Pin 0 (Right switch)
    {
        GPIO_PORTF_ICR_R = 0x01;

        if((GPIO_PORTB_DATA_R & 0x0F) == 0x0F) // forward
            GPIO_PORTB_DATA_R &= ~0x0F;
        else // backward
            GPIO_PORTB_DATA_R |= 0x0F;
    
    } else {GPIO_PORTF_ICR_R = 0x11;} // error-avoiding statement

    if(state == 4)
    {
        if((GPIO_PORTB_DATA_R & 0x0F) == 0x0F) // forward
        {
            PWM0_0_GENA_R = PWM0_1_GENA_R = 0x8C;  // high on LOAD, low on COMPAdown
            PWM0_0_GENB_R = PWM0_1_GENB_R = 0x80C; // high on LOAD, low on COMPBdown
        }else // backward
        {
            PWM0_0_GENA_R = PWM0_1_GENA_R = 0xC8;  // low on LOAD, high on COMPAdown
            PWM0_0_GENB_R = PWM0_1_GENB_R = 0xC08; // low on LOAD, high on COMPBdown
        }
    }

   if(state == 4)
       {GPIO_PORTF_DATA_R &= ~0xE; GPIO_PORTF_DATA_R |= 0x02;} // red
   else
   {
       if((GPIO_PORTB_DATA_R & 0x0F) == 0x0F)// forward
           {GPIO_PORTF_DATA_R &= ~0xE; GPIO_PORTF_DATA_R |= 0x08;} // green
       else
           {GPIO_PORTF_DATA_R &= ~0xE; GPIO_PORTF_DATA_R |= 0x04;} // blue
   }
}
