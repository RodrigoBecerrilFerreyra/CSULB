#include "tm4c123gh6pm.h"
#include "TM4C-UART0.h"
#include <stdint.h>

#define MAXSTRLEN 255
#define EOT 4  // ASCII end of transmission character
#define ENQ 5  // ASCII enquiry character
#define ACK 6  // ASCII acknowledge character
#define NAK 21 // ASCII negative acknowledge character
#define CAN 24 // ASCII cancel character

#define LEDRED   0x2
#define LEDGREEN 0x8
#define LEDBLUE  0x4

extern void EnableInterrupts(void);

enum masterorslave {MASTER = 1, SLAVE = 0};
const uint8_t LEDcolors[6] = {LEDRED, LEDGREEN, LEDBLUE, LEDRED | LEDBLUE, LEDRED | LEDGREEN | LEDBLUE, 0};
volatile uint8_t currentcolor = 0;
volatile uint8_t mode = 3;
volatile uint8_t modechangeflag = 1;
volatile uint8_t firstrun = 1;
// master or slave select
// set to MASTER to program master MCU (MCU1)
// set to SLAVE  to program slave  MCU (MCU2)
enum masterorslave MCUselect = SLAVE;

void mode3(void);
void mode2(void);
void mode1(void);

int main(void)
{
    SYSCTL_RCGCUART_R |= 0x03; // enable UART 0 and UART 1
    SYSCTL_RCGC2_R |= 0x23; // enable ports A, B, and F
    // wait for clock to turn on
    while(((SYSCTL_RCGCUART_R & 0x03) != 0x03)
        && (SYSCTL_RCGC2_R    & 0x23) != 0x23);

    // UART 0 GPIO pins (A[0] = U0Rx and A[1] = U0Tx)
    GPIO_PORTA_AFSEL_R &= ~0x03;
    GPIO_PORTA_AFSEL_R |=  0x03; // select alternate function
    GPIO_PORTA_PCTL_R  &= ~0xFF;
    GPIO_PORTA_PCTL_R  |=  0x11; // select U0Rx and U0Tx
    GPIO_PORTA_DIR_R   |=  0x03; // output bits
    GPIO_PORTA_DEN_R   |=  0x03; // enable

    // UART 0 setup
    UART0_CTL_R  &= ~0x01; // disable UART 0
    UART0_IBRD_R  =  8; // 16 MHz / (16 * 115200) = 8.68055555556
    UART0_FBRD_R  =  44; // = floor(0.68055555556 * 64 + 0.5)

    //                        115200 baud
    UART0_LCRH_R &= ~0x80; // no parity bit
    UART0_LCRH_R |=  0x60; // word length: 8
    UART0_LCRH_R &= ~0x10; // 1-deep FIFO
    UART0_LCRH_R &= ~0x08; // 1 stop bit
    UART0_LCRH_R &= ~0x02; // no parity bit
    UART0_CTL_R  |=  0x01; // enable UART 0

    // UART 1 GPIO pins (B[0] = U1Rx and B[1] = U1Tx)
    GPIO_PORTB_AFSEL_R &= ~0x03;
    GPIO_PORTB_AFSEL_R |=  0x03; // select alternate function
    GPIO_PORTB_PCTL_R  &= ~0xFF;
    GPIO_PORTB_PCTL_R  |=  0x11; // select U1Rx and U1Tx
    GPIO_PORTB_DIR_R   |=  0x03; // output
    GPIO_PORTB_DEN_R   |=  0x03; // enable

    // external button B[2]
    GPIO_PORTB_AFSEL_R &= ~0x04;
    GPIO_PORTB_DIR_R   &= ~0x04; // input
    GPIO_PORTB_DEN_R   |=  0x04;

    // B[2] interrupt setup
    GPIO_PORTB_IM_R  &= ~0x04;
    GPIO_PORTB_IS_R  &= ~0x04; // edge-sensitive
    GPIO_PORTB_IBE_R &= ~0x04; // only one edge interrupts
    GPIO_PORTB_IEV_R |=  0x04; // rising edge-sensitive
    GPIO_PORTB_ICR_R  =  0x04; // clear GPIORIS
    GPIO_PORTB_IM_R  |=  0x04; // unmask
    NVIC_PRI0_R &= ~0xE000; // priority 0 for interrupt 1
    NVIC_EN0_R  &= ~0x02;
    NVIC_EN0_R  |= 0x02; // enable interrupt 1

    // UART 1 setup
    UART1_CTL_R  &= ~0x01; // disable UART 1
    UART1_IBRD_R  =  8; // 16 MHz / (16 * 115200) = 8.68055555556
    UART1_FBRD_R  =  44; // = floor(0.68055555556 * 64 + 0.5)
    //                        115200 baud
    UART1_LCRH_R &= ~0x80; // no parity bit
    UART1_LCRH_R |=  0x60; // word length: 8
    UART1_LCRH_R &= ~0x10; // FIFO disabled
    UART1_LCRH_R &= ~0x08; // 1 stop bit
    UART1_LCRH_R &= ~0x02; // no parity bit
    UART1_IFLS_R &= ~070; UART1_IFLS_R |= 040;
    //UART1_IM_R   |=  0x10; // enable receive interrupts
    UART1_CTL_R  |=  0x01; // enable UART 1
    NVIC_PRI1_R  &= ~0xE00000; // priority 0
    NVIC_EN0_R   |= 0x40; // enable interrupt 6

    // switch stuff
    do {GPIO_PORTF_LOCK_R = 0x4C4F434B;} while (GPIO_PORTF_LOCK_R == 1);
    GPIO_PORTF_CR_R |= 0x1;
    do {GPIO_PORTF_LOCK_R = 0;} while (GPIO_PORTF_LOCK_R == 0);
    GPIO_PORTF_AFSEL_R &= ~0x11;
    GPIO_PORTF_DIR_R   &= ~0x11;
    GPIO_PORTF_PUR_R   |= 0x11;
    GPIO_PORTF_DEN_R   |=  0x11;

    GPIO_PORTF_IM_R  &= ~0x11; // mask interrupt
    GPIO_PORTF_IS_R  &= ~0x11; // edge-sensitive interrupts
    GPIO_PORTF_IBE_R &= ~0x11; // interrupt on one edge only
    GPIO_PORTF_IEV_R &= ~0x11; // interrupt on falling edge
    GPIO_PORTF_ICR_R  =  0x11; // clear GPIORIS
    GPIO_PORTF_IM_R  |=  0x11; // unclear mask
    NVIC_PRI7_R      |=  0x00200000; // priority 1 for interrupt 30
    NVIC_EN0_R       |=  0x40000000; // enable bit 30
    EnableInterrupts();

    // LED stuff
    // PF1 is red, PF2 is blue, and PF3 is green
    GPIO_PORTF_AFSEL_R &= ~0x0E;
    GPIO_PORTF_DIR_R   |=  0x0E;
    GPIO_PORTF_DEN_R   |=  0x0E;
    char temp;

    while(1)
    {
        if(modechangeflag)
        {
            modechangeflag = 0;
            if(MCUselect == MASTER)
            {
                outputString("\r\nType 1 for mode 1, 2 for mode 2, or 3 for mode 3: ");
                temp = getInputChar();
                mode = temp - '0';

                if(mode < 1 || mode > 3)
                {
                    outputString("Invalid data. Bringing you to ");
                    outputString("mode 1...\r\n");
                    mode = 1;
                }
                if(firstrun == 1)
                {
                    //outputString("First run.\r\n");
                    firstrun = 0;
                }
                else
                {
                    //outputString("Second run.\r\n");
                    // send ACK
                    while(UART1_FR_R & 0x20); // TXFF
                    UART1_DR_R = ACK;
                    while((UART1_FR_R & 0x80) == 0);
                }

                // send data
                while(UART1_FR_R & 0x20); // TXFF
                UART1_DR_R = mode;
                while((UART1_FR_R & 0x80) == 0);
            }
            else if(MCUselect == SLAVE)
            {
                outputString("\r\nin slave modechangeflag block\r\n");
                outputString("\r\nmode (before) = "); outputChar(mode + '0'); outputNewLine();

                outputString("Waiting for UART... ");
                while(UART1_FR_R & 0x10); // RXFE

                outputString("Data received.\r\n");
                mode = UART1_DR_R & 0xFF;
                while(UART1_FR_R & 0x40); // RXFF

                outputString("mode (after) = "); outputChar(mode + '0'); outputNewLine();
            }
        }

        if(modechangeflag == 0 && mode == 3)
        {
            mode3();
        }
        else if(modechangeflag == 0 && mode == 2)
        {
            mode2();
        }
        else if(modechangeflag == 0 && mode == 1)
        {
            mode1();
        }
    }
}

