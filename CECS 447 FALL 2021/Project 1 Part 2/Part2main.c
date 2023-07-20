/*
Author: Rodrigo Becerril Ferreyra
Name: Project 1: Music Box
Version: 3
Short Description:
    This project has two modes: it either plays three songs in order
    (music box mode), or it allows the user to play four notes on a
    push button keyboard.
*/

#include "tm4c123gh6pm.h"
#include <stdint.h>

// These are indexes for the note table
#define C   0
#define D   1
#define E   2
#define F   3
#define G   4
#define A   5
#define B   6
// xva means one octave above x (8va)
#define Cva 7
#define Dva 8
#define Eva 9
#define Fva 10
#define Gva 11
#define Ava 12
#define Bva 13

#define sp 254 // sp means "short pause"
#define PAUSE 255 // a rest or silence

// Each note has a letter and a hold value
// (the value that goes into the SysTick reload register).
typedef struct
{
    uint8_t note;
    uint8_t hold_value;
}
Note;

extern void EnableInterrupts(void);
void delay(void);
void play_song(const Note[], uint16_t, uint8_t);

/*
const uint32_t notetable[4][7] =
{//   C    D    E    F    G    A    B
    {956, 851, 758, 716, 638, 568, 506},
    {478, 425, 379, 358, 319, 284, 253},
    {239, 213, 189, 179, 159, 142, 126},
    {119, 106,  95,  89,  79,  71,  63}
};
*/
const uint32_t notetable[4][7] =
{
    {122137,108844,96970,91429,81633,72727,64777},   // C3 Major notes
    {30534*2,27211*2,24242*2,22923*2,20408*2,18182*2,16194*2}, // C4 Major notes
    {15289*2,13621*2,12135*2,11454*2,10204*2,9091*2,8099*2}, // C5 Major notes
    {7645*2,6810*2,6067*2,5727*2,5102*2,4545,4050*2} // C6 Major notes
    //{122137/2,108844/2,96970/2,91429/2,81633/2,72727/2,64777/2},
    //{122137/4,108844/4,96970/4,91429/4,81633/4,72727/4,64777/4},
    //{122137/8,108844/8,96970/8,91429/8,81633/8,72727/8,64777/8}
};

// saw wave
//const uint8_t outwave[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
// sine wave
const uint8_t outwave[] = {31, 34, 37, 40, 43, 46, 48, 51, 53, 55, 57, 59, 60, 61, 62, 62, 62, 62, 61, 60, 59, 58, 56, 54, 52, 50, 47, 44, 42, 39, 36, 33, 29, 26, 23, 20, 18, 15, 12, 10, 8, 6, 4, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 5, 7, 9, 11, 14, 16, 19, 22, 25, 28};

volatile uint8_t current_output = 0; // index for outwave
volatile uint8_t play_mode = 0; // 0 = piano, 1 = music box
volatile uint8_t octave = 0; // which octave to play on (0, 1, or 2)
volatile uint8_t song_select = 0; // which song to play (0, 1, or 2)

