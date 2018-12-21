//slave
#include<lpc214x.h>
int main()
{
	PINSEL0=0x00001505;
	IO0DIR=(1<<16);
	IO0DIR|=(1<<4)|(1<<5)|(1<<7)|~(1<<6)|(1<<0);
	S0SPCR|=0x40;
	while(1)
	{
		char x;
		while((S0SPSR&0x80)==0);
		x=S0SPDR;
		if(x=='B')
			IO0SET=(1<<16);
		else
			IO0CLR=(1<<16);
	}
	
}
