#include<lpc214x.h>
#define RS 16
#define RW 17
#define EN 18
#define DLAB 7
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
//***********UART INITALIZATION************//
void uart_init()
{
	// U0LCR|=(1<<DLAB);
	// U0DLL=93;
	// U0DLM=00;
	// U0LCR=0x03;
	// U0LCR=(U0LCR&~(1<<DLAB));
	

	PINSEL0|=5;
	U0LCR=0x83;        //(1<<DLAB);
	U0DLL=97;
	U0DLM=0x00;
	U0LCR=0x03;//8 bit data
	U0FCR=0x07;
	U0LCR=(U0LCR&~(1<<DLAB));
}
	 
void write(char data)
	{
	U0THR=data;
	while((U0LSR&(1<<5))==0);
	 
	}
char read()
	{
	 char a;
	 while((U0LSR&(1<<0))==0);
	 a=U0RBR;
	 return a;
	}
void tx_string(char *str)
{
	while(*str)
	{
		write(*str);
		str++;
		delay(100);
	}
}

int main()
{
	char i,j=0,k=0,a[12],b[12]="0D0076A73CE0",c[12]="120088F25530";//card number
	int m,l;
	Lcd_Init();
	uart_init();
	PINSEL0=0x05;
	PINSEL1=0x00000000;
	while(1)
	{
	Lcd_String("RFID attendence");
	Lcd_Cmd(0xC0);
	Lcd_String("Swipe your Card");
	for(i=0;i<12;i++) //reading RFID tag number
	{
		a[i]=read();
		if(b[i]==a[i])
		j++;
		if(c[i]==a[i])
		k++;
	}
	if(j==12) //check for authenciation for b[i]
	{
		l++;
		Lcd_String("Person 1");
		Lcd_String("Attendence");
		//Lcd_String(11,,l,2);
		delay(1000);
	}
	else if(k==12) //check for authenciation for c[i]
	{
		m++;
		Lcd_String("Person 2");
		Lcd_String("Attendence");
	//	Lcd_String(11,1,m,2);
		delay(1000);
	}
	else
	{
		Lcd_String("Card not match");
		Lcd_String("Unkonwn Person");
		delay(1000);
	}

	}
}

