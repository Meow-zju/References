#include <macros.h> 
#include <iom128v.h>

void Go1(unsigned int act)  //0号电机，参数act，1代表正转，2反转，0停止
{
	switch(act)
	{
	case 1: {PORTA&=~BIT(1); PORTA|=BIT(0);} break;	 	//PA1置0，PA0置1
	case 2: {PORTA&=~BIT(0); PORTA|=BIT(1);} break;	 	//PA0置0，PA1置1
	case 0: PORTA&=~(BIT(0)|BIT(1)); break;            	//PA0置0，PA1置0
	}
}

void Go2(unsigned int act) 
{
	switch(act)
	{
	case 1: {PORTA&=~BIT(3); PORTA|=BIT(2);} break;	 	
	case 2: {PORTA&=~BIT(2); PORTA|=BIT(3);} break;	 	
	case 0: PORTA&=~(BIT(2)|BIT(3)); break;            	
	}
}

void Go3(unsigned int act)  
{
	switch(act)
	{
	case 1: {PORTA&=~BIT(5); PORTA|=BIT(4);} break;	 	
	case 2: {PORTA&=~BIT(4); PORTA|=BIT(5);} break;	 	
	case 0: PORTA&=~(BIT(4)|BIT(5)); break;            	
	}
}

void Go4(unsigned int act)  
{
	switch(act)
	{
	case 1: {PORTA&=~BIT(7); PORTA|=BIT(6);} break;	 	
	case 2: {PORTA&=~BIT(6); PORTA|=BIT(7);} break;	 	
	case 0: PORTA&=~(BIT(6)|BIT(7)); break;            	
	}
}