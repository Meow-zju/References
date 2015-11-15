#include <iom128v.h>
#include "delay.h"
unsigned char run[8];
//unsigned char s,i,j,k;
unsigned char z,y;

void step(unsigned int act,int time)  //0号电机，参数act，1代表正转，2反转，0停止
{
	switch(act)
	{
	case 1: {unsigned char run[8]={0x0e,0x0c,0x0d,0x09,0x0b,0x03,0x07,0x06};
		 while(time>0)
		 {
		 for(z=0;z<8;z++) //改变数组的长度值需改变这个数字8，8为数组的长度。
		 {
		 PORTF=run[z];
		 delay_MS(3);
		 time--;
		 }
		 }
		 } 
	break;	 	//PA1置0，PA0置1
	
	case 2: {unsigned char run[8]={0x06,0x07,0x03,0x0b,0x09,0x0d,0x0c,0x0e};
		while(time>0)
		{
		for(z=0;z<8;z++) //改变数组的长度值需改变这个数字8，8为数组的长度。
		{
		PORTF=run[z];
		delay_MS(3);
		time--;
		}
		}} 
	break;	 	//PA0置0，PA1置1
	case 0: {unsigned char run[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};} break;     //PA0置0，PA1置0
	}

}