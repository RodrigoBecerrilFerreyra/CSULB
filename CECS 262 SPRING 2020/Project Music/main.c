#include <reg51.h>

void delay(void); void delay(float);
void delay1sec(void);
sbit output = P3^0;

int main(void)
{
	P1 = 0x00;
	while(1)
	{
		output = 1;
		delay();
		
		output = 0;
		delay();
	}
}

void delay(void)
{
	TR0 = 0;
	TMOD = 0x01;
	TH0 = 0xf3; TL0 = 0x9b; // 63263
	TR0 = 1;
	while(!TF0); TF0 = 0;
}

void delay(float hertz)
{
	unsigned long int times = 65536.0f - ((1.0/hertz)*1000000.0f);
	unsigned int loops = 0;
	unsigned int i;
	
	while(times < 0)
	{
		times += 65536;
		loops++;
	}
	
	
}

void delay1sec(void)
{
	unsigned int i;
	TMOD = 0x01;
	TH0 = 0x3b; TL0 = 0xe8;
	TR0 = 1;
	for(i = 0; i < 20; i++)
	{
		while(!TF0);
		TF0 = 0;
		TH0 = 0x3b; TL0 = 0xe8; // 63263
		TR0 = 1;
	}
}
