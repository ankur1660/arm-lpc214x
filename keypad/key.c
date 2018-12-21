#include<lpc214x.h>
#define RS 16
#define RW 17
#define EN 18
void delay(unsigned int x)
{
	 int i,j;
	for(i=0;i<x;i++)
	for(j=0;j<1275;j++);
}

void Lcd_Cmd(char cmd);
void Lcd_Data(char data);
void Lcd_String(char *str);
void Lcd_Init();

void Lcd_Init()
{
	  PINSEL0=PINSEL1=0x00000000;
	  IO0DIR|=0xf0<<15;
	  IO0DIR|=(1<<RS)|(1<<RW)|(1<<EN);
	  Lcd_Cmd(0X02);
	  Lcd_Cmd(0X28); 
		Lcd_Cmd(0X06);
		Lcd_Cmd(0X01);
		Lcd_Cmd(0X80);
		Lcd_Cmd(0X0E);
	  delay(1000);
}
void Lcd_Cmd(char cmd)
{
	IO0SET|=(cmd&0xf0)<<15;//(cmd&0x780000);
	IO0CLR|=(1<<RS);//RS=0 FOR COMMAND
	IO0CLR|=(1<<RW);//RW=0 FOR COMMAND
	IO0SET|=(1<<EN);//EN=1
	delay(10);
	IO0CLR|=(1<<EN);//EN=0
  delay(10);	
	IO0CLR|=(cmd&0xf0)<<15;//)(cmd&0x780000);
	
	IO0SET|=((cmd<<4)&(0xf0))<<15;
	IO0CLR|=(1<<RS);//RS=0 FOR COMMAND
	IO0CLR|=(1<<RW);//RW=0 FOR COMMAND
	IO0SET|=(1<<EN);//EN=1
	delay(10);
	IO0CLR|=(1<<EN);//EN=0
  delay(10);	
	IO0CLR|=((cmd<<4)&(0xf0))<<15;
	
}
void lcd_data(char data)
{
	IO0SET|=(data&0xf0)<<15;
	IO0SET|=(1<<RS);//RS=1 FOR DATA
	IO0CLR|=(1<<RW);//RW=0 FOR DATA
	IO0SET|=(1<<EN);//EN=1
	delay(10);
	IO0CLR|=(1<<EN);//EN=0
  delay(10);	
	IO0CLR|=(data&0xf0)<<15;
	
	IO0SET|=((data<<4)&(0xf0))<<15;
	IO0SET|=(1<<RS);//RS=1 FOR DATA
	IO0CLR|=(1<<RW);//RW=0 FOR DATA
	IO0SET|=(1<<EN);//EN=1
	delay(10);
	IO0CLR|=(1<<EN);//EN=0
  delay(10);	
	IO0CLR|=((data<<4)&(0xf0))<<15;
	
}
char keypad()
{
	IO0CLR|=1<<4;  //case 1
	IO0SET|=(1<<5)|(1<<6)|(1<<7);
	if(!IO0PIN&(1<<0))
	{
		while(!IO0PIN&(1<<0));
		return '7';
		//delay(10);
	}
	if(!IO0PIN&(1<<1))
			return '4';
	if(!IO0PIN&(1<<2))
			return '1';
	if(!IO0PIN&(1<<3))
			return 'O';
	
	IO0CLR|=1<<5;  //case 2
	IO0SET|=0xd<<4;
	if(!IO0PIN&(1<<0))
			return '8';
	if(!IO0PIN&(1<<1))
			return '5';
	if(!IO0PIN&(1<<2))
			return '2';
	if(!IO0PIN&(1<<3))
			return '0';
	
	IO0CLR|=1<<6;  //case 3 <===
	IO0SET|=0xb<<4;
	if(!IO0PIN&(1<<0))
				return '9';
	if(!IO0PIN&(1<<1))
			return '6';
	if(!IO0PIN&(1<<2))
		 return '3';
	if(!IO0PIN&(1<<3))
			return'=';
	
	
	IO0CLR|=1<<7;  //case 4 <===
	IO0SET|=0x7<<4;
	if(!IO0PIN&(1<<0))
			return'/';
	if(!IO0PIN&(1<<1))
			return'*';
	if(!IO0PIN&(1<<2))
			return'-';
	if(!IO0PIN&(1<<3))
			return'+';
}
int main()
{
	IO0DIR|=0xff;
	Lcd_Init();
	while(1)
	{
		char c;
		c=keypad();
		lcd_data(c);
	}
}