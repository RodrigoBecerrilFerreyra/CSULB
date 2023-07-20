#include <reg51.h>
//#include <stdint.h> //library doesn't work, please fix
//by Rodrigo Becerril Ferreyra

sbit sw0 = P0^0;
sbit sw1 = P0^1;
sbit sw2 = P0^2;
sbit sw3 = P0^3;
sbit sw4 = P0^4;
sbit sw5 = P0^5;
sbit sw6 = P0^6;
sbit sw7 = P0^7;

bit goingleft = 0;
bit firsttime = 1;
bit countup = 1;
unsigned char time = 1;
unsigned char leftbounce;
unsigned char rightbounce;

void delay(unsigned char seconds)
{
	unsigned int i;
	
	switch(seconds)
	{
		case 1:
			for(i = 0; i < 0x7e32; i++);
			break;
		case 2:
			for(i = 0; i < 0xfc65; i++);
			break;
		case 3:
			for(i = 0; i < 0xffff; i++);
			for(i = 0; i < 0x7a99; i++);
			break;
		case 4:
			for(i = 0; i < 0xffff; i++);
			for(i = 0; i < 0xf994; i++);
			break;
	}
	
}


int main()
{
	P0 = 0xFF;
	P1 = 0x00;
	
	while(1)
	{
		
		//delay logic
		if((!sw4 && !sw5 && !sw6 && !sw7) || sw4)
			time = 1; //0.5 s
		else if(sw5)
			time = 2; //1 s
		else if(sw6)
			time = 3; //1.5 s
		else if(sw7)
			time = 4; //2 s
		
		if(sw0) //left-right bounce
		{
			
			if(firsttime) //initial setting
				P1 = 0x80;
			
			delay(time);
			
			switch(P1) //this prevents the LED from going past bit 0 or bit 7.
			{
				case 0x01:
					goingleft = 1;
					break;
				case 0x80:
					goingleft = 0;
					break;
				default:
					goingleft = goingleft;
			}
			
			P1 = goingleft ? P1 << 1 : P1 >> 1;
			firsttime = 0;
			
		}
		else if(sw1) //counting mode
		{
			
			if(firsttime) //initialization
				P1 = countup ? 0x00 : 0xff;
			
			delay(time);
			
			P1 = countup ? P1 + 1 : P1 - 1;
			
			firsttime = 0;
			
		}
		else if(sw2) //doublebounce
		{
			
			if(firsttime) //initialization
			{
				leftbounce  = 0x01;
				rightbounce = 0x80;
			}
			
			delay(time);
			
			P1 = leftbounce | rightbounce;
			
			leftbounce  <<= 1;
			rightbounce >>= 1;
			
			if(leftbounce == 0x00 && rightbounce == 0x00)
			{
				leftbounce  = 0x01;
				rightbounce = 0x80;
			}
			
			firsttime = 0;
			
		}
		else if(sw3) //bounce left only (increment)
		{
			
			if(firsttime)
				P1 = 0x00;
			
			delay(time);
			
			switch(P1)
			{
				case 0x00:
					goingleft = 0;
					break;
				case 0xff:
					goingleft = 1;
					break;
				default:
					goingleft = goingleft;
			}
			
			if(!goingleft)
			{
				P1 >>= 1;
				P1 += 0x80;
			}
			else
				P1 <<= 1;
			
			firsttime = 0;
			
		}
		else
		{
			firsttime = 1;
			P1 = 0x00;
		}
		
	}
	
	return 0;
}
