/**
 * Filename: portal.c
 * Draws a looping person passing through portals (as seen in
 * Valve's Portal series of video games) on the ST7735 128x160 px
 * color LCD screen (pinouts below).
 * @author Rodrigo Becerril Ferreyra
 */

/* List of connections from the ST7735 to the Lauchpad
 * Pin#->Name  -> Launchpad Pin
 * 1  -> GND   -> GND
 * 2  -> VCC   -> +3.3V
 * 3  -> NC
 * 4  -> NC
 * 5  -> NC
 * 6  -> RESET -> PA7
 * 7  -> A0    -> PA6
 * 8  -> SDA   -> PA5
 * 9  -> SCL   -> PA2
 * 10 -> CS    -> PA3
 * 11 -> SCK
 * 12 -> MISO
 * 13 -> MOSI
 * 14 -> SC_CS
 * 15 -> LED+  -> +3.3V
 * 16 -> LED-
 */

#include <stdint.h>       // for precise number sizes
#include "tm4c123gh6pm.h" // easy access to memory-mapped IO
#include "ST7735.h"       // driver functions for LCD
#include "PLL.h"          // for setting MCU to 80 MHz

// some macros to simplify math
#define middlevert 64
#define middlehoriz 80
#define upperlimit 48
#define lowerlimit 156
#define frombottom(x) (159 - (x))
#define fromright(x) (127 - (x))
#define fromUpperLimit(x) (upperlimit + (x))
#define fromLowerLimit(x) (lowerlimit - (x))
#define holdTime 5500

void systickInit(void);
void systickWait(const uint32_t ms);

typedef struct Cursor
{
    uint8_t x;
    uint8_t y;
} Cursor;