int main(void)
{
    // initialize ports A (output), D (input), and F (on-board button interrupts)

    SYSCTL_RCGC2_R |= 0x29; // enable ports A, D, and F
    while((SYSCTL_RCGCGPIO_R & 0x29) != 0x29);

    // Port A
    GPIO_PORTA_DIR_R |= 0xFC;  // A[7:2] are output bits
    GPIO_PORTA_AFSEL_R &= ~0xFC;
    GPIO_PORTA_DR8R_R |= 0xFC;
    GPIO_PORTA_DEN_R |= 0xFC;
    //GPIO_PORTA_DATA_R &= ~0xFC; // clear output bits
    GPIO_PORTA_DATA_R = outwave[current_output] << 2;
    
    // Port D
    GPIO_PORTD_DIR_R &= ~0x0F; // D[3:0] are inputs
    GPIO_PORTD_AFSEL_R &= ~0x0F;
    //GPIO_PORTD_PDR_R |= 0x0F; // positive logic for buttons
    GPIO_PORTD_DEN_R |= 0x0F;

    // Port F
    do{GPIO_PORTF_LOCK_R = 0x4C4F434B;} while((GPIO_PORTF_LOCK_R & 0x1) == 0x1);
    GPIO_PORTF_CR_R |= 0x13; // unlock several registers
    do{GPIO_PORTF_LOCK_R = 0;} while((GPIO_PORTF_LOCK_R & 0x1) == 0x0);
    GPIO_PORTF_DIR_R &= ~0x11; // input
    GPIO_PORTF_DIR_R |= 0x06; //output
    GPIO_PORTF_AFSEL_R &= ~0x17;
    GPIO_PORTF_PUR_R |= 0x11;
    GPIO_PORTF_DEN_R |= 0x17;
    GPIO_PORTF_DATA_R &= ~0x06; // clear led

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

    //Note major_scale[] = {C, 2, D, 2, E, 2, F, 2, G, 2, A, 2, B, 2, Cva, 2};
    Note twinkle_twinkle[] =
    {
        C,4, sp,0, C,4, G,4, sp,0, G,4, A,4, sp,0, A,4, G,4, PAUSE, 4, F,4, sp,0, F,4, E,4, sp,0, E,4, D,4, sp,0, D,4, C,4, PAUSE,4,
        G,4, sp,0, G,4, F,4, sp,0, F,4, E,4, sp,0, E,4, D,4, PAUSE,4, G,4, sp,0, G,4, F,4, sp,0, F,4, E,4, sp,0, E,4, D,4, PAUSE,4,
        C,4, sp,0, C,4, G,4, sp,0, G,4, A,4, sp,0, A,4, G,4, PAUSE, 4, F,4, sp,0, F,4, E,4, sp,0, E,4, D,4, sp,0, D,4, C,4
    };
    Note marry_had_a_little_lamb[] =
    {
        E,4, D,4, C,4, D,4, E,4, sp,0, E,4, sp,0, E,8,
        D,4, sp,0, D,4, sp,0, D,8, E,4, G,4, sp,0, G,8,
        E,4, D,4, C,4, D,4, E,4, sp,0, E,4, sp,0, E,4, sp,0, E,4,
        D,4, sp,0, D,4, E,4, D,4, C, 8
    };
    Note happy_birthday[] =
    {
        G,2, sp,0, G,2, A,4, G,4, Cva,4, B,4, PAUSE,4,
        G,2, sp,0, G,2, A,4, G,4, Dva,4, Cva,4, PAUSE,4,
        G,2, sp,0, G,2, Gva,4, Eva,4, Cva,4, B,4, A,8, PAUSE,4,
        Fva,2, sp,0, Fva,2, Eva,4, Cva,4, Dva,4, Cva,8,
    };

    uint8_t piano_input;
    while(1)
    {
        if(play_mode) // if music box mode
        {
            GPIO_PORTF_DATA_R |= 0x02;  // red LED on
            GPIO_PORTF_DATA_R &= ~0x04; // blue LED off
            switch(song_select)
            {
                case 0:
                    play_song(happy_birthday, sizeof(happy_birthday)/sizeof(happy_birthday[0]), song_select);
                    break;
                case 1:
                    play_song(marry_had_a_little_lamb, sizeof(marry_had_a_little_lamb)/sizeof(marry_had_a_little_lamb[0]), song_select);
                    break;
                case 2:
                    play_song(twinkle_twinkle, sizeof(twinkle_twinkle)/sizeof(twinkle_twinkle[0]), song_select);
                    break;
                default:
                    song_select = 0;
            }
        }
        else // if piano mode
        {
            GPIO_PORTF_DATA_R &= ~0x02; // red LED off
            GPIO_PORTF_DATA_R |= 0x04;  // blue LED on
            piano_input = GPIO_PORTD_DATA_R & 0x0F; // read LS 4 bits (positive logic)

            if(!piano_input) // if no buttons are selected
            {
                NVIC_ST_CTRL_R &= ~0x01; // stop timer
                NVIC_ST_CURRENT_R = 0; // clear count
                continue;
            }

            if(piano_input & 0x01)      // C
                NVIC_ST_RELOAD_R = (notetable[octave][C])/64;
            else if(piano_input & 0x02) // D
                NVIC_ST_RELOAD_R = (notetable[octave][D])/64;
            else if(piano_input & 0x04) // E
                NVIC_ST_RELOAD_R = (notetable[octave][E])/64;
            else if(piano_input & 0x08) // F
                NVIC_ST_RELOAD_R = (notetable[octave][F])/64;
            
            // start timer
            NVIC_ST_CTRL_R |= 0x01;
        }
    }
}

