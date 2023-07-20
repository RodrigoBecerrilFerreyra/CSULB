/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 18 November 2020
*/

/*
    Project summary:
    Inputs: sensor = B[0], sw1 = F[4], sw2 = F[0]
    Outputs: F[3:1]
    Notes: sensor = 1 means that the sensor detects something;
    sensor = 0 means that the sensor does not detect anything.
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

// Port F definitions
// interrupt
#define F_GPIOIS  *((volatile unsigned long *) 0x40025404)
#define F_GPIOIBE *((volatile unsigned long *) 0x40025408)
#define F_GPIOIEV *((volatile unsigned long *) 0x4002540C)
#define F_GPIOIM  *((volatile unsigned long *) 0x40025410)
#define F_GPIOMIS *((volatile unsigned long *) 0x40025418)
#define F_GPIOICR *((volatile unsigned long *) 0x4002541C)

// data
#define F_GPIODATA   (volatile unsigned long *) 0x40025000 // not dereferencing
#define F_GPIODIR  *((volatile unsigned long *) 0x40025400)
#define F_GPIOPUR  *((volatile unsigned long *) 0x40025510)
#define F_GPIODEN  *((volatile unsigned long *) 0x4002551C)
#define F_GPIOLOCK *((volatile unsigned long *) 0x40025520)
#define F_GPIOCR   *((volatile unsigned long *) 0x40025524)

// Port B definitions
// interrupt
#define B_GPIOIS  *((volatile unsigned long *) 0x40005404)
#define B_GPIOIBE *((volatile unsigned long *) 0x40005408)
#define B_GPIOIEV *((volatile unsigned long *) 0x4000540C)
#define B_GPIOIM  *((volatile unsigned long *) 0x40005410)
#define B_GPIOMIS *((volatile unsigned long *) 0x40005418)
#define B_GPIOICR *((volatile unsigned long *) 0x4000541C)
    
//data
#define B_GPIODATA  (volatile unsigned long *) 0x40005000 // not dereferencing
#define B_GPIODIR *((volatile unsigned long *) 0x40005400)
#define B_GPIODEN *((volatile unsigned long *) 0x4000551C)

// system clock definition
#define RCGC2 *((volatile unsigned long *) 0x400FE108)

// SysTick Timer definitions
// Base Core Peripherals register: 0xE000_E0000
#define STCTRL    *((volatile unsigned long *) 0xE000E010)
#define STRELOAD  *((volatile unsigned long *) 0xE000E014)
#define STCURRENT *((volatile unsigned long *) 0xE000E018)

// state definitions
#define green    0
#define blue     1
//#define flashing 3
/*#define red_off1 2
#define red_on1  3
#define red_off2 4
#define red_on2  5
#define red_off3 6
#define red_on3  7
*/

// masks (avoids magic numbers)
#define Pin0   0x01
#define Pin4   0x10
#define Pin3_1 0x0E
#define debouncedelaytime 47950

// function prototypes
int main(void);
void systick_init(uint32_t);
void portF_init(void); void portB_init(void);
extern void EnableInterrupts(void); // defined in startup.s
extern void WaitForInterrupt(void); // defined in startup.s
void flash(void);

// global variables
// these variables are used for calculation of
// the next state in the FSM
volatile uint8_t sw1 = 0;
volatile uint8_t sw2 = 0;
volatile uint8_t sensor = 0;
volatile uint8_t sensor_flag = 0;
volatile uint8_t systick_count = 0;
volatile uint8_t isflashing = 0;

int main(void)
{
    portF_init(); portB_init();
    EnableInterrupts();
    uint8_t CS = green;
    // infinite loop
    while(1)
    {
    /*
        if(green)
            if(sensor)
                flash
                go blue
        else if(blue)
            if(!sensor)
                flash
                go green
        if(green)
            if(sw1)
                flash
                go blue
        else if(blue)
            if(sw2)
                flash
                go green
        set_outputs();
    */
        if(!isflashing)
        {
            if(CS == green)
                *(F_GPIODATA + Pin3_1) = 0x8/*0_1000*/;
            else if(CS == blue)
                *(F_GPIODATA + Pin3_1) = 0x4/*0_0100*/;
        }
        
        if(sensor_flag)
        {
            if(CS == green)
            {
                if(sensor)
                {
                    flash();
                    CS = blue;
                }
            }else if(CS == blue)
            {
                if(!sensor)
                {
                    flash();
                    CS = green;
                }
            }
            sensor_flag = 0;
            sw1 = 0; sw2 = 0;
        }

        if(CS == green)
        {
            if(sw1)
            {
                flash();
                CS = blue;
            }
            sw2 = 0;
        }else if(CS == blue)
        {
            if(sw2)
            {
                flash();
                CS = green;
            }
            sw1 = 0;
        }
    }
}

