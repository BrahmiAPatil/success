#include<p18f4580.h> /* Header File Inclusion		             */
#include "pwm.h"
#define IN0 PORTDbits.RD0
#define IN1 PORTDbits.RD1
#define IN2 PORTDbits.RD2
#define IN3 PORTDbits.RD3
#define IN4 PORTDbits.RD4
#define IN5 PORTDbits.RD5
#define IN6 PORTDbits.RD6
#define IN7 PORTDbits.RD7
void delay(int a);
void write(unsigned char a);
void str(rom const char *s);
void delay(int a)
{
	int i,j;
	for(i=0;i<500;i++)
	for(j=0;j<a;j++);
}
void str(rom const char *s)
{
	
while(*s!='\0')
{
 write(*s);
while(PIR1bits.TXIF==0);
PIR1bits.TXIF=0;
s++;
}
}
void write(unsigned char data)
{
	while(!TXSTAbits.TRMT);
	TXREG=data;
}

void main()			        		
{
	char read;
    ADCON1	=	0X0F;
	TRISC	=	0x80;		        /* RC6=0 (O/P) RC7=1(I/P)			           */			
	TRISD	=	0X00;	
	SPBRG	=	0x19;		        /* Serial Port Baud rate Generator (9600)	   */
	TXSTA	=	0X24;		        /* Transmission Enabling(TXEN=1,SYNC=0,BRGH=1) */
	RCSTA	=	0X90;		        /* Rception Enabling (SPEN=1,CREN=1)		   */
	str("PRESS");//following buttons to move robot in respective directions")
	//str(10);
	str("1-forward direction");
	//str('10');
	str("2-reverse direction");
	//str('10');
	str("3-right direction");
	//str('10');
	str("4-left direction");
	//str('10');
					    
	while(1)
	{
	while(PIR1bits.RCIF==0);
	if(PIR1bits.RCIF==1)
	{
	PIR1bits.RCIF=0;
	read=RCREG;
	switch(read)
	{
		case '1'://str(0x0a);
			str("forward direction");
			PORTD=0X5A;
			
			break;
		case '2'://str(0x0a);
			str("reverse direction");
			PORTD=0xA5;
			
			break;	
		case '3'://str(0x0a);
			str("right direction");
			IN0=0;IN2=0;
			//pwm_delay(200);
			IN1=1;IN3=1;
			IN0=0;IN2=0;
			//pwm_delay(200);
			IN1=0;IN3=0;
			IN4=1;IN6=1;
			pwm_delay(49);
			IN5=0;IN7=0;
			//delay(500);
			break;
		case '4'://str(0x0a);
			str("left direction");
			IN0=1;IN2=1;
		//pwm_delay(49);
			IN1=0;IN3=0;
			IN4=0;IN6=0;
			pwm_delay(200);
			IN5=1;IN7=1;
			//delay(500);
			break;
		default :str(0x0a);
			str("wrong input");
		    PORTD=0X00;
		    //delay(500);
		    break;
		PIR1bits.RCIF=0;
	}
}
}
}