#include <LPC213X.H>

unsigned char x;

unsigned char serial_Rx()                                                    // RECIEVER function
{
 while((U0LSR & 0X01) == 0);
 x=U0RBR;
 return (x);
 }

void serial_Tx(unsigned char A)                                         // TRANSMIT function
 {
 U0THR=A; 
 while((U0LSR&(1<<5))==0);
 }
 
 
void delay (unsigned int m)                                                // TIMER0 delay function
{
T0MCR=0X04;
T0MR0=3000*m;
T0TC=0X00;
T0TCR=0X01;
while(T0TC<T0MR0);
T0TC=0X00;
}


 int main()
 {
	 int data;
 IODIR0=(1<<16);
 PINSEL0=0x05;
 U0LCR=0X83;
 U0DLL=((3000000/(16*9600))%256);
 U0DLM=((3000000/(16*9600))/256);
 U0LCR=0X03;
 U0FCR=0X07;
 while(1)
 {
 data=serial_Rx();
 if  (data=='A')
  {
  IOSET0=(1<<16);
  delay(100);
    }
  else if(data=='B')
     {
     IOCLR0=(1<<16);
     delay(100);
     }
     serial_Tx(data);
      }
		}
	
