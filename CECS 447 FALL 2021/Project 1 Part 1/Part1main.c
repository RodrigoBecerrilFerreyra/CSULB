/*
Author: Rodrigo Becerril Ferreyra
Name: Project 1: Music Box
Version: 2
Short Description:
    Plays three different songs.
*/

#include "tm4c123gh6pm.h"
#include <stdint.h>

#define C4 0
#define D4 1
#define E4 2
#define F4 3
#define G4 4
#define A4 5
#define B4 6
#define C5 0+7
#define D5 1+7
#define E5 2+7
#define F5 3+7
#define G5 4+7
#define A5 5+7
#define B5 6+7
#define C6 0+14
#define D6 1+14
#define E6 2+14
#define F6 3+14
#define G6 4+14
#define A6 5+14
#define B6 6+14
#define shortpause 254
#define PAUSE 255

typedef struct
{
    uint16_t reload_value;
    uint8_t hold_value;
}
Note;

const uint16_t tones[] =
    {30534,27211,24242,22923,20408,18182,16194, // C4 Major notes
    15289,13621,12135,11454,10204,9091,8099, // C5 Major notes
    7645,6810,6067,5727,5102,4545,4050}; // C6 Major notes

Note songs[3][255] =
{{
// so                  so   la   so   doe' ti
   G5,2, shortpause, 1,G5,2,A5,4,G5,4,C6,4,B5,4,
// pause     so                  so   la   so   ray' doe'
   PAUSE,4,  G5,2, shortpause, 1,G5,2,A5,4,G5,4,D6,4,C6,4,
// pause    so                  so   so'  mi'  doe' ti   la
   PAUSE,4, G5,2, shortpause, 1,G5,2,G6,4,E6,4,C6,4,B5,4,A5,8, 
// pause     fa'                 fa'   mi'  doe' ray' doe'  stop
   PAUSE,4,  F6,2, shortpause, 1,F6,2, E6,4,C6,4,D6,4,C6,8, 0,0
},
{E6, 4, D6, 4, C6, 4, D6, 4, E6, 4, shortpause, 1, E6, 4, shortpause, 1, E6, 8,
 D6, 4, shortpause, 1, D6, 4, shortpause, 1, D6, 8, E6, 4, shortpause, 1, G6, 4, shortpause, 1, G6, 8,
 E6, 4, D6, 4, C6, 4, D6, 4, E6, 4, shortpause, 1, E6, 4, shortpause, 1, E6, 4, shortpause, 1, E6, 4,
 D6, 4, shortpause, 1, D6, 4, E6, 4, D6, 4, C6, 8, 0, 0 },

{C6,4, shortpause, 1,C6,4,G6,4, shortpause, 1,G6,4,A6,4, shortpause, 1,A6,4,G6,8,F6,4, shortpause, 1,F6,4,E6,4, shortpause, 1,E6,4,D6,4, shortpause, 1,D6,4,C6,8, 
 G6,4, shortpause, 1,G6,4,F6,4, shortpause, 1,F6,4,E6,4, shortpause, 1,E6,4,D6,8,G6,4, shortpause, 1,G6,4,F6,4, shortpause, 1,F6,4,E6,4, shortpause, 1,E6,4,D6,8, 
 C6,4, shortpause, 1,C6,4,G6,4, shortpause, 1,G6,4,A6,4, shortpause, 1,A6,4,G6,8,F6,4, shortpause, 1,F6,4,E6,4, shortpause, 1,E6,4,D6,4, shortpause, 1,D6,4,C6,8,0,0}};
    
extern void EnableInterrupts(void);
void delay(void);
void play_song(Note[], uint8_t);

volatile uint8_t master_play_control = 0;
volatile uint8_t song_select = 0;

