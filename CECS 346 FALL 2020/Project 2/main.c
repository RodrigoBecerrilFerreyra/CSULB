/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Project 2
    Date: 18 December 2020
*/

/*
    Project summary:
    Inputs: sensor = B[0], sw1 = F[4]
    Outputs: F[3:1], B[7:4]
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
#define B_GPIODATA   (volatile unsigned long *) 0x40005000 // not dereferencing
#define B_GPIODIR  *((volatile unsigned long *) 0x40005400)
#define B_GPIODEN  *((volatile unsigned long *) 0x4000551C)
#define B_GPIODR8R *((volatile unsigned long *) 0x40005508)

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

// masks (avoids magic numbers)
#define Pin0   0x01
#define Pin4   0x10
#define Pin3_1 0x0E
#define MotorOutPins 0xF0 //1111_0000
#define debouncedelaytime 47950

// function prototypes
int main(void);
void systick_init(uint32_t);
void portF_init(void); void portB_init(void);
extern void EnableInterrupts(void); // defined in startup.s
extern void WaitForInterrupt(void); // defined in startup.s
void flash(void);
void adjustmotorout(void);

// global variables
volatile uint8_t sw1 = 0;
volatile uint8_t sensor = 0;
volatile uint8_t sensor_flag = 0;
volatile uint16_t systick_count = 0;
volatile uint8_t isflashing = 0;
uint8_t CS = green;
volatile uint8_t motorout = 0x6; // 0110

int main(void)
{
    portF_init(); portB_init();
    EnableInterrupts();
    // infinite loop
    while(1)
    {
        if(!isflashing)
        {
            if(CS == green)
                *(F_GPIODATA + Pin3_1) = 0x8/*0_1000*/;
            else if(CS == blue)
                *(F_GPIODATA + Pin3_1) = 0x4/*0_0100*/;
        }
        
        if(sensor_flag)
        {
            sensor_flag = 0;
            sw1 = 0;
            if(!isflashing)
            {
                if(CS == green)
                {
                    if(sensor)
                    {
                        CS = blue;
                        flash();
                    }
                }else if(CS == blue)
                {
                    if(!sensor)
                    {
                        CS = green;
                        flash();
                    }
                }
            }
        }
        if(sw1)
        {
            sw1 = 0;
            if(!isflashing)
            {
                if(CS == green)
                    CS = blue;
                else if(CS == blue)
                    CS = green;
                flash();
            }
        }
    }
}

/*
Starts the LED flashing process (raises flag,
turns off LED, starts timer).
*/
void flash(void)
{
    isflashing = 1;
    *(F_GPIODATA + Pin3_1) &= 0x11; // lights off 1_0001
    motorout = 0x2;
    //*(B_GPIODATA + MotorOutPins) = 0xC;
    systick_init(80000); // turn timer on, 5 ms
}

/*
Simple implementation of a wrap-around
left-shift and right-shift based on current state.
*/
void adjustmotorout(void)
{
    if(CS == green)
    {
        motorout >>= 1;
        if(motorout == 0x0)
            motorout = 0x8;
    }
    else if(CS == blue)
    {
        motorout <<= 1;
        if(motorout == 0x10)
            motorout = 0x01;
    }
}

/*
Initializes SysTick timer and interrupt to
trigger at whichever time the user desires.
Run at startup.
*/
void systick_init(uint32_t cycles)
{
    STCURRENT = 0x00;      // clear current and count values
    STCTRL   &= 0x00;      // clear all
    STCTRL   |= 0x04;      // enable system clock
    STCTRL   |= 0x02;      // enable interrupt
    STRELOAD  = cycles - 1;

    *((volatile unsigned long *) 0xE000E408) /*PRI3*/ &= 0x1FFFFFFF; // clear three MSBs, priority 0
    STCTRL |= 0x01; // start timer
    STCURRENT = 0x00; // clear current and count values
}

/*
Initializes Port F.
Run at startup.
*/
void portF_init(void)
{
    RCGC2 |= 0x20; // 10_0000
    while((RCGC2 & 0x20) != 0x20); // wait for clock to enable
    
    // data initialization
    F_GPIODIR |= ~Pin4; // I_OOOO
    F_GPIOPUR |= Pin4; // 1_0000
    F_GPIODEN |= Pin4 | Pin3_1; // 1_1110
    
    // interrupt initialization
    F_GPIOIM  &= ~Pin4; // mask F[4] and F[0]
    F_GPIOIS  &= ~Pin4; // edge-triggered
    F_GPIOIBE &= ~Pin4; // not both edges
    F_GPIOIEV &= ~Pin4; // falling edge-triggered
    F_GPIOICR  =  Pin4; // clear bits in GPIORIS and GPIOMIS
    F_GPIOIM  |=  Pin4; // unmask F[4] and F[0]
    *((volatile unsigned long *) 0xE000E41C) /*PRI7*/ |= 0x400000; // priority 2
    *((volatile unsigned long *) 0xE000E100) /*EN0*/|= 0x40000000; // enable interrupt 30
}

/*
Initializes Port B.
Run at startup.
*/
void portB_init(void)
{
    RCGC2 |= 0x02; // 00_0010
    while((RCGC2 & 0x02) != 0x02); // wait for clock to enable
    
    // data
    B_GPIODIR &= ~Pin0; // ----_---I
    B_GPIODIR  |= 0xF0; // OOOO_----
    B_GPIODEN  |= 0xF0 | Pin0; // 1111_0001
    B_GPIODR8R |= 0xF0; // 1111_0000
    
    // interrupt
    B_GPIOIM  &= ~Pin0; // mask B[0]
    B_GPIOIS  &= ~Pin0; // edge-sensitive trigger
    B_GPIOIBE |=  Pin0; // both edges
    //B_GPIOIEV &= ~Pin0; // falling edge
    B_GPIOICR  =  0xFF; // clear GPIORIS
    B_GPIOIM  |=  Pin0; // unmask B[0]
    
    *((volatile unsigned long *) 0xE000E400) |= /*PRI0*/0x2000; // Priority 1
    *((volatile unsigned long *) 0xE000E100) |= /*EN0*/0x2; // Interrupt 1
}

/*
Port F ISR.
*/
void GPIOPortF_Handler(void)
{
    uint16_t i; for(i = 0; i < debouncedelaytime; i++); // delay
    F_GPIOICR = Pin4; // acknowledge and clear interrupt flag
    sw1 = 1; // set flag
}

/*
Port B ISR. Only fully runs if
the system is not in its flashing state.
*/
void GPIOPortB_Handler(void)
{
    B_GPIOICR = Pin0;
    if(!isflashing)
    {
    sensor_flag = 1;
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
}

/*
SysTick ISR. Contains various checks at different
frequencies in order to implement different timings
for different operations.
*/
void SysTick_Handler(void)
{
    systick_count++;
    STCURRENT = 0;

    // Red LED flash
    if(systick_count % 50 == 0) // 4 Hz
        *(F_GPIODATA + Pin3_1) ^= 0x02;

    // motor output adjustment
    if(systick_count % 1 == 0) // 100 Hz
    {
        *(B_GPIODATA + MotorOutPins) = motorout << 4;
        // << 4 necessary because the motor is connected to the most significant 4 bits of the port
        adjustmotorout();
    }

    // end timer after 5 s
    if(systick_count >= 1000)
    {
        STCTRL &= ~0x01; // turn timer off
        systick_count = 0;
        isflashing = 0;
    }
}

