#include<LPC214x.h>
#define LCD_PORT 0x00FF0000
#define CS1 1<< 26
#define CS2 1<<27
#define GRST 1<<24
#define EN 1<<10

#define RS 1<<25
#define RW 1<<11

#define LCD_SHIFT 16


void delay(unsigned int time)
{
  int i , j;
  for(i =0; i<time;i++)
  for(j =0 ; j<10; j++);
  }
 
 void Ldelay(unsigned int time)
{
  int i , j;
  for(i =0; i<time;i++)
  for( j=0 ; j<5000; j++);
  }
 
  void LCD_strobe()
  {
    IO0SET = EN ;
delay(5);
IO0CLR = EN ;
delay(5);
  }
 
  void GLCD_data(unsigned char ch)
  {
   IOCLR1 = LCD_PORT;
   IOSET1 = ch <<LCD_SHIFT;
   IOSET1 = RS;
   LCD_strobe();
   }
   
   void GLCD_cmd(unsigned char ch)
  {
   IOCLR1 = LCD_PORT;
   IOSET1 = ch <<LCD_SHIFT;
   IOCLR1 = RS;
   LCD_strobe();
   }
 
  void GLCD_init()
  {
int i;
    PINSEL0 = 0;
PINSEL1= 0;
PINSEL2 = 0;

IODIR1= LCD_PORT | RS | CS1|CS2|GRST;
IODIR0 = EN | RW;
IOSET1 = GRST | CS1 | CS2;
IOCLR1 = RS;
IOCLR0 = EN | RW;

for(i =0; i<10; i++)
{
GLCD_cmd(0x3F);
GLCD_cmd(0x40);
GLCD_cmd(0xB8);
    }
}


int main()
{
GLCD_init();

 int i,j;
 for(i = 1; i<2; i++)
 {
 
  IO1SET = CS1;
IO1CLR = CS2;
  GLCD_cmd(0xB8 | i);
  for(j =55 ; j<64;j++)
  {
   GLCD_cmd(0x40|j);
   GLCD_data(0x00);
  }
 }
 
 for(i = 5; i<6; i++)
 {
 
  IO1SET = CS1;
IO1CLR = CS2;
  GLCD_cmd(0xB8 | i);
  for(j =55 ; j<64;j++)
  {
   GLCD_cmd(0x40|j);
   GLCD_data(0x00);
  }
 }
 
 for(i = 2; i<5; i++)
 {
 
  IO1SET = CS1;
IO1CLR = CS2;
  GLCD_cmd(0xB8 | i);
  for(j =59 ; j<64;j++)
  {
   GLCD_cmd(0x40|j);
   GLCD_data(0x00);
  }
 }
 
 for(i = 1; i<2; i++)
 {
  IO1SET = CS2;
IO1CLR = CS1;
 
  GLCD_cmd(0xB8 | i);
  for(j =63; j<72;j++)
  {
   GLCD_cmd(0x40|j);
   GLCD_data(0x00);
  }
 }
 
 for(i =5; i<6; i++)
 {
 
  IO1CLR= CS1;
  IO1SET = CS2;
  GLCD_cmd(0xB8 | i);
  for(j =63; j<72;j++)
  {
   GLCD_cmd(0x40|j);
   GLCD_data(0x00);
  }
  }
  for(i =2; i<5; i++)
 {
 
  IO1CLR= CS1;
  IO1SET = CS2;
  GLCD_cmd(0xB8 | i);
  for(j =63; j<68 ;j++)
  {
   GLCD_cmd(0x40|j);
   GLCD_data(0x00);
  }
 }
}

