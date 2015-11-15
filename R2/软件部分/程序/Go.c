//Go(方向[1,2,3,4,前后左右]，格数，时间)


/*					③
                    ↑
					1
			******************
			*		1 2 3	 *
			* 7			 10	 *
			* 8			 11	 *
	② ← 3 * 9			 12	 * 4 → ①
			*				 *
			*				 *
			*		4 5 6	 *
			******************
					2
					↓
					④
*/

#include <macros.h>
#include <iom128v.h>
#include "delay.h"
 #include "Go.h"
#define S1 ScanC(1)
#define S2 ScanC(2)
#define S3 ScanC(3)
#define S4 ScanC(4)
#define S5 ScanC(5)
#define S6 ScanC(6)
#define S7 ScanC(7)
#define S8 ScanC(0)
#define S9 ScanB(0)
#define S10 ScanB(1)
#define S11 ScanB(2)
#define S12 ScanB(3)

#define Forward ScanC(5)
#define Backward ScanC(5)
#define Left ScanC(0)
#define Right ScanC(0)

#define White !=0
#define Black ==0

	
	void Revise(void)
	{
	Go1(1);
	Go2(2);
	Go3(1);
	Go4(2);
	delay_MS(1560);
	Go1(0);
	Go2(0);
	Go3(0);
	Go4(0);
	}
	
	unsigned int ScanC(unsigned int Num)
	{
	 	 unsigned int i,sum=0;
	 	 for(i=1;i<=10;i++)
		     if(PINC&BIT(Num))
			     sum++;
		 if(sum>=5)
		     return 1;
		 else return 0;  
	}
	unsigned int ScanB(unsigned int Num)
	{
	 	 unsigned int i,sum=0;
	 	 for(i=1;i<=10;i++)
		     if(PINB&BIT(Num))
			     sum++;
		 if(sum>=5)
		     return 1;
		 else return 0;  
	}
	
	void Go(int d,int n,int t)  //0号电机，参数1代表正转，2反转，0停止
	{
		unsigned long j=0,temp=0,i=0;
		unsigned int flag=0,BreakTime=0,UnCountTime=800;
		if(n==0)
		{
			UnCountTime=0;
		    n=1;
		}
		if(n<0)
		{
			BreakTime=t; 
			t=5;
			n=1;
		}  
//n=0情况，前进距离由时间t控制******************************************
	

//***********************************************************			
			if(d==1)
			{
				Go1(1);
				Go2(1);
				for(;;)
				{						
					i=j;
					if((S10 White)&&(S12 Black)&&(S7 White)&&(S9 Black))
					{
						Go3(1);
						Go4(1);
						delay_MS(t);
						Go3(0);
						Go4(0);
						j++;
					}
					if((S9 White)&&(S7 Black)&&(S10 White)&&(S12 Black))
					{
						Go3(2);
						Go4(1);
						delay_MS(t);
						Go3(0);
						Go4(0);
						j++;
					}
					if((S12 White)&&(S10 Black)&&(S7 White)&&(S9 Black))
					{
						Go3(1);
						Go4(2);
						delay_MS(t);
						Go3(0);
						Go4(0);
						j++;
					}
					if((S12 White)&&(S10 Black)&&(S9 White)&&(S7 Black))
					{
						Go3(2);
						Go4(2);
						delay_MS(t);
						Go3(0);
						Go4(0);
						j++;
					}
					if((S11 White)&&(S7 White)&&(S9 Black))
					{
						Go3(1);
						delay_MS(t);
						Go3(0);
						j++;
					}
					if((S11 White)&&(S9 White)&&(S7 Black))
					{
						Go3(2);
						delay_MS(t);
						Go3(0);
						j++;
					}
					if((S8 White)&&(S10 White)&&(S12 Black))
					{
						Go4(1);
						delay_MS(t);
						Go4(0);
						j++;
					}
					if((S8 White)&&(S12 White)&&(S10 Black))
					{
						Go4(2);
						delay_MS(t);
						Go4(0);
						j++;
					}
					if((S11 White)&&(S8 White))
					{
						delay_MS(t);
						j++;
					}
					if(j==i)
					{
					delay_MS(t);
					j++;
					}
						
					if((BreakTime>0)&&(j*t>=BreakTime))
						{
						flag=n;
						}
					if((BreakTime==0)&&(j*t-temp>=UnCountTime)&&(Forward White))
					{
							flag++;
							if(flag<n)
								temp=j*t;						
					}
					if(flag>=n)
					{
						Go1(0);
						Go2(0);
						break;
					}
				}
			}
//*****************************************************************
		if(d==2)
			{
				Go1(2);
				Go2(2);
			
				for(;;)
				{		
				i=j;				
					if((S10 White)&&(S12 Black)&&(S7 White)&&(S9 Black))
					{
						Go3(1);
						Go4(1);
						delay_MS(t);
						Go3(0);
						Go4(0);
						j++;
					}
					if((S9 White)&&(S7 Black)&&(S10 White)&&(S12 Black))
					{
						Go3(2);
						Go4(1);
						delay_MS(t);
						Go3(0);
						Go4(0);
						j++;
					}
					if((S12 White)&&(S10 Black)&&(S7 White)&&(S9 Black))
					{
						Go3(1);
						Go4(2);
						delay_MS(t);
						Go3(0);
						Go4(0);
						j++;
					}
					if((S12 White)&&(S10 Black)&&(S9 White)&&(S7 Black))
					{
						Go3(2);
						Go4(2);
						delay_MS(t);
						Go3(0);
						Go4(0);
						j++;
					}
					if((S11 White)&&(S7 White)&&(S9 Black))
					{
						Go3(1);
						delay_MS(t);
						Go3(0);
						j++;
					}
					if((S11 White)&&(S9 White)&&(S7 Black))
					{
						Go3(2);
						delay_MS(t);
						Go3(0);
						j++;
					}
					if((S8 White)&&(S10 White)&&(S12 Black))
					{
						Go4(1);
						delay_MS(t);
						Go4(0);
						j++;
					}
					if((S8 White)&&(S12 White)&&(S10 Black))
					{
						Go4(2);
						delay_MS(t);
						Go4(0);
						j++;
					}
					if((S11 White)&&(S8 White))
					{
						delay_MS(t);
						j++;
					}
					if(j==i)
					{
					delay_MS(t);
					j++;
					}
					if((BreakTime>0)&&(j*t>=BreakTime))
						{
						flag=n;
						}
					if((BreakTime==0)&&(j*t-temp>=UnCountTime)&&(Backward White))
					{
							flag++;
							if(flag<n)
								temp=j*t;						
					}
					if(flag>=n)
					{
						Go1(0);
						Go2(0);
						break;
					}
				}
			}
//******************************************
			if(d==3)
			{
				Go3(1);
				Go4(1);
				
				for(;;)
				{	
				i=j;
					if((S3 White)&&(S1 Black)&&(S6 White)&&(S4 Black))
					{
						Go1(1);
						Go2(1);
						delay_MS(t);
						Go1(0);
						Go2(0);
						j++;
					}
					if((S3 White)&&(S1 Black)&&(S4 White)&&(S6 Black))
					{
						Go1(1);
						Go2(2);
						delay_MS(t);
						Go1(0);
						Go2(0);
						j++;
					}
					if((S1 White)&&(S3 Black)&&(S6 White)&&(S4 Black))
					{
						Go1(2);
						Go2(1);
						delay_MS(t);
						Go1(0);
						Go2(0);
						j++;
					}
					if((S1 White)&&(S3 Black)&&(S4 White)&&(S6 Black))
					{
						Go1(2);
						Go2(2);
						delay_MS(t);
						Go1(0);
						Go2(0);
						j++;
					}
					if((S2 White)&&(S6 Black)&&(S4 White))
					{
						Go2(2);
						delay_MS(t);
						Go2(0);
						j++;
					}
					if((S2 White)&&(S4 Black)&&(S6 White))
					{
						Go2(1);
						delay_MS(t);
						Go2(0);
						j++;
					}
					if((S5 White)&&(S3 Black)&&(S1 White))
					{
						Go1(2);
						delay_MS(t);
						Go1(0);
						j++;
					}
					if((S5 White)&&(S1 Black)&&(S3 White))
					{
						Go1(1);
						delay_MS(t);
						Go1(0);
						j++;
					}
					if((S2 White)&&(S5 White))
					{
						delay_MS(t);
						j++;
					}
					if(j==i)
					{
					delay_MS(t);
					j++;
					}
					if((BreakTime>0)&&(j*t>=BreakTime))
						{
						flag=n;
						}
					if((BreakTime==0)&&(j*t-temp>=UnCountTime)&&(Left White))
					{
							flag++;
							if(flag<n)
								temp=j*t;						
					}
					if(flag>=n)
					{
						Go3(0);
						Go4(0);
						break;
					}
				}
			}
//****************************************************
			if(d==4)
			{
				Go3(2);
				Go4(2);
			
				for(;;)
				{
					i=j;
					if((S3 White)&&(S1 Black)&&(S6 White)&&(S4 Black))
					{
						Go1(1);
						Go2(1);
						delay_MS(t);
						Go1(0);
						Go2(0);
						j++;
					}
					if((S3 White)&&(S1 Black)&&(S4 White)&&(S6 Black))
					{
						Go1(1);
						Go2(2);
						delay_MS(t);
						Go1(0);
						Go2(0);
						j++;
					}
					if((S1 White)&&(S3 Black)&&(S6 White)&&(S4 Black))
					{
						Go1(2);
						Go2(1);
						delay_MS(t);
						Go1(0);
						Go2(0);
						j++;
					}
					if((S1 White)&&(S3 Black)&&(S4 White)&&(S6 Black))
					{
						Go1(2);
						Go2(2);
						delay_MS(t);
						Go1(0);
						Go2(0);
						j++;
					}
					if((S2 White)&&(S6 Black)&&(S4 White))
					{
						Go2(2);
						delay_MS(t);
						Go2(0);
						j++;
					}
					if((S2 White)&&(S4 Black)&&(S6 White))
					{
						Go2(1);
						delay_MS(t);
						Go2(0);
						j++;
					}
					if((S5 White)&&(S3 Black)&&(S1 White))
					{
						Go1(2);
						delay_MS(t);
						Go1(0);
						j++;
					}
					if((S5 White)&&(S1 Black)&&(S3 White))
					{
						Go1(1);
						delay_MS(t);
						Go1(0);
						j++;
					}
					if((S2 White)&&(S5 White))
					{
						delay_MS(t);
						j++;
					}
					if(j==i)
					{
					delay_MS(t);
					j++;
					}
					if((BreakTime>0)&&(j*t>=BreakTime))
						{
						flag=n;
						}
					if((BreakTime==0)&&(j*t-temp>=UnCountTime)&&(Right White))
					{
							flag++;
							if(flag<n)
								temp=j*t;						
					}
					if(flag>=n)
					{
						Go3(0);
						Go4(0);
						break; 
					}
				}
		}
	}