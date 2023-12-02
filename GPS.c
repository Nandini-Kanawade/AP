//Introductory, Receive and Transmit complete strings
#include "lpc214x.h"
#include "stdio.h"
#include "string.h"
#include "uart.c"
void delay(unsigned int time){
	unsigned int i,j ;
	for(i=0;i<time;i++)
		for(j=0;j<5000;j++);
}
int main(){
	unsigned char temp;
	UART0Init();
	UART1Init();
	while(1)	{
		temp= UART_Getchar();
		UART0_putchar(temp);
	}
	while(1);
	return 0;
}


//--------------------------------------------------
//Part2, Extract only latitude and longitude
//UART.c:
 unsigned char UART0_putchar(unsigned char ch) {
 	if(ch=='\n'){
		while(!(U0LSR & 0x20));
		U0THR=0X0D;
	}
	while(!(U0LSR & 0x20));
	return(U0THR = ch);
}
unsigned char UART_Getchar(void){
	while(!(U1LSR & 0x01));
	return(U1RBR);
}
void UART0Init(){
	PINSEL0 |= 0x00000005;
	U0FCR = 0x07;
	U0LCR = 0x83;
	U0DLL = 0x62;
	U0DLM = 0;
	U0LCR = 0x03;
}
void UART1Init(){
	PINSEL0 |= 0x00050000;
	U1FCR = 0x07;
	U1LCR = 0x83;
	U1DLL = 0x62;
	U1DLM = 0;
	U1LCR = 0x03;
}


//PART2
#include"lpc214x.h"
#include"stdio.h"
#include"string.h"
#include"UART0.c"
#include"UART1.c"
unsigned char message_1[36] = "GPS program - UART initialized\n";
unsigned char message_2[36] = "\n Invalid GPS string"; 
unsigned char lat_msg[36] = "\n Latitude = ";
unsigned char long_msg[36]= "\n Longitide = ";
unsigned char rcv_byte,count;
unsigned char rcv_array[30];
// delay function
void delay(unsigned int time){ 
	unsigned int i,j;
	for(i=0;i<time;i++) 
	for(j=0;j<5000;j++);
} 
int main(){
	UART0Init(); //UART 0 is user interface
	UART1Init(); //UART 1 -> GPS
	UART0_PutS(message_1);
	while(1){ 	
		// for $
		while(rcv_byte!='$'){
			rcv_byte = UART1_GetChar();
			UART1_PutChar(rcv_byte);
		};
		rcv_byte = UART1_GetChar(); //G (not checking)
		UART1_PutChar(rcv_byte);
		rcv_byte = UART1_GetChar(); //P (not checking)
		UART1_PutChar(rcv_byte);
		rcv_byte = UART1_GetChar(); // next character
		UART1_PutChar(rcv_byte);
		if(rcv_byte == 'R'){
			for(count=0;count<14;count++){
				rcv_byte = UART1_GetChar();
			};
			rcv_byte = UART1_GetChar(); // A/V 19th char (A- valid ; V- invalid)
			UART1_PutChar(rcv_byte);
			if(rcv_byte == 'V'){ // checking data validity 
				UART0_PutS(message_2); 
				delay(30000);
			} 
			else{
				rcv_byte = UART1_GetChar();
				UART1_PutChar(rcv_byte);
				for(count=0;count<24;count++){
					rcv_byte = UART1_GetChar(); 
					rcv_array[count] = rcv_byte;
					UART1_PutChar(rcv_byte);
				};				
				UART0_PutS(lat_msg);
				for(count=0;count<10;count++){
					UART0_PutChar(rcv_array[count]); // Latitude 
				};				
				UART0_PutS(long_msg);
				for(count=12;count<23;count++){
					UART0_PutChar(rcv_array[count]); // Longitude 
				};
			}
		}
	}
}

//UART0.c File:
void UART0Init(){ //initialise UART0 
	PINSEL0 |=0x00000005; //select TxD0: bit 1:0=01,& RxD0: bit 3:2=01 U0FCR=0x07; // Enable FIFO, clear Rx & Tx FIFO, Write 1 character at a time
	U0LCR=0x83; // select 8-bit character, one stop bit, enable divisor latch access
	U0DLL=0x62; // Baud rate=9600
	U0DLM=0;
	U0LCR=0x03;
}
unsigned char UART0_PutChar(unsigned char Ch){ //transmit from UART0
	if(Ch=='\n') { 
		while(!(U0LSR & 0x20)); 
		U0THR=0x0D;
	} 
	while(!(U0LSR & 0x20));
	return(U0THR=Ch);
}
	
void UART0_PutS(unsigned char *ch){ //Displaying on serial window 
	while(*ch){
		UART0_PutChar(*ch++);
	}
}

//UART1.c File:
void UART1Init(){ //initialise UART1
	PINSEL0 |=0x00050000; //select TxD1: bit 1:0=01,& RxD1: bit 3:2=01 
	U1FCR=0x07; // Enable FIFO, clear Rx & Tx FIFO, Write 1 character at a time
	U1LCR=0x83; // select 8-bit character, one stop bit, enable divisor latch access 
	U1DLL=0x62; // Baud rate=9600 
	U1DLM=0; 
	U1LCR=0x03;
}
unsigned char UART1_PutChar(unsigned char Ch){ //transmit from UART1
	while(!(U1LSR & 0x20));
	if(Ch=='\n')
		Ch=0x0D;
	U1THR=Ch;
	return Ch;
}
void UART1_PutS(unsigned char *Ch){
	while(*Ch)
	UART1_PutChar(*Ch++);
}
unsigned char UART1_GetChar(void){ //receive character from UART0
	while(!(U1LSR & 0x01));
	return(U1RBR);
} 
