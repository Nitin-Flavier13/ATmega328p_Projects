void init_port(void);
void TIMER1_Delay(char );
void outport(char );

void TIMER1_Delay(char z)
{
  char *TIMER1_TCCRA1=(char *)0x80; // WGM 10, 11
  char *TIMER1_TCCRB1=(char *)0x81; // WGM 13, 12, CLK prescaler
  short *TIMER1_TCNT1=(short *)0x84;
  short *TIMER1_OCRA1=(short *)0x88;
  //char *TIMER1_TIMSK1=(char *)0x6F;
  volatile char *TIMER1_TIFR1=(volatile char *)0x36;

  *TIMER1_TIFR1=0;
  *TIMER1_TCNT1=0;
  *TIMER1_TCCRA1=0;
  *TIMER1_TCCRB1=0x0C;
  *TIMER1_OCRA1=31*2*z;
  while(((*TIMER1_TIFR1)&0x02)==0);

}
void init_port(void)
{
  char *dir_d=(char *)0x2A;
  char *dir_b=(char *)0x24;
  *dir_d=0xFC;*dir_b=0x03;
}
void outport(char x)
{
  volatile char *outport_d=(volatile char *)0x2B;
  volatile char *outport_b=(volatile char *)0x25;
  *outport_d=x<<2;
  *outport_b=x>>6;
}