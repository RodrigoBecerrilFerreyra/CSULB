// Documentation
// CECS346 Lab 2 - Switch and LED Interface
// Description: Getting to know your board by connecting switches and LEDs.
// Student Name: Rodrigo Becerril Ferreyra

// Input/Output:
//   PE0 - Input  - SW1
//   PE1 - Input  - SW2
//   PB0 - Output - LED_G
//   PB1 - Output - LED_Y
//   PB2 - Output - LED_R

// Preprocessor Directives
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

// 1. Pre-processor Directives Section
// Constant declarations to access port registers using 
// symbolic names instead of addresses

// PORT E register definitions
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *) 0x400243FC ))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *) 0x40024400 ))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *) 0x40024420 ))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *) 0x4002451C ))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *) 0x40024528 ))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *) 0x4002452C ))
//#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *) 0x40024520 ))
//#define GPIO_PORTE_CR_R         (*((volatile unsigned long *) 0x4002441C ))
// No unlocking of GPIOCR needed

// PORT B register definitions
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *) 0x400053FC ))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *) 0x40005400 ))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *) 0x40005420 ))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *) 0x4000551C ))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *) 0x40005528 ))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *) 0x4000552C ))
//#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *) 0x40005520 ))
//#define GPIO_PORTB_CR_R         (*((volatile unsigned long *) 0x4000541C ))
// No unlocking of GPIOCR needed

// system control register RCGC2 definition
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *) 0x400FE108 ))

// define constants and aliases         0 = in, 1 = out, x = don't care (output)
#define LIGHT       GPIO_PORTB_DATA_R //8'bxxxxx111
#define SW          GPIO_PORTE_DATA_R //8'bxxxxxx00
#define SW1_MASK 	0x01        // E[0] for switch 1
#define SW2_MASK 	0x02        // E[1] for switch 2
#define RED         0x04        // B[2] for red LED
#define YELLOW      0x02        // B[1] for yellow LED
#define GREEN       0x01        // B[0] for green LED
#define OFF         0x00        // B[7:0] is cleared

// Function Prototypes - Each subroutine defined
void Delay(uint8_t n_50ms);
void PortB_Init(void);
void PortE_Init(void);

int main(void) {
    // Initialize GPIO Ports B, E
    PortB_Init();
    PortE_Init();
    // Initial state: Green LED on, the other two LEDs off
    LIGHT = GREEN;
    uint8_t currentState;

    while(1) {
        Delay(1);
		
        // Check the following conditions and set Out appropriately:
        // If the sw1 is pressed, the currently on LED will be turned off, the next LED will be turned on. 
        // If sw2 is pressed, currently on LED will flash at a speed of 50 ms.
        // If both sw1 and sw2 are pressed, current led will flash once at a speed of 50 ms 
        //    and then move to the next one.

        uint8_t sw1 = SW & SW1_MASK;
        uint8_t sw2 = SW & SW2_MASK;
        if(sw1)
        {
            Delay(1);
            if(LIGHT & GREEN)
            {
                LIGHT &= ~GREEN; //turn green off
                LIGHT |= YELLOW; //turn yellow on
            }else if(LIGHT & YELLOW)
            {
                LIGHT &= ~YELLOW; //turn yellow off
                LIGHT |= RED; //turn red on
            }else if(LIGHT & RED)
            {
                LIGHT &= ~RED; //turn red off
                LIGHT |= GREEN; //turn green on
            }else
            {
                LIGHT = OFF;
                LIGHT = GREEN;
            }
        }
        if(sw2)
        {
            currentState = LIGHT;
            LIGHT = OFF;
            Delay(1);
            LIGHT = currentState;
        }
	}
}

// Subroutine to initialize port B pins for output
// PB2,PB2,PB0 are outputs for red, green, and yellow LEDs
// Inputs: None
// Outputs: None
void PortB_Init(void)
{
    SYSCTL_RCGC2_R |= 0x00000002;                    // activate B clock
    while ((SYSCTL_RCGC2_R&0x00000002)!=0x00000002); // wait for the clock to be ready

    //GPIO_PORTB_LOCK_R = 0x4C4F434B;       // unlock Port B
    //GPIO_PORTB_CR_R |= 0x07;              // allow changes to B[2:0]
    // No unlocking of GPIOCR needed
    GPIO_PORTB_AMSEL_R &= ~0xFF;          // disable analog function
    GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;     // GPIO clear bit PCTL
    GPIO_PORTB_DIR_R |= 0xFF;             // B[7:0] outputs
    GPIO_PORTB_AFSEL_R &= ~0xFF;          // no alternate function
    GPIO_PORTB_DEN_R |= 0x07;             // enable digital pins B[2:0]
}

// Subroutine to initialize port E pins PE0 & PE1 for input
// Inputs: None
// Outputs: None
void PortE_Init(void)
{
    SYSCTL_RCGC2_R |= 0x00000010;         // activate E clock
    while ((SYSCTL_RCGC2_R&0x00000010)!=0x00000010); // wait for the clock to be ready

    //GPIO_PORTE_LOCK_R = 0x4C4F434B;       // unlock Port E
    //GPIO_PORTE_CR_R |= 0x03;              // allow changes to E[1:0]
    // No unlocking of GPIOCR needed
    GPIO_PORTE_AMSEL_R &= ~0x3F;          // disable analog function
    GPIO_PORTE_PCTL_R &= ~0x00FFFFFF;     // GPIO clear bit PCTL
    GPIO_PORTE_DIR_R &= ~0x03;            // E[1:0] input
    GPIO_PORTE_DIR_R |= ~0x03;            // E[7:2] outpu
    GPIO_PORTE_AFSEL_R &= ~0x3F;          // no alternate function
    GPIO_PORTE_DEN_R |= 0x03;             // enable digital pins E[1:0]
}


// Subroutine to wait about 0.05 sec
// Inputs: uint8_t n_50ms - amount of time to wait in the form of n(50 ms)
// Outputs: None
// Notes: the Keil simulation runs slower than the real board
void Delay(uint8_t n_50ms)
{
    uint8_t loops; volatile unsigned long time;
    for(loops = 0; loops < n_50ms; loops++)
    {
        time = 727240*10/9;
        while(time > 0){time--;} //~50 ms
    }
}