int main(void)
{
    // initialize ports A (output) and F (on-board button interrupts)

    SYSCTL_RCGC2_R |= 0x21; // enable ports A and F
    while((SYSCTL_RCGCGPIO_R & 0x21) != 0x21);

    // Port A
    GPIO_PORTA_DIR_R |= 0x80;  // output
    GPIO_PORTA_AFSEL_R &= ~0x80;
    GPIO_PORTA_DR8R_R |= 0x80;
    GPIO_PORTA_DEN_R |= 0x80;
    GPIO_PORTA_DATA_R &= ~0x80; // clear output bit

    // Port F
    do{GPIO_PORTF_LOCK_R = 0x4C4F434B;} while((GPIO_PORTF_LOCK_R & 0x1) == 0x1);
    GPIO_PORTF_CR_R |= 0x13; // unlock several registers
    do{GPIO_PORTF_LOCK_R = 0;} while((GPIO_PORTF_LOCK_R & 0x1) == 0x0);
    GPIO_PORTF_DIR_R &= ~0x11; // input
    GPIO_PORTF_DIR_R |= 0x02; //output
    GPIO_PORTF_AFSEL_R &= ~0x13;
    GPIO_PORTF_PUR_R |= 0x11;
    GPIO_PORTF_DEN_R |= 0x13;
    GPIO_PORTF_DATA_R &= ~0x02; // clear led

    // initialize port f interrupts as recommended by datasheet
    GPIO_PORTF_IM_R &= ~0x11;
    GPIO_PORTF_IS_R &= ~0x11;
    GPIO_PORTF_IS_R &= ~0x11;
    GPIO_PORTF_IEV_R &= ~0x11; // falling edge-triggered
    GPIO_PORTF_ICR_R = 0x11;
    GPIO_PORTF_IM_R |= 0x11;

    NVIC_PRI7_R &= ~0x00E00000; // Clear INTC field
    NVIC_PRI7_R |= 0x00200000; // Set priority to 1
    NVIC_EN0_R |= 0x40000000; // enable bit 30 (port f) interrupt

    // Enable SysTick
    NVIC_ST_CTRL_R = 0x6;
    NVIC_ST_CURRENT_R = 0;
    NVIC_PRI3_R &= ~0xE0000000; // clear INTD field (priority 0)
    NVIC_EN0_R |= 0x00008000; // enable bit 15 (systick) interrupt
    EnableInterrupts();

    while(1)
    {
        if(master_play_control)
            play_song(songs[song_select], song_select);
    }
}

void play_song(Note song[], uint8_t whichsong)
{
	uint8_t i=0, j;

	while (song[i].hold_value) { // delay==0 indicate end of the song

		if (song[i].reload_value==PAUSE) // index = 255 indicate a pause: stop systick
			NVIC_ST_CTRL_R &= ~0x01; // silence tone, turn off SysTick timer
		else { // play a regular note
            if(song[i].reload_value == shortpause)
            {
                delay();
                i++;
                continue;
            }
            else
            {
                NVIC_ST_RELOAD_R = tones[song[i].reload_value];
                NVIC_ST_CTRL_R |= 0x01; // start timer
            }
		}
        
		// tempo control: 
		// play current note for specified duration
        for(uint8_t k = 0; k < 4; ++k)
        {
            // block of code that kills the song
            if((!master_play_control) || (whichsong != song_select))
            {
                NVIC_ST_CTRL_R &= ~0x01;// NVIC_ST_CURRENT_R = 0;
                GPIO_PORTA_DATA_R &= ~0x80;
                GPIO_PORTF_DATA_R &= ~0x02;
                break;
            }
            else
            {
                for (j=0;j<song[i].hold_value;j++)
                    delay();
            }
		}

		NVIC_ST_CTRL_R &= ~0x01;// NVIC_ST_CURRENT_R = 0;
		++i;  // move to the next note
	}
	
	// pause after each play
	for (j=0;j<40;j++)
		delay();
}

void SysTick_Handler(void)
{
    NVIC_ST_CTRL_R &= ~0x01;
    switch(GPIO_PORTA_DATA_R & 0x80)
    {
        case 0x80: // if on
            GPIO_PORTA_DATA_R &= ~0x80;
            GPIO_PORTF_DATA_R &= ~0x02;
            break;
        case 0x00: // if off
            GPIO_PORTA_DATA_R |= 0x80;
            GPIO_PORTF_DATA_R |= 0x02;
            break;
        default:
            GPIO_PORTA_DATA_R |= 0x80;
    }
    NVIC_ST_CURRENT_R = 0; NVIC_ST_CTRL_R |= 0x01;
}

void GPIOPortF_Handler(void)
{
    for(uint16_t debounce = 0; debounce < 65534; ++debounce);
    switch(GPIO_PORTF_MIS_R & 0x11)
    {
        case 0x10: // left switch (SW1)
            GPIO_PORTF_ICR_R = 0x10;
            master_play_control = !master_play_control;
            break;
        case 0x01: // right switch (SW2)
            GPIO_PORTF_ICR_R = 0x01;
            ++song_select;
            if(song_select > 2) song_select = 0;
            break;
        default:
            GPIO_PORTF_ICR_R = 0x11;
    }
}

// Delays the program for approximately 0.25 s
void delay(void)
{
    for(volatile uint32_t time = 39958; time > 0; --time);
    // (727240*20/91)/4 = 39958
}
