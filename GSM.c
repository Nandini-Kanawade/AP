#include "lpc214x.h"
#include <stdio.h>
#include <string.h>
#include "uartgsm.c"
void delay(unsigned int time){
	unsigned int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<5000;j++);
	}
}
void GSM_cmd(unsigned char *cmd){
	uart1_Puts(cmd);
	delay(100);
}
int main(){
	unsigned char *msg= "Hello Cummins \n\r"; 
	uart0_init();
	uart1_init();
	uart0_Puts( "\n GSM Program");
	
	//dial a number and then disconnect
	GSM_cmd("ATD7499989871;\n\r");
	uart0_Puts("ATD7499989871;\n"); 
	delay(20000);
	GSM_cmd("ATH0\r");
	uart0_Puts("ATH0");
	delay(3000);
	
	//SMS transmit
	GSM_cmd("AT+CMGF=1\n\r");
	uart0_Puts("AT+CMGF=1\n\r");
	delay(1000);
	GSM_cmd("AT+CMGS=\"07499989871\"\n\r");
	uart0_Puts("AT+CMGS=\"07499989871\"\n\r");
	delay(1000);
	uart1_Puts(msg);
	delay(1000);
	uart1_PutChar(0x1A);
	delay(60000);
	delay(60000);
	delay(60000);
}

//UART.c File:
unsigned char UART0_PutChar(unsigned char Ch){
	if(Ch == '\n'){
		while (!(U0LSR & 0x20));
		U0THR = 0x0D;
	}
	while(!(U0LSR & 0x20));
	return(U0THR = Ch);
}
unsigned char uart1_GetChar(void){
	while(! (U1LSR & 0x01));
	return(U1RBR);
}
void uart0_init(){
	PINSEL0 |= 0x00000005;
	U0FCR = 0x07;
	U0LCR = 0x83;
	U0DLL = 0x62;
	U0DLM = 0;
	U0LCR = 0x03;
}
void uart1_init(){
	PINSEL0 |= 0x00050000;
	U1FCR = 0x07;
	U1LCR = 0x83;
	U1DLL = 0x62;
	U1DLM = 0;
	U1LCR = 0x03;
}
unsigned char uart1_PutChar(unsigned char ch){
	while(!(U1LSR & 0x20));
	if(ch=='\n')
	ch==0x0D;
	U1THR= ch;
	return ch; 
}
void uart1_Puts(unsigned char *ch){
	while(*ch){
		uart1_PutChar(*ch++);
	}
}
void uart0_Puts(unsigned char *ch){
	while(*ch){
		UART0_PutChar(*ch++);
	}
}
