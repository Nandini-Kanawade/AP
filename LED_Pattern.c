Flashing on off
#include <lpc214x.h>
#include "delay.c"

int main()
{
	  PINSEL2 = 0x00000000;
	  IODIR1 = 0xffffffff;

	  while(1)
	  {
	  	IOSET1 = 0xFFFFFFFF;
		delay(1000);
		IOCLR1 = 0xFFFFFFFF;
		delay(1000);
	  }
}

Delay.c
void delay(unsigned int time)
{
	unsigned int i, j;
	for(i = 0; i < 1500; i++)
		for(j = 0; j < time; j++);
}
