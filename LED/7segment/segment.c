#include<lpc214x.h>
//char a[]={(1<<0),(1<<4)};
int main()
{
	IO0DIR=IO0DIR|(0x0f);
	if(((IO0PIN&(1<<16)))|((IO0PIN&(1<<17))))//forward
	{
		//IO0CLR=IO0CLR|(0x0a);
		IO0SET=IO0SET|(0x05);
	}
	if((IO0PIN!=(1<<16))&&(IO0PIN!=(1<<17)))//backward
	{
		IO0SET=IO0SET|(0x0a);
		
	}
	if((IO0PIN&(1<<16))&&(IO0PIN!=(1<<17)))//right
	{
			IO0SET=IO0SET|(0x01);
			IO0CLR=IO0CLR|(0x0f);
	}
	if((IO0PIN&=~(1<<16))&&(IO0PIN&(1<<17)))//left
	{
		IO0SET=IO0SET|(0x04);
		IO0CLR=IO0CLR|(0x0b);
	}
	else
	{
		IO0CLR=IO0CLR|(0x0f);
	}
	
}
	