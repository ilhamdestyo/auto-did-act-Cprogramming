#include "io.h"
#include "mytimer.h"

#define myLCD PORTA

float FCPU = 1;

void serial_init();
void serial_tr(unsigned char);
void serial_tr_bcd(unsigned char);

void i2c_init();
void i2c_start();
void i2c_wr(unsigned char);
unsigned char i2c_re(unsigned char);
void i2c_stop();

void rtc_init();
void rtc_set_t(unsigned char, unsigned char, unsigned char);
void rtc_set_d(unsigned char, unsigned char, unsigned char);
void rtc_get_t(unsigned char*, unsigned char*, unsigned char*);
void rtc_get_d(unsigned char*, unsigned char*, unsigned char*);

void cmd(unsigned char x);
void lcd_display(unsigned char x);
void lcd_init();
void lcd_str(unsigned char *str);
void lcd_pos(int line,int pos);

int main()
   {
  
       unsigned char i,j,k,p,q,r;
       DDRA=0XFF;
       DDRB=(1<<PB0)|(1<<PB1)|;
       rtc_init();
       //rtc_set_t(0x19,0x45,0x30); 
       //rtc_set_d(0x09,0x01,0x10);
       
       serial_init();
       lcd_init();
       lcd_str("TIME ");
       lcd_pos(2,0);
       lcd_str("DATE ");
       while(1) 
          {
                 /* time
**************************************************************************/
               lcd_pos(1,6);
               rtc_get_t(&i,&j,&k);
               lcd_display('0'+(i>>4));
               lcd_display('0'+(i & 0x0f));
               lcd_display(':');

               lcd_display('0'+(j>>4));
               lcd_display('0'+(j & 0x0f));
               lcd_display(':');

               lcd_display('0'+(k>>4));
               lcd_display('0'+(k & 0x0f));
               delay_ms(50);

  /* date
****************************************************************************/

              lcd_pos(2,6);
              rtc_get_d(&p,&q,&r);
              lcd_display('0'+(r>>4));
              lcd_display('0'+(r & 0x0f));
              lcd_display('-');

              lcd_display('0'+(q>>4));
              lcd_display('0'+(q & 0x0f));
              lcd_display('-');

              lcd_display('0'+(p>>4));
              lcd_display('0'+(p & 0x0f));
              delay_ms(500);

         }
       return 0;
   }

//EEPROM Function register
void serial_init()
   {
       UCSRB=(1<<TXEN);
       UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
       UBRRL=0X33;
    }
    
//USART Function register
void serial_tr(unsigned char x)
   {
       while(!(UCSRA & (1<<UDRE)));
       UDR= x; 
       while(TXC ==0);
   }

void serial_tr_bcd(unsigned char x)
   {
       serial_tr('0'+(x>>4));
       serial_tr('0'+(x & 0x0f));
   }


void i2c_init()
   {
       TWSR=0X00; //Status register 
       TWBR=0X47; //Bit rate register
       TWCR=0X04; //enables the TWI interface in the device and takes control over the I/O pins.
   }

void i2c_start()
  {
      TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
      while((TWCR &(1<<TWINT))==0);
  }
//I2CWrite
void i2c_wr(unsigned char x)
  {
	    uint8_t status;
     TWDR=x;/* Copy data in TWI data register */
     TWCR=(1<<TWINT)|(1<<TWEN);/* Enable TWI and clear interrupt flag */
     while(!(TWCR & (1<<TWINT)));
     status=TWSR&0xF8;		/* Read TWI status register */
		if(status==0x28)		/* Check for data transmitted &ack received */
		return 0;			/* Return 0 to indicate ack received */
		if(status==0x30)		/* Check for data transmitted &nack received */
		return 1;			/* Return 1 to indicate nack received */
		else
		return 2;	/* Else return 2 for data transmission failure */

  }
//I2CRead
unsigned char i2c_re(unsigned char x)
   {
       TWCR=(1<<TWINT)|(1<<TWEN)|(x<<TWEA);/* Enable TWI, generation of ack */
       while(!(TWCR &(1<<TWINT)));/* Wait until TWI finish its current job */
       return TWDR;/* Return received data */
   }
//I2CStop
void i2c_stop()
   {
       TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);/* Enable TWI, generate stop */
       for(int i=0;i<200;i++);
       
   }

//RTC function
void rtc_init()
   {
      i2c_init();
      i2c_start();
      i2c_wr(0xD0);   // address DS1307 for write
      i2c_wr(0x0);   // address DS1307 for write
      i2c_wr(0x07);  //set register pointer to 7
      i2c_wr(0x00);  //set value of location 7 to 0
      i2c_stop();  // transmit stop condition
   }

void rtc_set_t(unsigned char h,unsigned char m,unsigned char s)
   {
       i2c_start();
       i2c_wr(0xd0);     // address DS1307 for write
       i2c_wr(0);        //set register pointer to 0
       i2c_wr(s);
       i2c_wr(m);
       i2c_wr(h);
       i2c_stop();
   }

void rtc_set_d(unsigned char y,unsigned char m,unsigned char d)
   {
       i2c_start();
       i2c_wr(0xd0);     // address DS1307 for write
       i2c_wr(4);        //set register pointer to 4
       i2c_wr(d);
       i2c_wr(m);
       i2c_wr(y);
       i2c_stop(); 
   }

void rtc_get_t(unsigned char *h,unsigned char *m,unsigned char *s)
   {
       i2c_start();
       i2c_wr(0xd0);     // address DS1307 for write
       i2c_wr(0);        //set register pointer to 0
       i2c_stop();

       i2c_start();
       i2c_wr(0xD1);     // address DS1307 for read
       *s=i2c_re(1);     //read sec ,read ack
       *m=i2c_re(1);     //read min ,read ack
       *h=i2c_re(0);     //read hour ,read nack
       i2c_stop();
   }


void rtc_get_d(unsigned char *y,unsigned char *m,unsigned char *d)
    {
        i2c_start();
        i2c_wr(0xD1);     // address DS1307 for write
        i2c_wr(0);        //set register pointer to 4
        i2c_stop();


        i2c_start();
        i2c_wr(0xd1);     // address DS1307 for read
        *d=i2c_re(1);     //untuk baca hari ,read ack
        *m=i2c_re(1);     //untuk baca bulan,read ack
        *y=i2c_re(0);     //untuk baca tahun,read nack
        i2c_stop();
    }

void cmd(unsigned char x)
   {
       myLCD=x;
       PORTB=(0<<0);
       PORTB=(0<<1);
       PORTB=(1<<2);
       delay_ms(10);
       PORTB=(0<<2);

   }

void lcd_display(unsigned char x)
   {
      myLCD=x;
      PORTB=(1<<0);
      PORTB=(0<<1)|(1<<0);
      PORTB=(1<<2)|(0<<1)|(1<<0);
      delay_ms(20);
      PORTB=(0<<2)|(0<<1)|(1<<0);
   }

void lcd_init()
   {
       cmd(0x38);
       cmd(0x0e);
       cmd(0x01);
       cmd(0x06);
       cmd(0x80);
   }

void lcd_str(unsigned char *str)
   {
        while(*str!='\0')
          {
               lcd_display(*str);
               str++;
           }
    }

void lcd_pos(int line,int pos)
    {
        if(line==1)
            cmd(0x80+pos);
        else if(line==2)
            cmd(0xc0+pos);
    }
