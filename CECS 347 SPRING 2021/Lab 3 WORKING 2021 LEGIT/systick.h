#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#define STCTRL *((volatile unsigned long *) 0xE000E010)
#define STRELOAD *((volatile unsigned long *) 0xE000E014)
#define STCURRENT *((volatile unsigned long *) 0xE000E018)

#endif // __SYSTICK_H__
