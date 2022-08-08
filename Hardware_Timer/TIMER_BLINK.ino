#include "flavier.h"
char i=1,l[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
char m[8]={1,2,3,4,5,6,7,8};
void setup() 
{
  init_port();
  led_blink();
}
void led_blink(void)
{
  char data=0;
  while(1)
  {
    for(char j=0;j<8;j++)
    {
      if(i%m[j]==0)
      {
        data|=l[j];
      } 
    }
    outport(data);
    TIMER1_Delay(1000);
    outport(0x00);
    TIMER1_Delay(100);
    i++;data=0;
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
