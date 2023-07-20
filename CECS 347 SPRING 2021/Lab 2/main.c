/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: CECS 347 Lab 2
    Date started: 31 January 2021
    Date completed: 10 January 2021
*/

#include <stdint.h> // for data types
#include "tm4c123gh6pm.h" // for port addresses

// function prototypes
extern void EnableInterrupts(void);
extern void WaitForInterrupt(void);

int main(void)
{
    // turning on clocks
    SYSCTL_RCGC0_R |= 0x100000; // enable PWM
    while((SYSCTL_RCGC0_R & 0x100000) != 0x100000);
    SYSCTL_RCGC2_R |= 0x20;     // enable Port F clock
    while((SYSCTL_RCGC2_R & 0x20) != 0x20);
    SYSCTL_RCGCPWM_R |= 0x2; // enable Module 1
    while((SYSCTL_RCGCPWM_R & 0x2) != 0x2);
    
    // unlocking and relocking Port F
    do{GPIO_PORTF_LOCK_R = 0x4C4F434B;}while(GPIO_PORTF_LOCK_R != 0); // unlock port f
    GPIO_PORTF_CR_R |= 0x01; // unlock CR for F[0]
    do{GPIO_PORTF_LOCK_R = 0x0;}while(GPIO_PORTF_LOCK_R == 0); // relock port f
    
    // using F[2] and F[3] for M1PWM6 and M1PWM7, respectively
    GPIO_PORTF_AFSEL_R &= ~0x1D; GPIO_PORTF_AFSEL_R |= 0xC; // also clearing F[4] and F[0]
    GPIO_PORTF_PCTL_R &= ~0xFF00; GPIO_PORTF_PCTL_R |= 0x5500;
    
    // Set USEPWMDIV and set it to /2
    SYSCTL_RCC_R |= 0x100000; SYSCTL_RCC_R &= 0xFFF1FFFF;
    
    // set up parameters for PWM (Module 1, Generator 3, A and B as F[2] and F[3])
    PWM1_3_CTL_R = 0; // clear ctl (count-down mode)
    PWM1_3_GENA_R = 0xC8; // low on LOAD, high on COMPAdown
    PWM1_3_GENB_R = 0xC08; // low on LOAD, high on COMPBdown
    PWM1_3_LOAD_R = 320 - 1;  // 25 kHz @ 8 MHz clock frequency
    PWM1_3_CMPA_R = 160 - 1;  // 50% duty cycle
    PWM1_3_CMPB_R = 160 - 1;  // 50% duty cycle
    PWM1_3_CTL_R |= 0x1;      // start timer
    PWM1_ENABLE_R |= 0xC0;    // enable M1PWM7 and M1PWM6
    
    // set up LEDs and buttons
    GPIO_PORTF_DIR_R &= ~0x1F; GPIO_PORTF_DIR_R |= 0xC;
    GPIO_PORTF_PUR_R |= 0x11;
    GPIO_PORTF_DEN_R |= 0x1D; // 1_1101
    
    // enable interrupts from F[0] and F[4]
    GPIO_PORTF_IM_R &= ~0x11;  // mask pins
    GPIO_PORTF_ICR_R = 0x11;   // clearing RIS
    GPIO_PORTF_IM_R |= 0x11;   // unmask pins
    NVIC_PRI7_R &= ~0xE00000;  // Priority 0 for Interrupt 30 (Port F)
    NVIC_EN0_R |= 0x40000000;  // Enable Interrupt 30 (Port F)
    
    while(1){WaitForInterrupt();}
}

void GPIOPortF_Handler(void)
{
    switch(GPIO_PORTF_MIS_R)
    {
        case 0x10: // Pin 4 (Left switch)
            GPIO_PORTF_ICR_R = 0x10;
            if(PWM1_3_CMPA_R <= 255 && PWM1_3_CMPB_R <= 255)
                // 255 = 320 - 2(320 * 10%) - 1
                {PWM1_3_CMPA_R += 32; PWM1_3_CMPB_R += 32;}
            break;

        case 0x01: // Pin 0 (Right switch)
            GPIO_PORTF_ICR_R = 0x01;
            if(PWM1_3_CMPA_R >= 63 && PWM1_3_CMPB_R >= 63)
                // 31 = 2(320 * 10%) - 1
                {PWM1_3_CMPA_R -= 32; PWM1_3_CMPB_R -= 32;}
            break;

        default:
            GPIO_PORTF_ICR_R = 0x11;
            break;
    }
}