void flash(void)
{
    isflashing = 1;
    *(F_GPIODATA + Pin3_1) &= 0x11; // lights off 1_0001
    systick_init(8000000); // turn timer on, 500 ms
}
/*
    systick_init(void) function summary:
    Initializes SysTick timer and interrupt to
    trigger every 1 ms.
    Run at startup.
*/
void systick_init(uint32_t cycles)
{
    STCURRENT = 0x00;      // clear current and count values
    STCTRL   &= 0x00;      // clear all
    STCTRL   |= 0x04;      // enable system clock
    STCTRL   |= 0x02;      // enable interrupt
    STRELOAD  = cycles - 1; // 1 ms @ 16 MHz

    *((volatile unsigned long *) 0xE000E408) /*PRI3*/ &= 0x1FFFFFFF; // clear three MSBs, priority 0
    STCTRL |= 0x01; // start timer
    STCURRENT = 0x00; // clear current and count values
}

/*
    portF_init(void) function summary:
    Initializes Port F.
    Run at startup.
*/
void portF_init(void)
{
    RCGC2 |= 0x20; // 10_0000
    while((RCGC2 & 0x20) != 0x20); // wait for clock to enable
    
    F_GPIOLOCK = 0x4C4F434B;   // unlock F_GPIOCR
    while(F_GPIOLOCK != 0x0);  // wait for unlock
    F_GPIOCR |= 0x1;           // unlock F[0]
    F_GPIOLOCK = 0;            // lock F_GPIOCR
    while(F_GPIOLOCK != 0x1);  // wait for lock
    
    // data initialization
    F_GPIODIR |= ~(Pin4 | Pin0); // I_OOOI
    F_GPIOPUR |= Pin4 | Pin0; // 1_0001
    F_GPIODEN |= Pin4 | Pin3_1 | Pin0; // 1_1111
    
    // interrupt initialization
    F_GPIOIM  &= ~(Pin4 | Pin0); // mask F[4] and F[0]
    F_GPIOIS  &= ~(Pin4 | Pin0); // edge-triggered
    F_GPIOIBE &= ~(Pin4 | Pin0); // not both edges
    F_GPIOIEV &= ~(Pin4 | Pin0); // falling edge-triggered
    F_GPIOICR  =  (Pin4 | Pin0); // clear bits in GPIORIS and GPIOMIS
    F_GPIOIM  |=  (Pin4 | Pin0); // unmask F[4] and F[0]
    *((volatile unsigned long *) 0xE000E41C) /*PRI7*/ |= 0x400000; // priority 2
    *((volatile unsigned long *) 0xE000E100) /*EN0*/|= 0x40000000; // enable interrupt 30
}

/*
    portB_init(void) function summary:
    Initializes Port B.
    Run at startup.
*/
void portB_init(void)
{
    RCGC2 |= 0x02; // 00_0010
    while((RCGC2 & 0x02) != 0x02); // wait for clock to enable
    
    // data
    B_GPIODIR&= ~Pin0; // -_---I
    B_GPIODEN |= Pin0; // 0_0001
    
    // interrupt
    B_GPIOIM  &= ~Pin0; // mask B[0]
    B_GPIOIS  &= ~Pin0; // edge-sensitive trigger
    B_GPIOIBE |=  Pin0; // both edges
    //B_GPIOIEV &= ~Pin0; // falling edge
    B_GPIOICR  =  Pin0; // clear GPIORIS
    B_GPIOIM  |=  Pin0; // unmask B[0]
    
    *((volatile unsigned long *) 0xE000E400) |= /*PRI0*/0x2000; // Priority 1
    *((volatile unsigned long *) 0xE000E100) |= /*EN0*/0x2; // Interrupt 1
}

void GPIOPortF_Handler(void)
{
    uint16_t i; for(i = 0; i < debouncedelaytime; i++);
    switch(F_GPIOMIS)
    {
        case Pin0:
            F_GPIOICR = Pin0;
            sw2 = 1;
            break;
        case Pin4:
            F_GPIOICR = Pin4;
            sw1 = 1;
            break;
    }
}
void GPIOPortB_Handler(void)
{
    sensor_flag = 1;
    B_GPIOICR = Pin0;
    uint16_t i; for(i = 0; i < debouncedelaytime; i++);
    switch(*(B_GPIODATA + Pin0))
    {
        case 0: // obstacle detected
            sensor = 1;
            break;
        case 1: // no obstacle detected
            sensor = 0;
            break;
        default:
            sensor = 0;
            break;
    }
}

void SysTick_Handler(void)
{
    systick_count++;
    *(F_GPIODATA + Pin3_1) ^= 0x02;
    if(systick_count >= 6)
    {
        STCTRL &= ~0x01; // turn timer off
        systick_count = 0;
        isflashing = 0;
    }
}

