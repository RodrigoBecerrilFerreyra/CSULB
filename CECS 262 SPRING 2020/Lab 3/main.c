#include <reg51.h>
// By Rodrigo Becerril Ferreyra

unsigned int magicNum = 8192; //2^13

//Required functions from previous labs for pattern();
void wait(unsigned int cycles);
void ls(unsigned char times);
void rs(unsigned char times);
void bounce2(void);
void pattern(void);

////////////////////////////////

// These three are the mode selection bits
sbit mode1 = P0^7;
sbit mode2 = P0^6;
sbit mode3 = P0^5;
// These three are for the OR gate in mode2
sbit or1   = P0^0;
sbit or2   = P0^1;
sbit or3   = P0^2;

// Output bit for mode2
sbit out   = P1^1;

int main(void)
{
	//Reminder: my main() loops infinitely whether I have a superloop or not.
	P1 = 0x00; //output
	P0 = 0xFF; //input
	
	while(mode1) //Using while instead of if in order to keep count
		{P1 += 1; wait(magicNum);}
	while(mode2)
		out = (or1 || or2 || or3); //assigns either a 1 or 0
	while(mode3)
		pattern(); //FIXME: pattern does not break when switch is turned off when running
	
	return 0;
}

////////////////////////////////

void pattern(void)
{
	/**Pattern for Lab 1/Lab2 */
	unsigned char i;
	
	for(i=0;i<2;i++){bounce2();}
	for(i=0;i<2;i++){rs(1); ls(1);}
	rs(2); ls(2);
}

void wait(unsigned int cycles)
{
	unsigned int i;
	for(i = 0; i < cycles; i++);
}

void ls(unsigned char times)
{
	/**shifts one bit from the right to the left*/
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
	/**Shifts one bit from the right to the left*/
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
	/**Bounces two bits together*/
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
