#include <iom128v.h>
#include "server.h"
#include "delay.h"
#include "steping.h"
#include <macros.h> 
#include "motor.h"
#include "Go.h"
#include "bluetooth.h"

#define LeftDistans 250
#define RightDistans 750
#define Recognition 5000
//A:蓝，    B：红，    C:绿，   D:黄
//E:红可乐，F:黑可乐， G:百事， H:雪碧
//I:王老吉，J：加多宝，K：醒目，L：美年达
//M:苹果，  N:橙汁，   O:纯牛奶 P:高钙牛奶
#define Shelf_A_UP 'A'
#define Shelf_A_DOWN 'a'
#define Shelf_B_UP 'D'
#define Shelf_B_DOWN 'd'
#define Shelf_C_UP 'L'
#define Shelf_C_DOWN 'l'
#define Shelf_D_UP 'P'
#define Shelf_D_DOWN 'p'
unsigned char a;
int flaga=0;
int flagb=0;
int flagc=0;
int flagd=0;
void main(void){

//端口初始化
DDRA=0xFF;  //PA0-PA7控制电机，输出。
PORTA=0x00;	

DDRB&=0b11111000;//PB0-PB3传感器，高阻状态,输入
PORTB&=0b11111000;
DDRC=0x00;	//PC0-PC7传感器1-7,8，高阻，输入
PORTC=0x00;

DDRB|=0b11100000;	//PB5、6、7输出，3个舵机	
PORTB&=0b00011111;
DDRE|=0b00011010;	//PE1、3、4输出，1个蓝牙，2个舵机	
PORTE&=0b11100111;

DDRF=0xFF;  //PF0-PF3控制步进电机，输出。
PORTF=0x00;	
//初始化T1、T3计数器
//关闭定时器中断
TIMSK=0x00;
TCNT0=0x00;    
TCCR0=0x6b;    
OCR0=0x80;     
TCNT1H=0x00;    
TCNT1L=0x00;    
TCCR1A=0xa9;   
TCCR1B=0x0c;
TCCR1C=0x00;
TCNT3H=0x00;    
TCNT3L=0x00;    
TCCR3A=0xa9;  
TCCR3B=0x0c;
TCCR3C=0x00;
//5个舵机初始位置
OCR1A=20;
OCR1B=18;
OCR1C=15;
OCR3B=37;
//***********开始调试***********
uart0_init();     //蓝牙初始化
while(a!='c')
{
a=getchar0();     //读取一个字符
delay_MS(300);
};
//***********开跑！！！***********
//A货架
 Go(1,-1,3000); 	//盲跑一格
 delay_MS(1000);
 Go(1,1,10); 	//前进一格
 delay_MS(1000);
 Go(3,-1,200);	//左移一段距离a（须调整）
 //识别A1列
  delay_MS(3000);
while(a!='s')
{
putchar0(Shelf_A_UP);    //假设A货架上层拿b物块
delay_MS(1000);
a=getchar0();     //读取一个字符
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 if(a=='t'){    //如果识别正确
 delay_MS(1000); 
 catch1();      //抓取
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,-1,3000);	//后退盲跑
 Go(2,0,10);	//后退前进一格 
 delay_MS(1000);
 Go(3,-1,240);	//左移一段距离a到A放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put2();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(1000);
 Go(4,0,5);		//回到白线十字
  delay_MS(1000);
 flaga=1;    //2表示抓去了上层
 a='1';
 Go(1,-1,3000);	//前进盲跑
 Go(1,0,10);	//前进一格到达A货架前十字 
 delay_MS(1000);
 }
 else Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 //上层A1没有识别到识别上层A2列
 if(flaga!=1){
 Go(4,-1,RightDistans);	//右移一段距离
 delay_MS(3000);
while(a!='s')
{
putchar0(Shelf_A_UP);    //假设A货架上层拿b物块
delay_MS(1000);
a=getchar0();     //读取一个字符
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确
 Go(3,-1,500);	//左移一段距离抓取
 delay_MS(1000);
 catch1();      //抓取
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,-1,3000);	//后退盲跑
 Go(2,0,10);	//后退一格 
 delay_MS(1000);
 Go(3,-1,240);	//左移一段距离a到A放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put2();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(1000);
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 flaga=2;
 a='1';
 Go(1,-1,3000);	//前进盲跑
 Go(1,0,10);	//前进一格到达A货架前十字 
 }
 
 delay_MS(1000);
 Go(4,1,5);     //右移一格准备识别B货架
 //A货架识别完毕，停留在B货架前的十字，若抓取上层A1则flaga=1,抓取上层A2列则flaga=2,都没抓flaga=0
 
 //B货架
 delay_MS(1000);
 Go(3,-1,LeftDistans);	//左移一段距离a（须调整）
 //识别B1列
 delay_MS(3000);
 while(a!='s')
{
 putchar0(Shelf_B_UP);    //假设B货架上层拿a物块
 delay_MS(1000);
 a=getchar0();     //读取一个字符
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 if(a=='t'){    //如果识别正确
 delay_MS(1000);
 catch1();      //抓取
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,2,10);	//后退前进两格 
 delay_MS(1000);
 Go(3,1,10);	//左移一个
 delay_MS(1000);
 Go(4,-1,220);	//右移一段距离到B放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put2();		//放手
 delay_MS(1000);
 Server5(37,80);//水平前转  
 delay_MS(1000);
 Go(4,0,5);		
 delay_MS(1000);
 Go(1,2,5);     //回到B货架正对十字
 delay_MS(1000);
 flagb=1;
 a='1';
 }
 else Go(4,0,5);		//否则直接回到B前面白线十字
 delay_MS(1000);
 //上层B1没有识别到识别上层B2列
 Go(4,-1,RightDistans);	//右移一段距离
 //识别B2列
 delay_MS(3000);
 if(flagb!=1){
 while(a!='s')
{
 putchar0(Shelf_B_UP);    //假设B货架上层拿a物块
 delay_MS(1000);
 a=getchar0();     //读取一个字符
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确
 Go(3,-1,500);	//左移一段距离抓取
 catch1();      //抓取
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,2,10);	//后退两格 
 delay_MS(1000);
 Go(3,1,10);	//左移一个
 delay_MS(1000);
 Go(4,-1,220);	//右移一段距离到B放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put2();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(1000);
 Go(4,0,5);		//回到B货架正对十字
 delay_MS(1000);
 flagb=2;
 a='1';
 Go(1,2,5);    //前进两格回到B货架前十字
 delay_MS(1000);
 }
 Go(4,1,5);    //右移一个准备识别C货架,在C货架前面
  
 //C货架
 delay_MS(1000);
 Go(3,-1,LeftDistans);	//左移一段距离a（须调整）
 //识别C1列
 delay_MS(3000);
 while(a!='s')
{
 putchar0(Shelf_C_UP);    //假设C货架拿e物块
 delay_MS(1000);
 a=getchar0();     //读取一个字符
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 if(a=='t'){    //如果识别正确
 delay_MS(1000); 
 catch1();      //抓取
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,2,10);	//后退前进两格 
 delay_MS(1000);
 Go(4,1,5);	//右移一个
 delay_MS(1000);
 Go(3,-1,240);	//左移一段距离到C放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put2();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(2000);
 Go(3,0,5);		//左移一段距离到C货架正对的十字
 delay_MS(1000);
 Go(1,2,5);		//前进两格C货架前的十字
 delay_MS(1000);
 flagc=1;
 a='1';
 }
 else Go(4,0,5);//否则直接回到C前面白线十字
 delay_MS(1000);
 //C1没有识别C2列的
 Go(4,-1,RightDistans);	//右移一段距离
delay_MS(3000);
 if(flagc!=1){
 while(a!='s')
{
 putchar0(Shelf_C_UP);    //假设C货架拿e物块
 delay_MS(1000);
 a=getchar0();     //读取一个字符
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确
 Go(3,-1,500);	//左移一段距离抓取
 catch1();      //抓取
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,2,10);	//后退前进两格 
 delay_MS(1000);
 Go(4,1,10);	//右移一个
 delay_MS(1000);
 Go(3,-1,240);//左移一段距离到C放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put2();		//放手
 delay_MS(1000);
 Server5(37,80);//水平前转  
 delay_MS(2000);
 Go(3,0,5);		//左移一段距离到C货架正对的十字
 delay_MS(1000);
 flagc=2;
 a='1';
 Go(1,2,5);		//前进两格到C前的十字
 delay_MS(1000);
 }
 Go(4,1,5);		//右移一格到D前的十字
 delay_MS(1000);
//准备识别D货架
 //D货架
Go(3,-1,240);	//左移一段距离a（须调整）
 //识别D1列
 delay_MS(3000);
while(a!='s')
{
putchar0(Shelf_D_UP);    //假设A货架上层拿b物块
delay_MS(1000);
a=getchar0();     //读取一个字符
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 if(a=='t'){    //如果识别正确
 delay_MS(1000); 
 catch1();      //抓取
 delay_MS(1000); 
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,-1,3000);	//后退盲跑
 Go(2,0,10);	//后退前进一格 
 delay_MS(1000);
 Go(4,-1,220);	//右移一段距离a到D放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put2();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(1000);
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 flagd=1;  
 a='1';  
 Go(1,-1,3000);	//前进盲跑
 Go(1,0,10);	//前进一格到达D货架前十字
 delay_MS(1000); 
 }
 else Go(4,0,5);		//回到D前白线十字
 delay_MS(1000);
 //上层D1没有识别到识别上层D2列
 Go(4,-1,220);	//右移一段距离
 if(flagd!=1){
while(a!='s')
{
putchar0(Shelf_D_UP);    //假设A货架上层拿b物块
delay_MS(1000);
a=getchar0();     //读取一个字符
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确
 catch1();      //抓取
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,-1,3000);	//后退盲跑
 Go(2,0,10);	//后退一格 
 delay_MS(1000);
 Go(4,-1,220);	//右移一段距离a到D放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put2();		//放手
 delay_MS(1000);
 Server5(37,80);//水平前转  
 delay_MS(1000);
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 flagd=2;
 a='1';
 Go(1,-1,3000);	//前进盲跑
 Go(1,0,10);	//前进一格到达D货架前十字 
 delay_MS(1000);
 }
 Go(3,0,5);     //左移一格到达D货架前十字
 delay_MS(1000);
 //开始下降返回A货架，识别下层
 step(2,17000);	//丝杆下移准备识别下层
 delay_MS(1000);
 DDRF=0x00;  //PF0-PF3控制步进电机，输出。
 PORTF=0x00;
 delay_MS(1000);
 Go(3,1,5);     //左移三格到A货架前
 delay_MS(3000);
 Go(3,1,5);     //左移三格到A货架前
 delay_MS(3000);
 Go(3,1,5);     //左移三格到A货架前

 
 delay_MS(1000);
 Go(3,-1,200);	//左移一段距离a（须调整）
 //识别A1列
  delay_MS(3000);
if(flaga!=1&&flaga!=2){
while(a!='s')
{
putchar0(Shelf_A_DOWN);    //假设A货架上层拿b物块
delay_MS(1000);
a=getchar0();     //读取一个字符
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确
 delay_MS(1000); 
 catch1();      //抓取
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,-1,3000);	//后退盲跑
 Go(2,0,10);	//后退前进一格 
 delay_MS(1000);
 Go(3,-1,240);	//左移一段距离a到A放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put1();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(1000);
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 flaga=3;    //2表示抓去了上层
 a='1';
 Go(1,-1,3000);	//前进盲跑
 Go(1,0,10);	//前进一格到达A货架前十字 
 delay_MS(1000);
 }
 else Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 //上层A1没有识别到识别上层A2列
 if(flaga!=1&&flaga!=2&&flaga!=3){
 Go(4,-1,RightDistans);	//右移一段距离
 delay_MS(3000);
 Go(3,-1,500);	//左移一段距离抓取
 delay_MS(1000);
 catch1();      //抓取
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,-1,3000);	//后退盲跑
 Go(2,0,10);	//后退一格 
 delay_MS(1000);
 Go(3,-1,240);	//左移一段距离a到A放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put1();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(1000);
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 flaga=4;
 a='1';
 Go(1,-1,3000);	//前进盲跑
 Go(1,0,10);	//前进一格到达A货架前十字 
 }
 
 delay_MS(1000);
 Go(4,1,5);     //右移一格准备识别B货架
 //A货架识别完毕，停留在B货架前的十字，若抓取上层A1则flaga=1,抓取上层A2列则flaga=2,都没抓flaga=0
 
 //B货架
 
 delay_MS(1000);
 Go(3,-1,LeftDistans);	//左移一段距离a（须调整）
 //识别B1列
 if(flagb!=1&&flagb!=2){
 delay_MS(3000);
 while(a!='s')
{
 putchar0(Shelf_B_DOWN);    //假设B货架上层拿a物块
 delay_MS(1000);
 a=getchar0();     //读取一个字符
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确
 delay_MS(1000);
 catch1();      //抓取
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,2,10);	//后退前进两格 
 delay_MS(1000);
 Go(3,1,10);	//左移一个
 delay_MS(1000);
 Go(4,-1,220);	//右移一段距离到B放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put1();		//放手
 delay_MS(1000);
 Server5(37,80);//水平前转  
 delay_MS(1000);
 Go(4,0,5);		
 delay_MS(1000);
 Go(1,2,5);     //回到B货架正对十字
 delay_MS(1000);
 flagb=3;
 a='1';
 }
 else Go(4,0,5);		//否则直接回到B前面白线十字
 delay_MS(1000);
 //上层B1没有识别到识别上层B2列
 Go(4,-1,RightDistans);	//右移一段距离
 //识别B2列
 delay_MS(3000);
 if(flagb!=1&&flagb!=2&&flagb!=3){
 Go(3,-1,500);	//左移一段距离抓取
 catch1();      //抓取
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,2,10);	//后退两格 
 delay_MS(1000);
 Go(3,1,10);	//左移一个
 delay_MS(1000);
 Go(4,-1,220);	//右移一段距离到B放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put1();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(1000);
 Go(4,0,5);		//回到B货架正对十字
 delay_MS(1000);
 flagb=2;
 a='1';
 Go(1,2,5);    //前进两格回到B货架前十字
 delay_MS(1000);
 }
 Go(4,1,5);    //右移一个准备识别C货架,在C货架前面
  
 //C货架
 delay_MS(1000);
 Go(3,-1,LeftDistans);	//左移一段距离a（须调整）
 //识别C1列
 delay_MS(3000);
 if(flagc!=1&&flagc!=2){
 while(a!='s')
{
 putchar0(Shelf_C_UP);    //假设C货架拿e物块
 delay_MS(1000);
 a=getchar0();     //读取一个字符
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确
 delay_MS(1000); 
 catch1();      //抓取
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,2,10);	//后退前进两格 
 delay_MS(1000);
 Go(4,1,5);	//右移一个
 delay_MS(1000);
 Go(3,-1,240);	//左移一段距离到C放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put1();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(2000);
 Go(3,0,5);		//左移一段距离到C货架正对的十字
 delay_MS(1000);
 Go(1,2,5);		//前进两格C货架前的十字
 delay_MS(1000);
 flagc=3;
 a='1';
 }
 else Go(4,0,5);//否则直接回到C前面白线十字
 delay_MS(1000);
 //C1没有识别C2列的
 Go(4,-1,RightDistans);	//右移一段距离
