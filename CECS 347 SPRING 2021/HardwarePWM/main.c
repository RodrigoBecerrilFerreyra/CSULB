#include "tm4c123gh6pm.h"
#include <stdint.h>

int main(void)
{
    SYSCTL_RCGC2_R |= 0x20;
    while((SYSCTL_RCGC2_R & 0x20) != 0x20);

    GPIO_PORTF_DIR_R &= ~0xE;
    GPIO_PORTF_AFSEL_R &= ~0xE;
    GPIO_PORTF_DEN_R |= 0xE;
    while(1)
    {
        GPIO_PORTF_DATA_R |= 0xE;
    }
}
