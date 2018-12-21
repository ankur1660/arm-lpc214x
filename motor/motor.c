#include<lpc214x.h>
int main()
{
	IO0DIR=0xfffff;
	while(1)
	{
		if(IO0PIN&(1<<16))//forward
		{
			IO0SET|=(1<<0);
			IO0CLR|=(1<<1);
			IO0SET|=(1<<2);
			IO0CLR|=(1<<3);
		}
		else if(IO0PIN&(1<<17))//backward
		{
			IO0SET|=(1<<1);
			IO0CLR|=(1<<0);
			IO0SET|=(1<<3);
			IO0CLR|=(1<<2);
		}
		else if(IO0PIN&(1<<18))//right
		{
			IO0SET|=(1<<0);
			IO0CLR|=(1<<1);
			IO0CLR|=(1<<2);
			IO0CLR|=(1<<3);
		}
		else if(IO0PIN&(1<<19))//left
		{
			IO0CLR|=(1<<0);
			IO0CLR|=(1<<1);
			IO0SET|=(1<<2);
			IO0CLR|=(1<<3);
		}
		else 
		{
			IO0CLR|=0xf;
		}
		
	}
}