/**
* Plays a song from an array of Note structs.
* @param song[] The song to play.
* @param length_of_song The amount of notes in the song.
* @param old_song_select The number of the song (song 0, song 1, or song 2).
This will be compared to the current song number to see if it has changed since
the function was called.
*/
void play_song(const Note song[], uint16_t length_of_song, uint8_t old_song_select)
{
    uint8_t i, j, k;
    // Plays until the song is over without needing a special end Note.
    for(i = 0; i < length_of_song; ++i)
    {
        if(song[i].hold_value == PAUSE)
        {
            NVIC_ST_CTRL_R &= ~0x01; // silence tone, turn off SysTick timer
        }
        else // play a regular Note
        {
            NVIC_ST_CURRENT_R = 0; // clear count
            if(song[i].note == sp) // pause note
            {
                delay(); // ~0.25 s delay
                continue; // continue skips the hold time and goes on to the next Note.
            }
            else // normal Note
            {
                // if the note is greater than 6, then play the same note in a higher octave
                // else, play the Note normally
                NVIC_ST_RELOAD_R = (song[i].note >= 7) ? (notetable[octave + 1][song[i].note - 7])/64 : (notetable[octave][song[i].note])/64;
                NVIC_ST_CTRL_R |= 0x01; // start timer
            }
        }
        
        // tempo control
        // play current note for specified duration
        for(k = 0; k < 4; ++k) // actually four times longer than hold value
        {
            for (j = 0; j < song[i].hold_value; ++j)
            {
                // logic to stop playing Note if a global variable is changed
                // if the song select value has changed or the play mode changes to piano mode:
                if(song_select != old_song_select || !play_mode)
                {
                    NVIC_ST_CTRL_R &= ~0x01; // stop timer
                    NVIC_ST_CURRENT_R = 0; // clear count
                    return;
                }
                delay();
            }
		}

		NVIC_ST_CTRL_R &= ~0x01;
    }
    
    // pause after each play
	for (j = 0;j < 40;++j)
    {
		delay();
    }
}

/**
* Handles output generation.
*/
void SysTick_Handler(void)
{
    NVIC_ST_CTRL_R &= ~0x01; // stop timer
    
    // increment one, and loop back at 64
    current_output = (current_output >= 63) ? 0 : current_output + 1;
    // We need to lshft 2 because the outputs are A[7:2].
    GPIO_PORTA_DATA_R = outwave[current_output] << 2;
    
    // clear count value and restart timer
    NVIC_ST_CURRENT_R = 0; NVIC_ST_CTRL_R |= 0x01;
}

void GPIOPortF_Handler(void)
{
    for(uint16_t debounce = 0; debounce < 65534; ++debounce);
    switch(GPIO_PORTF_MIS_R & 0x11)
    {
        case 0x10: // left switch (SW1)
            GPIO_PORTF_ICR_R = 0x10;
            play_mode = !play_mode;
            break;
        case 0x01: // right switch (SW2)
            GPIO_PORTF_ICR_R = 0x01;
            if(play_mode) // if play_mode is in music box mode
            {
                // change song
                song_select = (song_select >= 2) ? 0 : song_select + 1;
            }
            else // if play_mode is in piano mode
            {
                // change octave
                octave = (octave >= 2) ? 0 : octave + 1;
            }
            break;
        default:
            GPIO_PORTF_ICR_R = 0x11;
    }
}

/**
* Delays the program for approximately 0.25 s
*/
void delay(void)
{
    for(volatile uint32_t time = 39958; time > 0; --time);
    // (727240*20/91)/4 = 39958
}
