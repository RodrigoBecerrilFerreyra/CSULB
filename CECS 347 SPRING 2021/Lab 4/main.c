// input signal connected to PE2/AIN1

#include <stdint.h>
#include "ADCSWTrigger.h"
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "Nokia5110.h"

#define STCTRL *((volatile unsigned long *) 0xE000E010)
#define STRELOAD *((volatile unsigned long *) 0xE000E014)
#define STCURRENT *((volatile unsigned long *) 0xE000E018)

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
//long StartCritical (void);    // previous I bit, disable interrupts
//void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

volatile uint16_t ADCvalue;
volatile uint8_t by_formula, by_table;
volatile uint8_t updateLCD = 0;

//const uint16_t table[] = {620, 670, 716, 740, 794, 835, 907, 1032, 1177, 1340, 1630, 2129, 3090};
const uint16_t table[] = {3090, 2129, 1630, 1340, 1177, 1032, 907, 835, 794, 740, 716, 670, 620};

int main(void)
{
    PLL_Init();
    ADC0_InitSWTriggerSeq3_Ch1(); // ADC initialization PE2/AIN1
    Nokia5110_Init(); Nokia5110_Clear();

    STCTRL |= 0x6; // Internal clock and interrupt enable
    STRELOAD = 800000 - 1; // 50MHz (clock) / 20 Hz (target)
    STCURRENT = 0;
    STCTRL |= 0x1;
    EnableInterrupts();

    while(1)
    {
        if(updateLCD)
        {
            updateLCD = 0;

            if(ADCvalue >= table[0])
                by_table = 10;
            else if(ADCvalue <= table[12])
                by_table = 70;
            else
            {
                uint8_t i;
                for(i = 1; i < 13; i++)
                {
                    if(table[i] <= ADCvalue)
                    {
                        by_table = (10 + 5*i) - (ADCvalue - table[i])/((table[i-1] - table[i])/5);
                        break;
                    }
                }


            }

            Nokia5110_Clear(); Nokia5110_SetCursor(0, 0);

            Nokia5110_OutString("ADC value:  ");
            Nokia5110_PrintNumber(ADCvalue);
            Nokia5110_SetCursor(0, 2);
            Nokia5110_OutString("By formula: ");
            Nokia5110_PrintNumber(by_formula);
            Nokia5110_SetCursor(0, 4);
            Nokia5110_OutString("By table:   ");
            Nokia5110_PrintNumber(by_table);
        }
    }
}

void SysTick_Handler(void)
{
    ADCvalue = ADC0_InSeq3();
    by_formula = 46696.59899/ADCvalue - 8.30869183;
    updateLCD = 1;
}
