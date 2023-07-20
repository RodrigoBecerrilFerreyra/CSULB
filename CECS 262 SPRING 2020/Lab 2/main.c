#include <reg51.h>

unsigned int magicNum = 8192;

void wait(unsigned int cycles);
void ls(unsigned char times);
void rs(unsigned char times);
void bounce2(void);

////////////////////////////////

int main(void)
{
	unsigned char i;
	
	for(i=0;i<2;i++){bounce2();}
	for(i=0;i<2;i++){rs(1); ls(1);}
	rs(2); ls(2);
	return 0;
}

////////////////////////////////

void wait(unsigned int cycles)
{
	unsigned int i;
	for(i = 0; i < cycles; i++);
}

void ls(unsigned char times)
{
	unsigned char i, j;
	
	for(j=0; j<times; j++)
	{
		P1 = 0x01;
		
		for(i = 0; i < 8; i++)
		{
			wait(magicNum);
			P1 = P1 << 1;
		}
	}
}

void rs(unsigned char times)
{
	unsigned char i, j;
	
	for(j=0; j<times; j++)
	{
		P1 = 0x80;
		
		for(i = 0; i < 8; i++)
		{
			wait(magicNum);
			P1 = P1 >> 1;
		}
	}
}

void bounce2(void)
{
	unsigned char i;
	unsigned char first;
	unsigned char second;
	
		first = 0x01;
		second = 0x80;
		for(i = 0; i < 8; i++)
		{
			
			P1 = first | second;
			wait(magicNum);
			
			first = first << 1;
			second = second >> 1;
			
		}
}
