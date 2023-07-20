/**
 * This program interfaces with UART1 and performs various operations
 * with the data retrieved from it.
 */
//#include <stdint.h>
#include <ctype.h> // for character tolower
#include "tm4c123gh6pm.h"

// These macros are for setting the LED colors
#define LEDred 0x2
#define LEDgrn 0x8
#define LEDblu 0x4

/**
 * This function waits until there is a response from UART1
 * and returns it.
 * @return The character retrieved from UART1.
 */
unsigned char getBluetoothInput(void);

void UART1_OutChar(unsigned char data);

int main(void)
{
    // Enable GPIO Port B and F
    SYSCTL_RCGC2_R |= 0x22;
    // Enable UART 1
    SYSCTL_RCGCUART_R |= 0x02;

    // Port B setup
    // Pins 0 and 1 are alternate functions
    GPIO_PORTB_AMSEL_R &= ~0x03;
    GPIO_PORTB_AFSEL_R |= 0x03;
    GPIO_PORTB_PCTL_R &= 0xFFFFFFFC;
    // Select UART1 Tx and Rx
    GPIO_PORTB_PCTL_R |= 0x00000011;
    // enable pins 0 and 1
    GPIO_PORTB_DEN_R |= 0x03;

    // Port F setup
    // set F[3:1] as outputs
    GPIO_PORTF_DIR_R |= 0x0E;
    // enable F[3:1]
    GPIO_PORTF_DEN_R |= 0x0E;

    // disable UART
    UART1_CTL_R &= ~0x01;
    // set the baud rate to 4800
    //UART1_IBRD_R = 0xD0; // 208 decimal
    //UART1_FBRD_R = 21;
    // set the baud rate to 38400
    //UART1_IBRD_R = 26; UART1_FBRD_R = 3;
    //UART1_IBRD_R = 104; UART1_FBRD_R = 11; // 9600
    UART1_IBRD_R = 17; UART1_FBRD_R = 23; // 57600
    // 8 bit word
    // one stop bit
    // no parity bit
    // FIFO enabled
    UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
    // enable UART
    UART1_CTL_R |= 0x301;

    unsigned char inchar = 0;

    while(1)
    {
        UART1_OutChar('x');
        inchar = tolower(getBluetoothInput());
        
        switch(inchar)
            {   case 'w': // forward
                GPIO_PORTF_DATA_R &= 0x11;
                GPIO_PORTF_DATA_R |= LEDgrn;
                break;
            case 's': // reverse
                GPIO_PORTF_DATA_R &= 0x11;
                GPIO_PORTF_DATA_R |= LEDblu;
                break;
            case 'a': // turn left
                GPIO_PORTF_DATA_R &= 0x11;
                GPIO_PORTF_DATA_R |= LEDred | LEDgrn;
                break;
            case 'd': // turn right
                GPIO_PORTF_DATA_R &= 0x11;
                GPIO_PORTF_DATA_R |= LEDred | LEDblu;
                break;
            case 't': // stop
                GPIO_PORTF_DATA_R &= 0x11; // LED off
                break;
            case 'u': // speed up
                break;
            case 'l': // slow down
                break;
            case 0:
                GPIO_PORTF_DATA_R = LEDblu;
                break;
            default:
                GPIO_PORTF_DATA_R = LEDred;
                break;
        }
    }
}

unsigned char getBluetoothInput(void)
{
    // do nothing while receive FIFO is empty
    while(UART1_FR_R & 0x10); // RXFE
    
    return (UART1_DR_R & 0xFF);
}

//------------UART1_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(unsigned char data){
  while((UART1_FR_R&UART_FR_TXFF) != 0);
  UART1_DR_R = data;
}
