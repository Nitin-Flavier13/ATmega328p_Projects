void init_port(void);
void outport_db(char);
void outportc(char);
char inportb(void);
void wait_until_press(void);
void dely(int);

void lcd_init(void);
void lcd_enable(void);
void write_lcd(char );
void clear_lcd(void);

char keypad_in(void);
void user_input_process(void);
void process(char u[],char ); // called under user_input_process()

void print_add(long );
void print_sub(long );
void print_mul(long long );
void print_div(long ,long );

void setup() 
{
  Serial.begin(9600);
  init_port();
  lcd_init();
  while(1)
  {
    user_input_process();
    dely(2000);
  }
}

void user_input_process(void)
{
  char z=0,w[15]={0},k=0;
  while(1)
  { 
   wait_until_press();
   z=keypad_in();
   z+=48;
   w[k]+=z;
   if(z!=61)
   {
     write_lcd(z);
   }
   else
   {
     break;
   }
   dely(1000);
   k++;
  }
  process(w,k);
  dely(1000);   //trying to make loop
  wait_until_press();//outport_db(0x3F);delay(3000);outport_db(0x00);delay(3000);
  z=keypad_in();
  while(z!=21)
  {
    wait_until_press();
    z=keypad_in();
    Serial.print(z,DEC);
    dely(10);
  }
  clear_lcd();
  //dely(4000);
  
/*  outport_db(0x80);
  lcd_enable();delay(1000);*/
}
void process(char u[15],char k)
{
  char a[7]={0},b[7]={0},sign;
  char f=0,g=0;
  long c=0,d=0;
  for(char i=0;u[i]>47;i++)
  {
    a[i]=u[i]-48;
    f++;
  }
  for(char j=f+1;j<k;j++)
  {
    b[j-f-1]=u[j]-48;
    g++;
  }
  sign=u[f];
  long lt=1;char h=0;
  while(f-h)
  {
    c+=lt*a[f-h-1];
    lt=10*lt;
    h++;
  }
  lt=1;h=0;
  while(g-h)
  {
    d+=lt*b[g-h-1];
    lt=10*lt;
    h++;
  }
  lt=0;char num[14]={0},op=0;
  if(sign==43)
  {
    lt=c+d;
    print_add(lt);
  }
  else if(sign==45)
  {
    lt=c-d;
    print_sub(lt);
  }
  else if(sign==42)
  {
    long long t;
    t=c*d;
    print_mul(t);
  }
  else if(sign==47)
  {
    print_div(c,d);
  }
}
char keypad_in(void)
{
  char r,c,h=2,colm,s[4][4]={{1,2,3,-5},{4,5,6,-3},{7,8,9,-6},{21,0,13,-1}};
  for(r=0;r<4;r++) 
  {
    outportc(1<<(r+h));
    for(c=0;c<4;c++)
    {
      colm=inportb();
      colm= colm>>2;
      if(colm==(1<<c))
      {
        outportc(0x00);
        return s[r][c];
      }
    }
  }
  outportc(0x00);
  return 0;
}
void write_lcd(char z)
{
  char i=0;
  while(i==0)//while(*ptr!=0)
  {
    outportc(0x02);
    outport_db(z);
    outportc(0x03);
    dely(10);
    outportc(0x00);
    dely(1);i++;
  }
}

void print_add(long lt)
{
  char num[14]={0},op=0;
  while(lt)
    {
        num[op]=lt%10;
        lt=lt/10;
        op++;
    }
    outport_db(0xC0);lcd_enable();
    for(char i=op-1;i>=0;i--)
    {
      write_lcd(num[i]+48);
    }
}
void print_sub(long lt)
{
  char num[14]={0},op=0;
  if(lt<0)
    {
      lt=lt*(-1);
      while(lt)
     {
        num[op]=lt%10;
        lt=lt/10;
        op++;
     }
     num[op]=-3;
     outport_db(0xC0);lcd_enable();
     for(char i=op;i>=0;i--)
     {
       write_lcd(num[i]+48);
     }
    }
    else
    {
      while(lt)
      {
        num[op]=lt%10;
        lt=lt/10;
        op++;
      }
      outport_db(0xC0);lcd_enable();
      for(char i=op-1;i>=0;i--)
      {
        write_lcd(num[i]+48);
      }
    }
}
void print_mul(long long t)
{
  char num[14]={0},op=0;
  while(t)
    {
      num[op]=t%10;
      t=t/10;
      op++;
    }
    outport_db(0xC0);lcd_enable();
    for(char i=op-1;i>=0;i--)
    {
      write_lcd(num[i]+48);
    }
}
void print_div(long c,long d)
{
  long lt;char num[14]={0},op=0;
  if(c>d)
  {
    lt=c/d;
    while(lt)
    {
      num[op]=lt%10;
      lt=lt/10;
      op++;
    }
    outport_db(0xC0);lcd_enable();
    for(char i=op-1;i>=0;i--)
    {
      write_lcd(num[i]+48);
    }
    op=0;lt=c%d;
    while(lt)
    {
      num[op]=lt%10;
      lt=lt/10;
      op++;
    }
    write_lcd(32);
    for(char i=op-1;i>=0;i--)
    {
      write_lcd(num[i]+48);
    }
  }
  else
  {
    outport_db(0xC0);lcd_enable();
    write_lcd(48);
    write_lcd(32);
    while(d)
    {
      num[op]=d%10;
      d=d/10;
      op++;
    }
    for(char i=op-1;i>=0;i--)
    {
      write_lcd(num[i]+48);
    }
  }  
}

void lcd_init(void)
{
  outport_db(0x01);
  lcd_enable();
  outport_db(0x38);
  lcd_enable();
  outport_db(0x0C);
  lcd_enable();
  outport_db(0x00);
  outport_db(0x06);
  lcd_enable();
}
void lcd_enable(void)
{
  outportc(0x01);
  dely(10);
  outportc(0x00);
  dely(1);
}
void clear_lcd(void)
{
  outport_db(0x01);
  lcd_enable();
  outport_db(0x02);
  lcd_enable();
}
void init_port(void)
{
  volatile char *dir_port_d=(volatile char *)0x2A;
  volatile char *dir_port_b=(volatile char *)0x24;
  volatile char *dir_port_c=(volatile char *)0x27;
  *dir_port_d=0xFC;
  *dir_port_b=0x03;
  *dir_port_c=0x3F;
}
void outport_db(char out)
{
  volatile char *outport_d=(volatile char *)0x2B;
  volatile char *outport_b=(volatile char *)0x25;
  *outport_d= out<<2;
  *outport_b= out>>6;
}
void outportc(char outc)
{
  volatile char *outport_c=(volatile char *)0x28;
  *outport_c=outc;
}
char inportb(void)
{
  volatile char *inport_b=(volatile char *)0x23;
  return *inport_b;
}
void wait_until_press(void)
{
  volatile char *inport_b=(volatile char *)0x23;
  outportc(0x3C);dely(100);
  while(*inport_b==0);
  Serial.print(*inport_b,DEC);
  outportc(0x00);
}
void dely(int num)
{
  volatile int i;
  while(num)
  {
    for(i=0;i<200;i++);
    num--;
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
