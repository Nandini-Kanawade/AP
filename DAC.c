Dac initialization:
void dac_init()
	{
     PINSEL1 |= 1<<19;
	   DACR |= 1<< 16;
	}

Main File:
#include <lpc214x.h>
#include <stdio.h>
#include "dac_init.c"

void delay(unsigned int time)
{	 
		unsigned int j,i;
		for( j=0;j<time;j++)
		{
			for(i=0;i<100;i++);
		}
}

int main()
{
		while(1)
		{
			DACR = 0xFFC0;
			delay(2);
			DACR = 0x000;
			delay(2);	
	  }
}


Triangular Wave:
#include <lpc214x.h>
#define DACPinMask 1<<19
#define DAC_DataMask 0x0000FFC0
#define DataShift 6

void DAC_init()
{
	PINSEL1 |= (DACPinMask);
	DACR |= 1<<16;
}

void delay(unsigned int time)
{
	unsigned int i, j;
	for(i=0;i<time;i++)
	{
		for(j=0; j<1000; j++);
	}
}

int main(void)
{
	DAC_init();
	while(1)
	{
		for(int i=0; i<=1023 ; i++)
		{
			DACR=(1<<16 | i<<DataShift);
		}
		
		for(int i=1022; i>=1 ; i--)
		{
			DACR=(1<<16 | i<<DataShift);
		}
	}
}

Sawtooth Wave:
#include <lpc214x.h>
#define DACPinMask 1<<19
#define DAC_DataMask 0x0000FFC0
#define DataShift 6

void DAC_init()
{
	PINSEL1 |= (DACPinMask);
	DACR |= 1<<16;
}

void delay(unsigned int time)
{
	unsigned int i, j;
	for(i=0;i<time;i++)
	{
		for(j=0; j<1000; j++);
	}
}

int main(void)
{
	DAC_init();
	while(1)
	{
		for(int i=1023; i>=1 ; i--)
		{
			DACR=(1<<16 | i<<DataShift);
		}
	}
}


Staircase Wave:
#include <lpc214x.h>
#define DACPinMask 1<<19
#define DAC_DataMask 0x0000FFC0
#define DataShift 6

void DAC_init()
{
	PINSEL1 |= (DACPinMask);
	DACR |= 1<<16;
}

void delay(unsigned int time)
{
	unsigned int i, j;
	for(i=0;i<time;i++)
	{
		for(j=0; j<1000; j++);
	}
}

int main(void)
{
	DAC_init();
	while(1)
	{
		for(int i=0; i<=1023 ; i += 200)
		{
			DACR=(1<<16 | i<<DataShift);
		}
	}
}

