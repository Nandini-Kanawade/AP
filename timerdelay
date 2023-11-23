#include<LPC214x.h>

void delay(unsigned int ms)
{
 T0PR=15000;
 T0TC=0;
 T0TCR=0x01;
 while(T0TC<ms);
 T0TCR=0x00;
}

void main()
{
int k;
 PINSEL2=0x00000000;
 IODIR1=0xFF000000;

 while(1)
 { 
 for(k=1;k<4;k++)
  {
	IOSET1 = 0x80000000 >> k | 0x01000000<<k;
	 delay(1000);
	IOCLR1 = 0x80000000 >> k | 0x01000000<<k;
 delay(1000);

 }
 for( k=0;k<4;k++)
 {
   	  IOSET1 = 0x08000000 >> k | 0x10000000<<k;
		  delay(1000);
		 IOCLR1 =  0x08000000 >> k | 0x10000000<<k;
		 delay(1000);
 }	
/*IOSET1=0xFF000000;
delay(1000);
IOCLR1=0xFF000000;
delay(1000);*/	 
}
}       
