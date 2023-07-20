#include <reg51.h>
//#include <stdint.h>

void bounce2(unsigned char times);
void bounce1(unsigned char times);

void left(unsigned char times);
void right(unsigned char times);



int main(void)
{
	while(1)
	{
		bounce2(2);
		
		bounce1(2);
		
		left(2); right(2);
	}
	
	return 0;
}



void bounce2(unsigned char times)
{
	unsigned char i;
	unsigned int delay;
	for(i=0;i<times;i++)
	{
		P1 = 0x18;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x24;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x42;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x81;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x42;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x24;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x18;
	}
}

void bounce1(unsigned char times)
{
	unsigned char i;
	
	for(i=0;i<times;i++)
	{
		right(1);
		left(1);
	}
}

void left(unsigned char times)
{
	unsigned char i;
	unsigned int delay;
	
	for(i=0; i<times; i++)
	{
		P1 = 0x80;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x40;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x20;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x10;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x08;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x04;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x02;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x01;
		for(delay = 0; delay < 16384; delay++);
	}
}

void right(unsigned char times)
{
	unsigned char i;
	unsigned int delay;
	
	for(i=0;i<times;i++)
	{
		P1 = 0x01;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x02;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x04;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x08;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x10;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x20;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x40;
		for(delay = 0; delay < 16384; delay++);
		P1 = 0x80;
		for(delay = 0; delay < 16384; delay++);
	}
}
