#include<lpc214x.h>
int i;
int intpll()
{
	PLL0CON=(1<<0);//1 step
	PLL0CFG=0x24;//for 60Mhz//2nd step
	PLL0FEED=0xaa;//3rd step
	PLL0FEED=0x55;
	while((PLL0STAT&(1<<10))==0);//waiting for pll lock 1
	PLL0CON|=(1<<1);//pll connect 
	PLL0FEED=0xaa;
	PLL0FEED=0x55;
	VPBDIV=0x01;//Peripheral devices running on 60 Mhz
}	

void ini_counter()
{
	T0TCR=0x01;
	T0CTCR=0x01;//rising clock
	T0TC=0x00;
	T0PC=0x00;
	T0MCR=0x0004;
	T0MR0=1000;
	while(T0TC!=T0MR0);
	T0TCR=0x02;
	
}
int main()
{
	IO0DIR=0xfff;
	ini_counter();
	IO0SET|=(1<<0);
	for(i=0;i<1000;i++);
	IO0CLR|=(1<<0);
	for(i=0;i<1000;i++);
}