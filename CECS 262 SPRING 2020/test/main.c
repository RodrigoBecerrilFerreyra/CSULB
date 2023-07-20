#include <reg51.h>

unsigned int i;

void delay(unsigned char seconds)
{
	unsigned char i, j;
  
  for(j = 0; j < seconds; j++)
  {
    for(i = 0; i < 20; i++) // 1 s
    {
      TMOD = 0x01; // mode 1
      TH0 = 0x3c; TL0 = 0xb0; // 0xffff - 50 000; 50 ms
      TR0 = 1; // turn timer off
      while(TF0 == 0); // do nothing until overflow
      TF0 = 0; // reset flag
    }
    TR0 = 0; // turn off timer
  }
}

int main(void)
{
	P1 = 0x00;
	while(1)
	{
		P1 = 0xff; delay(1);
		P1 = 0x00; delay(2);
	}
	return 0;
}