void mode1(void)
{
    currentcolor = 5; // dark
    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
    // Mode 1
    while(1)
    {
        if(MCUselect == MASTER)
        {
            outputString("Type to change the LED color:\r\n");
            outputString("\r\n(r)ed, g(green), b(blue), p(purple), w(white), d(dark): ");
            char input = getInputChar();
            // return for interrupt
            if(modechangeflag)
            {
                return;
            }

            switch(input)
            {
                case 'r':
                    //GPIO_PORTF_DATA_R = LEDRED;
                    currentcolor = 0;
                    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];

                    outputString("Red LED is on.\r\n");
                    break;
                case 'g':
                    //GPIO_PORTF_DATA_R = LEDGREEN;
                    currentcolor = 1;
                    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];

                    outputString("Green LED is on.\r\n");
                    break;
                case 'b':
                    //GPIO_PORTF_DATA_R = LEDBLUE;
                    currentcolor = 2;
                    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
                    outputString("Blue LED is on.\r\n");
                    break;
                case 'p':
                    //GPIO_PORTF_DATA_R = LEDRED | LEDBLUE;
                    currentcolor = 3;
                    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
                    outputString("Red and blue LEDs are on.\r\n");
                    break;
                case 'w':
                    //GPIO_PORTF_DATA_R = LEDRED | LEDGREEN | LEDBLUE;
                    currentcolor = 4;
                    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
                    outputString("Red, green, and blue LEDs are on.\r\n");
                    break;
                case 'd':
                    //GPIO_PORTF_DATA_R = 0;
                    currentcolor = 5;
                    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
                    outputString("No LEDs are on.\r\n");
                    break;
                default:
                    outputString("Data invalid.\r\n");
            }
        } else if(MCUselect == SLAVE)
        {
            // return for interrupt
            if(modechangeflag)
            {
                return;
            }
        }
    }
}

