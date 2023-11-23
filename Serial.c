//Serial transmission of a character only
#include <lpc214x.h>
void delay(unsigned int time){
	  int i,j;
	  for(i=0;i<time;i++)
	  for(j=0;j<2000;j++);
	}

void UART_Init(){
     PINSEL0 |=0x00000005;
     U0FCR = 0x07;		  //fifo control
	 U0LCR = 0x83;	 //line ctrl, for baud rate
	 U0DLL=0x62;		 //br
	 U0DLM=0x00;	 //br
	 U0LCR = 0x03;	 // to latch BR 
}

int main(){
 	UART_Init();
	U0THR = 'A';

	while(!(U0LSR & 0x20))
	while(1);			 //to print A only once
	return 0;
 }

//Serial transmission of a string
#include <lpc214x.h>

void delay(unsigned int time)
	{
	  int i,j;
	  for(i=0;i<time;i++)
	  for(j=0;j<2000;j++);
	}

 void UART_Init(){
     PINSEL0 |=0x00000005;
     U0FCR = 0x07;		  //fifo control
	 U0LCR = 0x83;		  //line ctrl, for baud rate
	 U0DLL = 0x62;		 //br
	 U0DLM = 0x00;	   //br
	 U0LCR = 0x03;	  // to latch BR 
}

int main(){
 	unsigned int i;
	unsigned char transmit[15] = "Pooja Aslesha";
	UART_Init();
	for(i = 0; transmit[i] != '\0'; i++){
	   while(!(U0LSR&0x20));  // wait till THR is empty
	   U0THR = transmit[i];	  //Display transmit only once
	 }
 }

//Serially transmit and receive
#include <lpc214x.h>
void UART_Init(){
     PINSEL0 |=0x00000005;
     U0FCR = 0x07;		  //fifo control
	 U0LCR = 0x83;		  //line ctrl, for baud rate
	 U0DLL = 0x62;		 //br
	 U0DLM = 0x00;	   //br
	 U0LCR = 0x03;	  // to latch BR 
}

void tx_recieve(){
	unsigned char i, rev_data[100];
	for(i = 0; i < 100; i++){
		  while(!(U0LSR&0x01));
		  rev_data[i] = U0RBR;
		  while(!(U0LSR&0x20));
		  U0THR = rev_data[i];
	}
	while(1);
}

int main(){
 	  UART_Init();
	  tx_recieve();
	  return 0;	
 }


