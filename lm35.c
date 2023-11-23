Main File:
#include<LPC214x.h>
#include<float.h>
#include<math.h>

#include "UART0_prog.c"
#include "float_ascii.c"

unsigned int data, adc_data;
unsigned char data_rcv[3];
unsigned char count;
unsigned char result;
unsigned char message_1[] = "\n\rADC data in HEX = ";
unsigned char message_2[] = "\n\rTemperature = ";
unsigned char res[20];
unsigned char crlf_1[] = "\n\r";
float temperature;

void Init_ADC(void)
{ // channel 1 init
	PINSEL1 |= 0x01000000; // P0.28 - AD0.1 as input
	AD0CR = 0x00200302;

	// channel 2 init - LM 35 channel
	PINSEL1 |= 0x04000000; // P0.29 - AD0.2 as input
	AD0CR |= 0x00200304;

}

unsigned int Read_ADC_1(void)
{
	AD0CR=0x01200302;
	while ( !(AD0DR1 & 0x80000000) );
	data=((AD0DR1>>6)&0x3FF);
	return data;
}

unsigned int Read_ADC_2(void)
{
	AD0CR = 0x01200304; //enable both channels
	while ( !(AD0DR2 & 0x80000000) );
	data =((AD0DR2 >> 6) & 0x3FF);
	return data;
}

void hex_ascII_transmit()
{
	for(count=0;count<3;count++)
	{
		if(data_rcv[count]<10)
		{
			result=data_rcv[count]+0x30;
			UART0_PutChar(result);
		}
		else
		{
			result=data_rcv[count]+0x37;
			UART0_PutChar(result);
		}
	}
	UART0_PutS(crlf_1);
}

void nibble_sep(void)
{
	data_rcv[2]=(adc_data & 0x0000000F);          // Lower nibble
	data_rcv[1]=(adc_data & 0x000000F0)>>4;       // middle nibble
	data_rcv[0]=(adc_data & 0x00000F00)>>8; // upper nibble
}

int main(void)
{
	Init_ADC();
	init_UART0();
	while(1)
	{    
		//channel 1 read
		adc_data = Read_ADC_1();
		nibble_sep();
		UART0_PutS(message_1);
		hex_ascII_transmit();

		// channel 2 read
		adc_data = Read_ADC_2();
		temperature = adc_data / 3.1; // CALIBRATION
		ftoa(temperature,res, 2);
		UART0_PutS(message_2);
		UART0_PutS(res);
	}
}


UART0:
void init_UART0(void)
{
	PINSEL0 |=0x00000005;
	U0LCR=0X83;

	U0DLM=0X00;
	U0DLL=0X62;

	U0LCR=0X03;
}

unsigned char UART0_PutChar(unsigned char Ch)
{
		if (Ch == '\n')  
	{
			while (!(U0LSR & 0x20));
			U0THR = 0x0D;                      
	}
		while(!(U0LSR & 0x20));
	return(U0THR = Ch);
}


void UART0_PutS(unsigned char *Ch)
{
	while(*Ch)
	UART0_PutChar(*Ch++);
}

Float_Ascii:
// C program for implementation of ftoa()
//  unsigned char res[20];
// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
 
 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '0';
    return i;
}
 
// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
intToStr((int)fpart, res + i + 1, afterpoint);  
    }
}