delay_MS(3000);
 if(flagc!=1&&flagc!=2&&flagc!=3){
 while(a!='s')
{
 putchar0(Shelf_C_UP);    //假设C货架拿e物块
 delay_MS(1000);
 a=getchar0();     //读取一个字符
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确*/
 Go(3,-1,500);	//左移一段距离抓取
 catch1();      //抓取
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,2,10);	//后退前进两格 
 delay_MS(1000);
 Go(4,1,10);	//右移一个
 delay_MS(1000);
 Go(3,-1,240);//左移一段距离到C放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put1();		//放手
 delay_MS(1000);
 Server5(37,80);//水平前转  
 delay_MS(2000);
 Go(3,0,5);		//左移一段距离到C货架正对的十字
 delay_MS(1000);
 flagc=4;
 a='1';
 Go(1,2,5);		//前进两格到C前的十字
 delay_MS(1000);
 }
 Go(4,1,5);		//右移一格到D前的十字
 delay_MS(1000);
//准备识别D货架
 //D货架
Go(3,-1,240);	//左移一段距离a（须调整）
 //识别D1列
 delay_MS(3000);
if(flagd!=1&&flagd!=2){
while(a!='s')
{
putchar0(Shelf_D_UP);    //假设A货架上层拿b物块
delay_MS(1000);
a=getchar0();     //读取一个字符
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //如果识别正确
 delay_MS(1000); 
 catch1();      //抓取
 delay_MS(1000); 
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,-1,3000);	//后退盲跑
 Go(2,0,10);	//后退前进一格 
 delay_MS(1000);
 Go(4,-1,220);	//右移一段距离a到D放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put1();		//放手
 delay_MS(1000);
 Server5(37,80); 	//水平前转  
 delay_MS(1000);
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 flagd=3;  
 a='1';  
 Go(1,-1,3000);	//前进盲跑
 Go(1,0,10);	//前进一格到达D货架前十字
 delay_MS(1000); 
 }
 else Go(4,0,5);		//回到D前白线十字
 delay_MS(1000);
 //上层D1没有识别到识别上层D2列
 Go(4,-1,220);	//右移一段距离
 if(flagd!=1&&flagc!=2&&flagc!=3){
 delay_MS(1000); 
 catch1();      //抓取
 Go(3,0,5);		//回到白线十字
 delay_MS(1000);
 Go(2,-1,3000);	//后退盲跑
 Go(2,0,10);	//后退一格 
 delay_MS(1000);
 Go(4,-1,220);	//右移一段距离a到D放货篮
 delay_MS(1000);
 Server5(7,80); //水平后转
 delay_MS(1000);
 put1();		//放手
 delay_MS(1000);
 Server5(37,80);//水平前转  
 delay_MS(1000);
 Go(4,0,5);		//回到白线十字
 delay_MS(1000);
 flagd=4;
 a='1';
 Go(1,-1,3000);	//前进盲跑
 Go(1,0,10);	//前进一格到达D货架前十字 
 delay_MS(1000);
 }
 Go(3,0,5);     //左移一格到达D货架前十字
 delay_MS(1000);
 }