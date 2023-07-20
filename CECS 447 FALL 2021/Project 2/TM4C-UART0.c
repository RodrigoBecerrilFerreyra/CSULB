#include "TM4C-UART0.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

extern volatile uint8_t modechangeflag;

/**
 * Outputs a char to UART0 and waits for completion.
 * @param letter the char to output
 */
void outputChar(const char letter)
{
    UART0_DR_R = letter;
    while(UART0_FR_R & 0x20); // wait for TXFF in UARTDR to be cleared
}

/**
 * Outputs all the characters in a string to UART0 one by one.
 * Stops at the null terminator.
 * @param str the string (char array) to output.
 */
void outputString(const char* str)
{
    char charInQuestion;
    uint16_t i = 0;

    // this loop goes through all the characters in the string
    // until it hits the null terminator; then it breaks
    while(1)
    {
        charInQuestion = *(str + i);
        outputChar(charInQuestion);
        if(charInQuestion == '\0') {break;}
        ++i;
    }
}

/**
 * Simply outputs a new line consisiting of a
 * carriage return '\r' and a line feed '\n'
 */
void outputNewLine(void)
{
    outputChar('\r');
    outputChar('\n');
}

/**
 * Returns the penultimate character inputted by the user.
 * In other words, it returns the last character
 * Note: when the user enters a backspace and presses enter,
 * the character returned will be the last non-backspace character entered.
 * This is true for any number of backspaces.
 * @return The penultimate character inputted.
 */
char getInputChar(void)
{
    char currdata = '\0', prevdata = '\0';

    do
    {
        // wait until receiver is not empty (RXFE)
        while(UART0_FR_R & 0x10)
        {
            if(modechangeflag) {return '\0';}
        }
        prevdata = (currdata == 0x7F) ? prevdata : currdata; // do not save backspaces
        currdata = UART0_DR_R & 0xFF; // get input
        if(currdata != '\r') {outputChar(currdata);} // this means the enter key has not been pressed
    }
    while(currdata != '\r');

    // simulate the enter key being pressed
    outputNewLine();

    return prevdata;
}

/**
 * Gets the string the user inputted and saves it in str.
 * @param str The location of where to save the user input.
 * @param maxlen The length of str (number of characters + 1).
 */
void getInputString(char *str, int maxlen)
{
    char indata; uint16_t length = 0;
    do
    {
        // wait until receiver is not empty (RXFE)
        while(UART0_FR_R & 0x10)
        {
            if(modechangeflag)
            {
                *str = '\0';
                return;
            }
        }
        indata = UART0_DR_R & 0xFF; // read data

        if(indata == '\b')
        {
            --str; // go back one character
            if(length > 0) {--length;}
        }
        else if(indata != '\r' && length < maxlen) // does not save \r
        {
            ++length;
            *str = indata;
            ++str; // move to next character in array
        }

        outputChar(indata);
    }
    while (indata != '\r');

    outputChar('\n'); // '\r' is already printed
    *str = '\0';
}