int main(void)
{
    // initialize
    PLL_Init(12);
    ST7735_InitR(INITR_REDTAB);
    Cursor man;
    const uint16_t ST7735_ORANGE = ST7735_Color565(0xFF, 0x67, 0);

    // draw the background
    ST7735_FillScreen(ST7735_BLACK);
    
    // draw a textbox on the top
    ST7735_FillRect(0, 0, 128, 45, ST7735_WHITE);

    // write some text in textbox
    ST7735_DrawString(1, 1, "Now you're thinking", ST7735_BLACK);
    ST7735_DrawString(1, 2, "with", ST7735_BLACK);
    for(int i = 0; i < 7; ++i) // 7 is the length of "PORTALS" without '\0'
        ST7735_DrawCharS(13*i + 32, 21, "PORTALS"[i], i & 1 ? ST7735_BLUE : ST7735_ORANGE, ST7735_WHITE, 2);
        // Explanation:
        // The last parameter in this function call is 2, which means that each
        // pixel thatis usually drawn as 1x1 px is drawn as 2x2 px. At size 1,
        // each letter is usually 5x7, but this time each letter is 10x14.
        // Therefore, each letter must be drawn 14 pixels away from the start of
        // the previous letter (which would be 14*i). I reduced this to 13*i to
        // make the letters closer together. I hope that the compiler optimizes
        // the multiplication by loop unrolling.
        //
        // The +32 in the first argument corresponds to the offset from the left
        // of the screen where the string "PORTALS" should start.
        //
        // The 21 in the second parameter is actually 3*7. Recall that each
        // letter on size 1 is 7 pixels tall. I have 7 pixels of blank space
        // and 7 pixels of text, so the new word should be on the third line.
        //
        // The antepenultimate parameter simply alternates between orange and
        // blue for the letters in "PORTAL".

    // draw the blue portal (just an orange rectangle)
    ST7735_FillRect(10, 45, 108, 3, ST7735_BLUE);

    // draw the orange portal
    ST7735_FillRect(10, 157, 108, 3, ST7735_ORANGE);

    man.x = middlevert;
    // controls the movement of the person
    while(1)
    {
        // first, draw head on bottom, body on top.
        // set coordinates for original position
        man.y = upperlimit;

        ST7735_DrawCircle(middlevert, frombottom(18), 15, ST7735_WHITE); // head
        ST7735_DrawLine(man.x, man.y, man.x, man.y+30, ST7735_WHITE); // body
        man.y += 10; // move cursor to the middle of the body
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_WHITE); // right arm
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_WHITE); // left  arm
        man.y += 20; // move cursor to the end of the body
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_WHITE); // right leg
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_WHITE); // left  leg

        systickWait(holdTime);

        // erase the stick figure by doing the exact same operation but with color black
        man.y = upperlimit;
        ST7735_DrawCircle(middlevert, frombottom(18), 15, ST7735_BLACK); // head
        ST7735_DrawLine(man.x, man.y, man.x, man.y+30, ST7735_BLACK); // body
        man.y += 10; // move cursor to the middle of the body
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_BLACK); // right arm
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_BLACK); // left  arm
        man.y += 20; // move cursor to the end of the body
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_BLACK); // right leg
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_BLACK); // left  leg

        // draw the whole stick figure several times going down
        for(int i = 0; i < 8; ++i)
        {
            // next, draw the whole man with his head touching the blue portal
            ST7735_DrawCircle(middlevert, fromUpperLimit(15 + (i*5)), 15, ST7735_WHITE);
            man.y = fromUpperLimit(15 + (i*5)) + 15;
            ST7735_DrawLine(man.x, man.y, man.x, man.y+30, ST7735_WHITE); // body
            man.y += 10; // move cursor to the middle of the body
            ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_WHITE); // right arm
            ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_WHITE); // left  arm
            man.y += 20; // move cursor to the end of the body
            ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_WHITE); // right leg
            ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_WHITE); // left  leg

            systickWait(holdTime);

            // erase previous drawing
            ST7735_DrawCircle(middlevert, fromUpperLimit(15 + (i*5)), 15, ST7735_BLACK);
            man.y = fromUpperLimit(15 + (i*5)) + 15;
            ST7735_DrawLine(man.x, man.y, man.x, man.y+30, ST7735_BLACK); // body
            man.y += 10; // move cursor to the middle of the body
            ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_BLACK); // right arm
            ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_BLACK); // left  arm
            man.y += 20; // move cursor to the end of the body
            ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_BLACK); // right leg
            ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_BLACK); // left  leg
        }

        // draw the head and body on the bottom and the legs on top
        ST7735_DrawLine(man.x, upperlimit, man.x+10, upperlimit+10, ST7735_WHITE); // right leg
        ST7735_DrawLine(man.x, upperlimit, man.x-10, upperlimit+10, ST7735_WHITE); // left  leg

        man.y = fromLowerLimit(20);
        ST7735_DrawCircle(man.x, man.y-15, 15, ST7735_WHITE); // head
        ST7735_DrawLine(man.x, man.y, man.x, man.y+20, ST7735_WHITE); // body
        man.y += 10;
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_WHITE); // right arm
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_WHITE); // left  arm

        systickWait(holdTime);

        // delete above image
        ST7735_DrawLine(man.x, upperlimit, man.x+10, upperlimit+10, ST7735_BLACK); // right leg
        ST7735_DrawLine(man.x, upperlimit, man.x-10, upperlimit+10, ST7735_BLACK); // left  leg

        man.y = fromLowerLimit(20);
        ST7735_DrawCircle(man.x, man.y-15, 15, ST7735_BLACK); // head
        ST7735_DrawLine(man.x, man.y, man.x, man.y+20, ST7735_BLACK); // body
        man.y += 10;
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_BLACK); // right arm
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_BLACK); // left  arm

        // the last image is the figure with half his body on top
        // and the other half on bottom
        man.y = fromLowerLimit(10);
        ST7735_DrawCircle(man.x, man.y-15, 15, ST7735_WHITE); // head
        ST7735_DrawLine(man.x, man.y, man.x, man.y+10, ST7735_WHITE); // body (top half)
        man.y = upperlimit; // go to top
        ST7735_DrawLine(man.x, man.y, man.x, man.y+20, ST7735_WHITE); // body (bottom half)
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_WHITE); // right arm
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_WHITE); // left  arm
        man.y += 20;
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_WHITE); // right leg
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_WHITE); // left  leg

        systickWait(holdTime);

        // delete prev image
        man.y = fromLowerLimit(10);
        ST7735_DrawCircle(man.x, man.y-15, 15, ST7735_BLACK); // head
        ST7735_DrawLine(man.x, man.y, man.x, man.y+10, ST7735_BLACK); // body (top half)
        man.y = upperlimit; // go to top
        ST7735_DrawLine(man.x, man.y, man.x, man.y+20, ST7735_BLACK); // body (bottom half)
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_BLACK); // right arm
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_BLACK); // left  arm
        man.y += 20;
        ST7735_DrawLine(man.x, man.y, man.x+10, man.y+10, ST7735_BLACK); // right leg
        ST7735_DrawLine(man.x, man.y, man.x-10, man.y+10, ST7735_BLACK); // left  leg
    }
}

void systickInit(void)
{
    // stop the timer before setting registers
    NVIC_ST_CTRL_R &= ~0x1;
    // set reload to 1 ms
    // 80 MHz / (1/1 ms) = 80000
    NVIC_ST_RELOAD_R = 80000 - 1;
    // clear the current value
    NVIC_ST_CURRENT_R = 0;
    // use system clock and no interrupt
    NVIC_ST_CTRL_R |= 0x4;
    // note that the timer is not started in this function
}

/**
 * Initializes SysTick hardware timer to pre-configured parameters.
 * Assumes an 80 MHz system clock.
 * @author Rodrigo Becerril Ferreyra
 */
void systickWait(const uint32_t ms)
{
    for(uint32_t i = 0; i < ms; ++i)
    {
        // clear count and start the timer
        NVIC_ST_CURRENT_R = 0;
        NVIC_ST_CTRL_R |= 0x01;
        // wait until the timer is finished
        while(NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT);
        // stop the timer and clear count
        NVIC_ST_CTRL_R &= ~0x01;
        NVIC_ST_CURRENT_R = 0;
    }
}