void mode2(void)
{
    // Mode 2
    //GPIO_PORTF_DATA_R = LEDRED;
    currentcolor = 0;
    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
    while(1)
    {
        // return for interrupt
        if(modechangeflag)
        {
            return;
        }

        // if recieve fifo is full (RXFF)
        while(UART1_FR_R & 0x40)
        {
            // update mode
            currentcolor = UART1_DR_R & 0xFF;
            GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
        }
    }
}

void mode3(void)
{
    currentcolor = 5;
    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
    // Mode 3
    if(MCUselect == MASTER)
    {
        char instring[MAXSTRLEN];
        char outstring[MAXSTRLEN];
        char statuscode;
        uint8_t i;
        while(1)
        {
            // user input block
            outputString("Please enter a message.\r\n");
            getInputString(instring, MAXSTRLEN);

            if(modechangeflag)
                return;

            //outputString("instring = ");
            //outputString(instring);
            //outputNewLine();

            // send the string
            i = 0;
            while(1)
            {
                while(UART1_FR_R & 0x20); // don't send if FIFO is full (TXFF)
                UART1_DR_R = instring[i];
                //outputString("Sending instring["); outputChar(i + '0');
                //outputString("] = "); outputChar(instring[i]);
                //outputNewLine();
                while(UART1_FR_R & 0x20); // wait until FIFO is empty (TXFF)

                // send enquiry character, wait for acknowledge character
                // don't send if fifo is full
                while(UART1_FR_R & 0x20); // TXFF
                //outputString("Sending ENQ... ");
                UART1_DR_R = ENQ;
                //outputString("Sent!\r\n");

                // wait for there to be something in the receive fifo
                while(UART1_FR_R & 0x10); // RXFE
                do {statuscode = UART1_DR_R & 0xFF;}
                while(statuscode != ACK);
                //outputString("Acknowledgement received!\r\n");

                if(instring[i] == '\0') {break;}
                ++i;
            }
            //outputString("Escaped the send loop.\r\n");

            // get response from slave MCU
            i = 0;
            while(1)
            {
                // wait for there to be data in the FIFO
                //outputString("Waiting for data... (i = ");
                //outputChar('0' + i); outputString(")\r\n");
                while(UART1_FR_R & 0x10); // RXFE

                outstring[i] = UART1_DR_R & 0xFF;
                //outputString("received outstring["); outputChar(i + '0');
                //outputString("] = "); outputChar(outstring[i]);
                //outputNewLine();

                // wait for enquiry character, send an acknowledgement char
                while(UART1_FR_R & 0x10); // RXFE
                //outputString("Waiting for enquiry... ");
                do {statuscode = UART1_DR_R & 0xFF;}
                while(statuscode != ENQ);
                //outputString("ENQ received!\r\n");

                // wait until transfer fifo is empty
                while(UART1_FR_R & 0x20); // TXFF
                UART1_DR_R = ACK;
                //outputString("Acknowledgement sent!\r\n");

                if(outstring[i] == '\0') {break;} // end of transmission
                ++i;
            }

            // send to PC
            outputString(outstring);
            outputNewLine();
        }
    }
    else if(MCUselect == SLAVE)
    {
        // Mode 3 slave
        char stringFromMaster[MAXSTRLEN];
        char stringToMaster[MAXSTRLEN];
        char statuscode;
        uint8_t j, k;
        while(1)
        {
            // block to get string from
            j = 0;
            while(1)
            {
                // wait for incoming string
                //outputString("Waiting for input data... (j = ");
                //outputChar(j + '0'); outputChar(')');
                //outputNewLine();
                while(UART1_FR_R & 0x10) // RXFE
                {
                    if(modechangeflag)
                    {
                        return;
                    }
                }

                stringFromMaster[j] = UART1_DR_R & 0xFF;
                //outputString("stringFromMaster[");
                //outputChar(j + '0');
                //outputString("] = ");
                //outputChar(stringFromMaster[j]);
                //outputNewLine();

                // wait for enquiry character, send acknowledgement char
                // wait for receive fifo to not be empty
                while(UART1_FR_R & 0x10); // RXFE
                //outputString("Waiting for enquiry character... ");
                do {statuscode = UART1_DR_R & 0xFF;}
                while(statuscode != ENQ);
                //outputString("Received!\r\n");

                // wait for transmit FIFO to be empty
                while(UART1_FR_R & 0x20); // TXFF
                UART1_DR_R = ACK;
                //outputString("Acknowledgement sent!\r\n");

                //outputChar(stringFromMaster[j]);
                //outputNewLine();

                if(stringFromMaster[j] == '\0') {break;} // end of transmission
                ++j;
            }

            //outputString("The entire string is \"");
            //outputString(stringFromMaster);
            //outputString("\"\r\n");

            // build response
            j = 0;
            while(1)
            {
                stringToMaster[j] = "I received \""[j];
                if(stringToMaster[j] == '\0') {break;}
                ++j;
            }

            // This does copy a null terminator into the string.
            // The first iteration should replace the \0.
            k = 0;
            while(1)
            {
                stringToMaster[j] = stringFromMaster[k];
                if(stringToMaster[j] == '\0') {break;}
                ++j; ++k;
            }

            // finish up the response
            stringToMaster[j]     = '\"'; // this replaces the \0 again
            stringToMaster[j + 1] = '.';
            stringToMaster[j + 2] = '\r';
            stringToMaster[j + 3] = '\n';
            stringToMaster[j + 4] = '\0';

            //outputString("The final string to send is:\r\n");
            //outputString(stringToMaster);
            //outputNewLine();

            // send stringToMaster
            j = 0;
            while(1)
            {
                while(UART1_DR_R & 0x20); // don't send if FIFO is full(TXFF)
                UART1_DR_R = stringToMaster[j];
                //outputString("Sending stringToMaster["); outputChar(j + '0');
                //outputString("] = "); outputChar(stringToMaster[j]);
                //outputNewLine();
                while(UART1_DR_R & 0x20); // wait until FIFO is empty (TXFF)

                // send ENQ, wait for ACK
                // wait until there is nothing in the transfer fifo
                while(UART1_FR_R & 0x20); // TXFF
                //outputString("Sending enquiry character... ");
                UART1_DR_R = ENQ; //outputString("Sent!\r\n");

                // wait for data to come in
                while(UART1_FR_R & 0x10);
                //outputString("Waiting for ACK... ");
                do {statuscode = UART1_DR_R & 0xFF;}
                while(statuscode != ACK);
                //outputString("Received!\r\n");

                if(stringToMaster[j] == '\0') {break;} // end of transmission
                ++j;
            }
            //outputString("Broke out of the send loop.\r\n");
        }
    }
}

