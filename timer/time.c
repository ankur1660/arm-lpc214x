#include<lpc214x.h>
#define PLLE 0
#define PLLC 1
#define PLOCK 10
#define counter_enable 0
#define counter_reset 1

void delay(int count)
{
	T0CTCR=0x00;//Timer Counter Register is disabled 
	T0PC=0x00; //247 //prescale register
	T0TC=0x00; //247 //
	T0PR=59999;//count limit
	T0TCR=(1<<counter_enable);//Timer is enabled
	while(T0TC!=count);//250
	T0TCR=0x00;
	
}

int intpll()
{
	PLL0CON=(1<<PLLE);//1 step
	PLL0CFG=0x24;//for 60Mhz//2nd step
	PLL0FEED=0xaa;//3rd step
	PLL0FEED=0x55;
	while((PLL0STAT&(1<<PLOCK))==0);//waiting for pll lock 1
	PLL0CON|=(1<<PLLC);//pll connect 
	PLL0FEED=0xaa;
	PLL0FEED=0x55;
	VPBDIV=0x01;//Peripheral devices running on 60 Mhz
}	

int main()
{
	intpll();
	IO0DIR|=0xff;
	while(1)
	{
	IO0SET|=0x01;
	delay(1);
	
	IO0CLR|=0x01;
	delay(1);	
	}	
}
//standard 255 delay in 1sec] 