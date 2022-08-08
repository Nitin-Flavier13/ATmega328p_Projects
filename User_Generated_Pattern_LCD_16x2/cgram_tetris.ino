void init_port(void);
void outport(char );
void outportc(char);

void init_lcd(void);
void enable_lcd(void);
void write_lcd(char *);
void data(char z);
void own_character(char *);
void lcd_clear(void);

void setup() 
{
  init_port();
  init_lcd();
  char dots[][8]={{0x00,0x04,0x00,0x00,0x11,0x11,0x0A,0x0E},{0x00,0x00,0x00,0x04,0x11,0x11,0x0A,0x0E},{0x00,0x00,0x00,0x00,0x11,0x15,0x0A,0x0E},{0x02,0x0E,0x00,0x00,0x11,0x11,0x0E,0x0E},{0x00,0x00,0x02,0x0E,0x11,0x11,0x0E,0x0E},{0x0C,0x00,0x00,0x00,0x13,0x1F,0x0E,0x0E},{0x00,0x00,0x0C,0x00,0x13,0x1F,0x0E,0x0E},{0x00,0x00,0x00,0x00,0x1F,0x1F,0x0E,0x0E}};  
  own_character((char *)dots);
}
void own_character(char *d)
{
  char i=0;
  outport(0x40);  //setting cgram address RS=0 giving instruction
  enable_lcd();
  for(char j=0;j<8;j++)
  {
    for(char k=0;k<8;k++)
    {
      data(*(d+j*8+k));
    }
  }
  outport(0x82);
  enable_lcd();
  write_lcd("Let's Start");
  dely(3000);
  lcd_clear();
  for(char k=0;k<8;k++)
  {
    outport(0x87);
    enable_lcd();
    data(k);
    dely(1500);
  }
  outport(0xC2);
  enable_lcd();
  write_lcd("Nice   Game");
  dely(3000);
}
void lcd_clear(void)
{
  outport(0x01);
  enable_lcd();
}
void write_lcd(char *ptr)
{  
  char i=0;
   while(*ptr!=0)
   {
     data(*ptr);
     ptr++;
     i++;
     if(i==16)
     {
       outport(0xC0);
       enable_lcd();
     }
   }
}
void data(char z)
{
  outportc(0x02);
  dely(1);
  outport(z);
  outportc(0x03);
  dely(1);
  outportc(0x00);
  dely(1); 
}
void init_lcd()
{
  outport(0x38);enable_lcd();
  outport(0x01);enable_lcd();
  outport(0x02);enable_lcd();
  outport(0x06);enable_lcd();
  outport(0x0C);enable_lcd();
}
void enable_lcd()
{
  outportc(0x01);
  dely(10);
  outportc(0x00);
  dely(1);
  
}
void outportc(char cdata)
{
   volatile char *outport_c=(volatile char *)0x28;
   *outport_c = cdata;
}
void init_port()
{
  char *dir_port_d=(char *)0x2A;
  char *dir_port_b=(char *)0x24;
  char *dir_port_c=(char *)0x27;
  *dir_port_d=0xFC;
  *dir_port_b=0x03;
  *dir_port_c=0x03;
}
void outport(char data)
{
  volatile char *outport_d=(volatile char *)0x2B;
  volatile char *outport_b=(volatile char *)0x25;
  *outport_d= data<<2;
  *outport_b= data>>6;
  //Serial.print(*outport_d,BIN);

}
void dely(int l)
{
  volatile int i;
  while(l--)
  {
    for(i=0;i<600;i++);
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