/**
 * Changes the mode that the system is operating in.
 */
void GPIOPortB_Handler(void)
{
    GPIO_PORTB_ICR_R = 0x04;
    currentcolor = 5; // dark
    GPIO_PORTF_DATA_R = LEDcolors[currentcolor];

    if(MCUselect == SLAVE)
    {
        char status;
        while(UART1_FR_R & 0x10); // RXFE
        do
        {
            status = UART1_DR_R & 0xFF;
            outputString("I'm stuck here: status = ");
            outputChar('0' + status);
            outputNewLine();
        }
        while(status != ACK);
    }
    modechangeflag = 1;
}

/**
 * Port F interrupt handler for Mode 2.
 * Does not work outside of Mode 2.
 */
void GPIOPortF_Handler(void)
{
    if(mode != 2)
    {
        GPIO_PORTF_ICR_R = 0x11;
        return;
    }
    switch(GPIO_PORTF_MIS_R)
    {
        case 0x10: // left button
            GPIO_PORTF_ICR_R = 0x10;

            // update mode and light
            currentcolor = (currentcolor >= 5) ? 0 : currentcolor + 1;
            GPIO_PORTF_DATA_R = LEDcolors[currentcolor];
            break;

        case 0x01: // right button
            GPIO_PORTF_ICR_R = 0x01;

            UART1_DR_R = currentcolor;
            while(UART1_FR_R & 0x20); // wait for TXFF in UARTDR to be cleared

            break;

        default:
            GPIO_PORTF_ICR_R = 0x11;
    }
}
