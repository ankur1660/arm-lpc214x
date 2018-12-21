#include<lpc214x.h>
void delay(int);


int main()
{
	PLL0CON=0x01;//1 step
	PLL0CFG=0x24;//for 60Mhz//2nd step
	PLL0FEED=0xaa;//3rd step
	PLL0FEED=0x55;
	while((PLL0STAT&(1<<10))==0);//waiting for pll lock 1
	PLL0CON|=(1<<1);//pll connect hogaya
	PLL0FEED=0xaa;
	PLL0FEED=0x55;
	
	VPBDIV=0x01;//Peripheral devices running on 60 Mhz
	
	
	
	
	while(1)
	{
		IO0DIR=0xff;
		IO0SET=0x01;
		delay(1000);
		IO0CLR=0x01;
		IO0SET=0x02;
		delay(1000);
		IO0CLR=0x02;
		IO0SET=0x04;
		delay(1000);
		IO0CLR=0x04;
}
}
void delay(int x)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<1000;j++);
	}
}
