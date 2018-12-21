 #include<lpc214x.h>
 #define rs 0
 #define rw 1
 #define e 2
 void lcd_cmd(char);
 void delay(int);
 void lcd_display();
 void lcd_data_cmd(char);
 void lcd_string(char *);
 int main()
 {
	 IO0DIR=0xfff;
	 lcd_display();
	 lcd_string(" Hello Avinsh, How are You !!!");
	 while(1)
	 {
		 lcd_cmd(0x18);
		 delay(10);
	 }
 }
 void lcd_display()
 {
	 lcd_cmd(0x38);
	 lcd_cmd(0x0e);
	 lcd_cmd(0x18);
		
}
 void lcd_cmd(char cmd)
 {
	 IO0SET|=(cmd<<3);
	 IO0CLR|=(1<<rs);
	 IO0CLR|=(1<<rs);
	 IO0SET|=(1<<e);
	 delay(100);
	 IO0CLR|=(1<<e);
	 delay(100);
	 IO0CLR|=(cmd<<3);
	 
	 
 }
 void lcd_data_cmd(char data)
 {
	 IO0SET|=(data<<3);
	IO0SET|=(1<<rs);
	IO0CLR|=(1<<rw);
	IO0SET|=(1<<e);
	delay(100);
	IO0CLR|=(1<<e);
	 delay(100);
	IO0CLR|=(data<<3);
 }
 
 
 void delay(int x)
 {
	 int i,j;
	 for(i=0;i<1000;i++)
	 {
		 for(j=0;j<100;j++)
			{}
		}
}
void lcd_string(char *str)
 {
	 while(*str!='\0')
	 {
		 lcd_data_cmd(*str);
		 str++;
	}
}
 