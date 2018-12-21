#include <LPC214x.h>
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
void Lcd_Data(char data)
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
void Lcd_String(char *str)
{
	 while(*str!='\0')
	 {
		 Lcd_Data(*str);
		 str++;
	 }
}
int main()
{
	Lcd_Init();
	//Lcd_Cmd(0x80);
	//Lcd_Data(0x41);
	Lcd_Cmd(0x84);
	Lcd_String("working");
	Lcd_Cmd(0xC0);
	Lcd_String("lpc2148");
	for(;;)
	{
		 //Lcd_Cmd(0x18);
		 delay(2000);
	}
	return 0;
}
