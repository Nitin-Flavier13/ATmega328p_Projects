void init_port(void);
void outport(char);
void outportc(char);
char inportb(void);
void TIMER1_Delay(char );

void TIMER1_Delay(char z)
{
  char *TIMER1_TCCRA1=(char *)0x80; // WGM 10, 11
  char *TIMER1_TCCRB1=(char *)0x81; // WGM 13, 12, CLK prescaler
  short *TIMER1_TCNT1=(short *)0x84;
  short *TIMER1_OCRA1=(short *)0x88;
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
  char *dir_c=(char *)0x27;
  *dir_d=0xFC;
  *dir_b=0x03;
  *dir_c=0x1F;
}

char inportb(void)
{
  volatile char *in_b=(volatile char *)0x23;
  volatile char z;
  z=*in_b;
  return z>>3;
}

void outport(char z)
{
  volatile char *out_d=(volatile char *)0x2B;
  volatile char *out_b=(volatile char *)0x25;
  *out_d=z<<2;
  *out_b=(z>>6)|0x02;
}

void outportc(char z)
{
  volatile char *out_c=(volatile char *)0x28;
  *out_c=z;
}