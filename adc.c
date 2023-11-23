UART0ADC.c:
void Uart0Init()	  		

{

	PINSEL0 |= 0X000000005;

	U0FCR = 0X07;

	U0LCR = 0X83;

	U0DLL = 0X62;			

	U0DLM = 0;

	U0LCR = 0X03;

}


int UART0_GetChar(void)
{
	while(!(U0LSR & 0x1));
return(U0RBR);
}

int UART0_PutChar(unsigned char Ch)
{
 if (Ch == '\n')  {
    while (!(U0LSR & 0x20));
    U0THR = 0x0D;                          /* output CR */
}

  while(!(U0LSR & 0x20));
return( U0THR = Ch);
}


int fputc(int ch, FILE *f) {
  return (UART0_PutChar(ch));
}

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;



MAINADC.c:
#include "LPC214x.h"
#include "stdio.h"
#include "uart0adc.c"

void adcdelay(unsigned int time)
{
unsigned int i,j;
	for(i = 0; i < time ;i++ )
	{		for(j = 0; j < 10000 ; j++);
	}
}

void ADCInit(void)
{
 PINSEL1 = 0x01000000; //P0.28 - AD0.1
 AD0CR = 0x00200302;		// ADC control register settings
 }

int main(void)
{
unsigned int adc_data;
unsigned char adc_ASCII[3], i, number;

Uart0Init();									//UartInit(9600);
ADCInit();                  // Init ADC

 while(1)
 {
	AD0CR = 0x01200302; 					                          // SOC
 	while((AD0DR1 & 0x80000000) != 0x80000000); //Wait till EOC - check DONE bit D31
	printf("\nADC Value(hex)= ");                             // o/p on serial
	adc_data = (AD0DR1 & 0x0000FFC0)>>6;         // Read data - 
	adcdelay(100);                                                 // delay
	adc_ASCII[2] = (adc_data & 0x0000000F);        // Seperate three Nibble
	adc_ASCII[1] = (adc_data & 0x000000F0)>>4; 
	adc_ASCII[0] = (adc_data & 0x00000F00)>>8;
   	printf("   \r");                                                                    // Now conver nibble to ASCII
	for (i=0;i<3;i++)
	{
	   if((0 <= adc_ASCII[i] && adc_ASCII[i] <= 9))
		{
		number = adc_ASCII[i] + 0x30;
		}
		if((0xA <= adc_ASCII[i] && adc_ASCII[i] <= 0xF))
		{
		number = adc_ASCII[i] + 0x37;
		}

	 UART0_PutChar(number);                                     // o/p result on serial
	}
	printf("   \r");
	}
} 
