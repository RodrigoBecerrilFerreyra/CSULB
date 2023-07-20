#include <reg51.h>

void delay(void)
{
	unsigned int i;
	
	TMOD = 0x01;
	for(i = 0; i < 20; i++)
	{
		TR0 = 1;
		TH0 = 0x3c; TL0 = 0xaf;
		while(TF0 == 0);
		TF0 = 0;
	}
}

//void delay1(void)
//{
//	unsigned int i;
//	for(i = 0; i < 8192; i++);
//}

int main(void)
{
	P1 = 0xff;
	delay();
	P1 = 0x00;
	delay();
	return 0;
}
