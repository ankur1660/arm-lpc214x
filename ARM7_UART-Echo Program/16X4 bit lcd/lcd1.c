 #include<lpc214x.h>
 #define rs 16
 #define rw 17
 #define en 18
 void delay(int x)
 {
	 int i,j;
	 for(i=0;i<x;i++)
	 {
		 for(j=0;j<100;j++)
			{}
		}
}
void lcdcmdwrite()
{
	IO0CLR|=(1<<rs);
	IO0CLR|=(1<<rw);
	IO0SET|=(1<<en);
	delay(100);
	IO0CLR|=(1<<en);
	delay(100);
}	
void lcd_cmd(char x)
{
	IO0SET|=((x&0xf80000)>>1);
	lcdcmdwrite();
	IO0CLR|=((x&0xf80000)>>1);
	IO0SET|=(((x<<20)&0xf8000)>>1);
	lcdcmdwrite();	
	IO0CLR|=(((x<<20)&0xf80000)>>1);
}
void lcddatawrite()
{
	IO0SET|=(1<<rs);
	IO0CLR|=(1<<rw);
	IO0SET|=(1<<en);
	delay(100);
	IO0CLR|=(1<<en);
	delay(100);
}
void lcddata(char x)
{
	IO0SET|=((x&0xf80000)>>1);
	lcddatawrite();
	IO0CLR|=((x&0xf80000)>>1);
	IO0SET|=(((x<<20)&0xf8000)>>1);
	lcddatawrite();	
	IO0CLR|=(((x<<20)&0xf80000)>>1);
}
void lcd_ini()
 {
	 IO0DIR=IO0DIR|0x7f;
	 lcd_cmd(0x02);//to initalize lcd in 4-bit
	 lcd_cmd(0x28);//to initalize lcd 2 lines ansd 4-bit moce
	 lcd_cmd(0x0e);//display on cursor
	 lcd_cmd(0x06);//shift cursor right
	// lcd_cmd(0x01);//clear display
	 lcd_cmd(0x80);//force cursor to start position
		
}
void lcd_string(char *x)
 {
	 while(*x!='\0')
	 {
		 lcddata(*x);
		 x++;
	}
}


int main()
 {
	 IO0DIR=0xffffffff;
	 lcd_ini();
	lcd_string("Ankur Singh");
	 while(1)
	 {
			lcd_cmd(0x18);
		 delay(10);
	 }
 }