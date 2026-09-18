 #include<lpc21xx.h>
 #include<stdio.h>
  #include "header.h"
  #define c ((IOPIN0>>14)&1)
  #define c1 ((IOPIN0>>15)&1)
  #define green (1<<17)
  #define red (1<<18)
  int main()
  {
  unsigned int value=0;
  float vout=0,temp=0;
 char a[20]; 
   IODIR0=3<<17;
   lcd_init();
   uart0_init(9600);
   adc_init();
   while(1)
   {
   lcd_cmd(0x01);
   lcd_cmd(0x80);
   uart0_tx_string("temperature:");
   value=adc_read(1);
   vout=(value*3.3)/1023.0;
   temp=(vout-0.05)/0.01;
   sprintf(a,"temp:%.2f \r\n",temp);
   uart0_tx_string(a);
   lcd_string("Temp:");
   lcd_integer(temp);
 
 
   if(c==0){
   sprintf(a,"fire=yes\r\n");
   uart0_tx_string(a);
   }
   else
   {
   sprintf(a,"fire=no\r\n");
   uart0_tx_string(a);
   }
            ///pir
   if(c1==0){
   sprintf(a,"worker=yes\r\n");
   uart0_tx_string(a);
   }
   else
   {
   sprintf(a,"worker=no\r\n");
   uart0_tx_string(a);
   }
 
 
   //status
   lcd_cmd(0xc0);
   if((c1==1)||(c==0))
   {
 
   sprintf(a,"status:danger\r\n LED status:Red\r\n");
   uart0_tx_string(a);
   IOSET0=green;
   IOCLR0=red;
   lcd_string("Status:Danger\r\n");
    }
   else
   {
 
   sprintf(a,"status:safe\r\n LED status:green\r\n");
   uart0_tx_string(a);
   IOSET0=red;
   IOCLR0=green;
   lcd_string("Status:safe\r\n");
    }
      delay_ms(1000);
   }
  }
