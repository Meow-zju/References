#include <iom128v.h>
#include "delay.h"
#include "Go.h"
#include <macros.h>

void Server1( unsigned int PWM, unsigned int DelayTime)		
{
	while(OCR1A<PWM)		
	{
		OCR1A++;
		delay_MS(DelayTime);
	}
	while(OCR1A>PWM)
	{
		OCR1A--;
		delay_MS(DelayTime);
	}
	
}

void Server2( unsigned int PWM, unsigned int DelayTime)		
{
	while(OCR1B<PWM)		
	{
		OCR1B++;
		delay_MS(DelayTime);
	}
	while(OCR1B>PWM)
	{
		OCR1B--;
		delay_MS(DelayTime);
	}
	
}

void Server3( unsigned int PWM, unsigned int DelayTime)		
{
	while(OCR1C<PWM)		
	{
		OCR1C++;
		delay_MS(DelayTime);
	}
	while(OCR1C>PWM)
	{
		OCR1C--;
		delay_MS(DelayTime);
	}
	
}

void Server4( unsigned int PWM, unsigned int DelayTime)		
{
	while(OCR3A<PWM)		
	{
		OCR3A++;
		delay_MS(DelayTime);
	}
	while(OCR3A>PWM)
	{
		OCR3A--;
		delay_MS(DelayTime);
	}
	
}

void Server5( unsigned int PWM, unsigned int DelayTime)		
{
	while(OCR3B<PWM)		
	{
		OCR3B++;
		delay_MS(DelayTime);
	}
	while(OCR3B>PWM)
	{
		OCR3B--;
		delay_MS(DelayTime);
	}
	
}


void catch1(void)
{
delay_MS(2000);
 Server5(40,80); //ˮƽ��ת
delay_MS(2000);
Server1(11,20);    //צ���ſ�
delay_MS(2000);
Go(1,-1,220);
delay_MS(2000);
Server3(28,80);    //��ƽ��
delay_MS(2000);
Go(1,-1,80);
delay_MS(2000);
Server1(22,20);    //צ�ӱպ�
delay_MS(2000);
Go(2,-1,300);
delay_MS(2000);
Server3(15,40);    //̧��
delay_MS(2000);
}

void put1(void)
{
delay_MS(2000);
Go(2,-1,200);
delay_MS(2000);
Server3(22,40);    //��ƽ��
delay_MS(2000);
Server1(15,20);    //צ���ſ�
delay_MS(2000);
Server3(15,40);    //̧��
delay_MS(2000);
Server1(22,20);    //צ�ӱպ�
delay_MS(2000);
Go(1,-1,200);
delay_MS(2000);
}

void put2(void)
{
delay_MS(2000);
Go(2,-1,200);
delay_MS(2000);
Server3(28,40);    //��ƽ��
delay_MS(2000);
Server1(15,20);    //צ���ſ�
delay_MS(2000);
Server3(15,40);    //̧��
delay_MS(2000);
Server1(22,20);    //צ�ӱպ�
delay_MS(2000);
Go(1,-1,200);
delay_MS(2000);
}

void catch2(void)
{
delay_MS(2000);
 Server5(40,80); //ˮƽ��ת
delay_MS(2000);
Go(1,-1,150);
delay_MS(2000);
Server1(13,20);    //צ���ſ�
delay_MS(2000);
Server3(28,40);    //��ƽ��
delay_MS(2000);
Server1(20,20);    //צ�ӱպ�
delay_MS(2000);
Go(2,-1,150);
delay_MS(2000);
Server3(15,40);    //̧��
delay_MS(2000);
}

/*
//���ˮƽ��ת
Server5(18,80); 	  
delay_MS(2000);
Server5(40,80); 	  
delay_MS(2000);
Server5(22,80); 	 
delay_MS(2000);
Server5(7,80); 	  
delay_MS(2000);
*/