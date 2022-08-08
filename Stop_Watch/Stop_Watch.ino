// Details
// D1 D2 D3 D4 are connected to the Cathode of the led.
// 7 LEDs to the Anode
// Top most button is for START -> 1st button
// Below it, is the STOP -> 2nd button
// Bottom one is for RESET -> 3rd button

#include "Ports.h"
void button(char,char,char,char,char);
void count(void);
void setter();

void setup() 
{
  init_port();
  count();
}

void button(char butn,char j,char i,char k,char m)
{
  char b[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F},d[4]={0x01,0x02,0x04,0x08};
  if(butn==1)
  {
    count();
  }
  else if(butn==2)
  {
    while(inportb()!=4)
    {
      outportc(~d[3]);
      outport(b[j]);
      TIMER1_Delay(12);outport(0x00);

      outportc(~d[2]);
      outport(b[i]);
      TIMER1_Delay(12);outport(0x00);

      outportc(~d[1]);
      outport(b[k]);
      TIMER1_Delay(12);outport(0x00);

      outportc(~d[0]);
      outport(b[m]);
      TIMER1_Delay(12);outport(0x00);
    }
    count();
  }
  else
  {
     count();
  }


}
void count(void)
{
  char b[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F},d[4]={0x01,0x02,0x04,0x08},inp;
  char hour_ones,hour_tens,min_ones,min_tens;
  setter();
  while(1)
  {
    for(char i=0;i<60;i++)
    {
      hour_ones=i%10;
      hour_tens=i/10;
      for(char j=0;j<60;j++)
      {
        min_ones=j%10;
        min_tens=j/10;
        for(int n=0;n<21;n++)
        {
          inp=inportb();
          if(inp!=0&&j>=1){button(inp,min_ones,min_tens,hour_ones,hour_tens);}

          outportc(~d[3]);
          outport(b[min_ones]);
          TIMER1_Delay(12);outport(0x00);

          outportc(~d[2]);
          outport(b[min_tens]);
          TIMER1_Delay(12);outport(0x00);

          inp=inportb();
          if(inp!=0&&j>=1){button(inp,min_ones,min_tens,hour_ones,hour_tens);}

          outportc(~d[1]);
          outport(b[hour_ones]);
          TIMER1_Delay(12);outport(0x00);

          outportc(~d[0]);
          outport(b[hour_tens]);
          TIMER1_Delay(12);outport(0x00);
        }
          
      }
    }
      
  }
}
void setter(void)
{
  TIMER1_Delay(80);
  outportc(0xF0);
  outport(0x3F);
  while(inportb()!=0x01);
}
void loop() {
  // put your main code here, to run repeatedly:

}
