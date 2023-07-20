/**
 * Program to program the HC-05 Bluetooth receiver.
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "TM4C-UART0.h"

#define MAXSTRLEN 255

// This is here for compatibility with TM4C-UART0.h and for interrupt handling.
// If this is set by an interrupt, any TM4C-UART0.h function will automatically
// exit and comply with the interrupt.
volatile uint8_t modechangeflag = 0;

/**
 * Checks if the string format is correct according to
 * the specifications of the HC-05 datasheets.
 * @param str A pointer to the first character in the string.
 * @return true if the string is formatted correctly, false otherwise.
 */
_Bool stringFormatIsCorrect(const char* const str);

/**
 * Sends a command to the HC-05 unit.
 * @param str A pointer to the string to send.
 */
void sendToHC05(const char* str);

/**
 * Fills str with \0.
 * @param str The string to modify.
 * @param lengthOfStr The length of the entire array.
 */
void fillWithZeros(char* str, int lengthOfStr);

int main(void)
{
    // clock enables
    // enable GPIO Ports A, B, and F
    SYSCTL_RCGC2_R |= 0x23;
    // enable UART 0 and 1 clocks
    SYSCTL_RCGCUART_R |= 0x03;

    // Port A
    // enable alternate function for A[1:0]
    GPIO_PORTA_AFSEL_R |= 0x03;
    // select UART0 functionality
    GPIO_PORTA_PCTL_R &= 0xFFFFFF00;
    GPIO_PORTA_PCTL_R |= 0x11;
    // enable
    GPIO_PORTA_DEN_R |= 0x03;

    // Port B
    // enable alternate functionfor B[1:0]
    GPIO_PORTB_AFSEL_R |= 0x03;
    // select UART0 functionality
    GPIO_PORTB_PCTL_R &= 0xFFFFFF00;
    GPIO_PORTB_PCTL_R |= 0x11;
    // enable
    GPIO_PORTB_DEN_R |= 0x03;
    
    // UART0
    // disable UART0
    UART0_CTL_R &= ~0x01;
    // 38400 baud
    //UART0_IBRD_R = 26; UART0_FBRD_R = 3;
    // 4800 baud
    //UART0_IBRD_R = 208; UART0_FBRD_R = 21;
    // 9600 baud
    UART0_IBRD_R = 104; UART0_FBRD_R = 11;
    // 8 bit word
    // 1 stop bit
    // no parity bits
    // no FIFO
    UART0_LCRH_R |= 0x60;
    // use system clock
    UART0_CC_R &= ~0xF;
    // enable UART0
    UART0_CTL_R |= 0x01;
    
    // UART1
    // disable UART1
    UART1_CTL_R &= ~0x01;
    // 38400 baud
    //UART1_IBRD_R = 26; UART1_FBRD_R = 3;
    UART1_IBRD_R = 26; UART1_FBRD_R = 3; // 38400
    // 4800 baud
    //UART1_IBRD_R = 208; UART1_FBRD_R = 21;
    // 8 bit word
    // 1 stop bit
    // no parity bit
    // FIFO disabled
    UART1_LCRH_R |= 0x60;
    // use system clock
    UART1_CC_R &= ~0xF;
    // enable UART0
    UART1_CTL_R |= 0x01;

    char stringBuffer[MAXSTRLEN];
    int i;

    outputString("Welcome to the serial terminal.\r\n");
    outputString("This is the setup program for the ");
    outputString("HC-05 Bluetooth Module.\r\n");
    outputString("You are in the \"AT\" command mode.\r\n");
    outputString("The general format for commands is \"AT+<command>\".\r\n");
    outputString("Try typing \"AT\"; you should get the response ");
    outputString("\"OK\".\r\n");
    while(1)
    {
        fillWithZeros(stringBuffer, MAXSTRLEN);
        //outputString("Filled stringBuffer with zeros.\r\n");
        i = 0;

        // get a user string
        outputString("Input query: ");
        getInputString(stringBuffer, MAXSTRLEN);

        if(!stringFormatIsCorrect(stringBuffer))
        {
            outputString("String format incorrect. Did not send.\r\n");
            continue;
        }
        else
        {
            sendToHC05(stringBuffer);
            
            // save response into stringBuffer and check for responses
            // "OK", "FAIL", or ")". Then terminate the string.
            i = 0;
            while(i < MAXSTRLEN - 2)
            {
                // wait for response
                while(UART1_FR_R & 0x10); // RXFE
                stringBuffer[i] = UART1_DR_R & 0xFF;

                // check for )
                if(stringBuffer[i] == ')')
                    break;
                // check for OK
                if(stringBuffer[i-1] == 'O' && stringBuffer[i] == 'K')
                    break;
                // check for FAIL
                if(stringBuffer[i-3] == 'F' && stringBuffer[i-2] == 'A'
                    && stringBuffer[i-1] == 'I' && stringBuffer[i] == 'L')
                    break;

                // check for \0 (failed transmission)
                if(stringBuffer[i] == '\0')
                {
                    outputString("Receive unsuccessful. Received: ");
                    // print the contents of stringBuffer
                    for(int j = 0; j <= i; ++j)
                        outputChar(stringBuffer[j]);
                    outputNewLine();
                    break;
                }
                ++i;
            }
            stringBuffer[i+1] = '\0';

            outputString("Response: "); outputString(stringBuffer);
            outputNewLine();
        }
    }
}

_Bool stringFormatIsCorrect(const char* const str)
{
    // get length of string
    uint8_t len = 0;
    for(const char* iter = str; *iter != '\0'; ++iter)
        ++len;

    // str[len] is the last element (\0)
    if(str[0] != 'A' || str[1] != 'T'
        || str[len-2] != '\r' || str[len-1] != '\n')
        return 0; // false
    return 1; // true
}

void sendToHC05(const char* str)
{
    // send characters one by one not including \0
    for(; *str != '\0'; ++str)
    {
        // wait until the FIFO is empty
        while(UART1_FR_R & 0x20); // TXFF
        // send data
        UART1_DR_R = *str;
        // wait until the FIFO is empty
        while(UART1_FR_R & 0x20); // TXFF
    }
}

void fillWithZeros(char* str, int lengthOfStr)
{
    for(int i = 0; i < lengthOfStr; ++i)
        str[i] = '\0';
}
