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
//A:����    B���죬    C:�̣�   D:��
//E:����֣�F:�ڿ��֣� G:���£� H:ѩ��
//I:���ϼ���J���Ӷ౦��K����Ŀ��L�������
//M:ƻ����  N:��֭��   O:��ţ�� P:�߸�ţ��
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

//�˿ڳ�ʼ��
DDRA=0xFF;  //PA0-PA7���Ƶ���������
PORTA=0x00;	

DDRB&=0b11111000;//PB0-PB3������������״̬,����
PORTB&=0b11111000;
DDRC=0x00;	//PC0-PC7������1-7,8�����裬����
PORTC=0x00;

DDRB|=0b11100000;	//PB5��6��7�����3�����	
PORTB&=0b00011111;
DDRE|=0b00011010;	//PE1��3��4�����1��������2�����	
PORTE&=0b11100111;

DDRF=0xFF;  //PF0-PF3���Ʋ�������������
PORTF=0x00;	
//��ʼ��T1��T3������
//�رն�ʱ���ж�
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
//5�������ʼλ��
OCR1A=20;
OCR1B=18;
OCR1C=15;
OCR3B=37;
//***********��ʼ����***********
uart0_init();     //������ʼ��
while(a!='c')
{
a=getchar0();     //��ȡһ���ַ�
delay_MS(300);
};
//***********���ܣ�����***********
//A����
 Go(1,-1,3000); 	//ä��һ��
 delay_MS(1000);
 Go(1,1,10); 	//ǰ��һ��
 delay_MS(1000);
 Go(3,-1,200);	//����һ�ξ���a���������
 //ʶ��A1��
  delay_MS(3000);
while(a!='s')
{
putchar0(Shelf_A_UP);    //����A�����ϲ���b���
delay_MS(1000);
a=getchar0();     //��ȡһ���ַ�
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 if(a=='t'){    //���ʶ����ȷ
 delay_MS(1000); 
 catch1();      //ץȡ
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,-1,3000);	//����ä��
 Go(2,0,10);	//����ǰ��һ�� 
 delay_MS(1000);
 Go(3,-1,240);	//����һ�ξ���a��A�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put2();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		//�ص�����ʮ��
  delay_MS(1000);
 flaga=1;    //2��ʾץȥ���ϲ�
 a='1';
 Go(1,-1,3000);	//ǰ��ä��
 Go(1,0,10);	//ǰ��һ�񵽴�A����ǰʮ�� 
 delay_MS(1000);
 }
 else Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 //�ϲ�A1û��ʶ��ʶ���ϲ�A2��
 if(flaga!=1){
 Go(4,-1,RightDistans);	//����һ�ξ���
 delay_MS(3000);
while(a!='s')
{
putchar0(Shelf_A_UP);    //����A�����ϲ���b���
delay_MS(1000);
a=getchar0();     //��ȡһ���ַ�
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ
 Go(3,-1,500);	//����һ�ξ���ץȡ
 delay_MS(1000);
 catch1();      //ץȡ
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,-1,3000);	//����ä��
 Go(2,0,10);	//����һ�� 
 delay_MS(1000);
 Go(3,-1,240);	//����һ�ξ���a��A�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put2();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 flaga=2;
 a='1';
 Go(1,-1,3000);	//ǰ��ä��
 Go(1,0,10);	//ǰ��һ�񵽴�A����ǰʮ�� 
 }
 
 delay_MS(1000);
 Go(4,1,5);     //����һ��׼��ʶ��B����
 //A����ʶ����ϣ�ͣ����B����ǰ��ʮ�֣���ץȡ�ϲ�A1��flaga=1,ץȡ�ϲ�A2����flaga=2,��ûץflaga=0
 
 //B����
 delay_MS(1000);
 Go(3,-1,LeftDistans);	//����һ�ξ���a���������
 //ʶ��B1��
 delay_MS(3000);
 while(a!='s')
{
 putchar0(Shelf_B_UP);    //����B�����ϲ���a���
 delay_MS(1000);
 a=getchar0();     //��ȡһ���ַ�
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 if(a=='t'){    //���ʶ����ȷ
 delay_MS(1000);
 catch1();      //ץȡ
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,2,10);	//����ǰ������ 
 delay_MS(1000);
 Go(3,1,10);	//����һ��
 delay_MS(1000);
 Go(4,-1,220);	//����һ�ξ��뵽B�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put2();		//����
 delay_MS(1000);
 Server5(37,80);//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		
 delay_MS(1000);
 Go(1,2,5);     //�ص�B��������ʮ��
 delay_MS(1000);
 flagb=1;
 a='1';
 }
 else Go(4,0,5);		//����ֱ�ӻص�Bǰ�����ʮ��
 delay_MS(1000);
 //�ϲ�B1û��ʶ��ʶ���ϲ�B2��
 Go(4,-1,RightDistans);	//����һ�ξ���
 //ʶ��B2��
 delay_MS(3000);
 if(flagb!=1){
 while(a!='s')
{
 putchar0(Shelf_B_UP);    //����B�����ϲ���a���
 delay_MS(1000);
 a=getchar0();     //��ȡһ���ַ�
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ
 Go(3,-1,500);	//����һ�ξ���ץȡ
 catch1();      //ץȡ
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,2,10);	//�������� 
 delay_MS(1000);
 Go(3,1,10);	//����һ��
 delay_MS(1000);
 Go(4,-1,220);	//����һ�ξ��뵽B�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put2();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		//�ص�B��������ʮ��
 delay_MS(1000);
 flagb=2;
 a='1';
 Go(1,2,5);    //ǰ������ص�B����ǰʮ��
 delay_MS(1000);
 }
 Go(4,1,5);    //����һ��׼��ʶ��C����,��C����ǰ��
  
 //C����
 delay_MS(1000);
 Go(3,-1,LeftDistans);	//����һ�ξ���a���������
 //ʶ��C1��
 delay_MS(3000);
 while(a!='s')
{
 putchar0(Shelf_C_UP);    //����C������e���
 delay_MS(1000);
 a=getchar0();     //��ȡһ���ַ�
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 if(a=='t'){    //���ʶ����ȷ
 delay_MS(1000); 
 catch1();      //ץȡ
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,2,10);	//����ǰ������ 
 delay_MS(1000);
 Go(4,1,5);	//����һ��
 delay_MS(1000);
 Go(3,-1,240);	//����һ�ξ��뵽C�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put2();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(2000);
 Go(3,0,5);		//����һ�ξ��뵽C�������Ե�ʮ��
 delay_MS(1000);
 Go(1,2,5);		//ǰ������C����ǰ��ʮ��
 delay_MS(1000);
 flagc=1;
 a='1';
 }
 else Go(4,0,5);//����ֱ�ӻص�Cǰ�����ʮ��
 delay_MS(1000);
 //C1û��ʶ��C2�е�
 Go(4,-1,RightDistans);	//����һ�ξ���
delay_MS(3000);
 if(flagc!=1){
 while(a!='s')
{
 putchar0(Shelf_C_UP);    //����C������e���
 delay_MS(1000);
 a=getchar0();     //��ȡһ���ַ�
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ
 Go(3,-1,500);	//����һ�ξ���ץȡ
 catch1();      //ץȡ
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,2,10);	//����ǰ������ 
 delay_MS(1000);
 Go(4,1,10);	//����һ��
 delay_MS(1000);
 Go(3,-1,240);//����һ�ξ��뵽C�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put2();		//����
 delay_MS(1000);
 Server5(37,80);//ˮƽǰת  
 delay_MS(2000);
 Go(3,0,5);		//����һ�ξ��뵽C�������Ե�ʮ��
 delay_MS(1000);
 flagc=2;
 a='1';
 Go(1,2,5);		//ǰ������Cǰ��ʮ��
 delay_MS(1000);
 }
 Go(4,1,5);		//����һ��Dǰ��ʮ��
 delay_MS(1000);
//׼��ʶ��D����
 //D����
Go(3,-1,240);	//����һ�ξ���a���������
 //ʶ��D1��
 delay_MS(3000);
while(a!='s')
{
putchar0(Shelf_D_UP);    //����A�����ϲ���b���
delay_MS(1000);
a=getchar0();     //��ȡһ���ַ�
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 if(a=='t'){    //���ʶ����ȷ
 delay_MS(1000); 
 catch1();      //ץȡ
 delay_MS(1000); 
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,-1,3000);	//����ä��
 Go(2,0,10);	//����ǰ��һ�� 
 delay_MS(1000);
 Go(4,-1,220);	//����һ�ξ���a��D�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put2();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(1000);
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 flagd=1;  
 a='1';  
 Go(1,-1,3000);	//ǰ��ä��
 Go(1,0,10);	//ǰ��һ�񵽴�D����ǰʮ��
 delay_MS(1000); 
 }
 else Go(4,0,5);		//�ص�Dǰ����ʮ��
 delay_MS(1000);
 //�ϲ�D1û��ʶ��ʶ���ϲ�D2��
 Go(4,-1,220);	//����һ�ξ���
 if(flagd!=1){
while(a!='s')
{
putchar0(Shelf_D_UP);    //����A�����ϲ���b���
delay_MS(1000);
a=getchar0();     //��ȡһ���ַ�
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ
 catch1();      //ץȡ
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,-1,3000);	//����ä��
 Go(2,0,10);	//����һ�� 
 delay_MS(1000);
 Go(4,-1,220);	//����һ�ξ���a��D�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put2();		//����
 delay_MS(1000);
 Server5(37,80);//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 flagd=2;
 a='1';
 Go(1,-1,3000);	//ǰ��ä��
 Go(1,0,10);	//ǰ��һ�񵽴�D����ǰʮ�� 
 delay_MS(1000);
 }
 Go(3,0,5);     //����һ�񵽴�D����ǰʮ��
 delay_MS(1000);
 //��ʼ�½�����A���ܣ�ʶ���²�
 step(2,17000);	//˿������׼��ʶ���²�
 delay_MS(1000);
 DDRF=0x00;  //PF0-PF3���Ʋ�������������
 PORTF=0x00;
 delay_MS(1000);
 Go(3,1,5);     //��������A����ǰ
 delay_MS(3000);
 Go(3,1,5);     //��������A����ǰ
 delay_MS(3000);
 Go(3,1,5);     //��������A����ǰ

 
 delay_MS(1000);
 Go(3,-1,200);	//����һ�ξ���a���������
 //ʶ��A1��
  delay_MS(3000);
if(flaga!=1&&flaga!=2){
while(a!='s')
{
putchar0(Shelf_A_DOWN);    //����A�����ϲ���b���
delay_MS(1000);
a=getchar0();     //��ȡһ���ַ�
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ
 delay_MS(1000); 
 catch1();      //ץȡ
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,-1,3000);	//����ä��
 Go(2,0,10);	//����ǰ��һ�� 
 delay_MS(1000);
 Go(3,-1,240);	//����һ�ξ���a��A�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put1();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 flaga=3;    //2��ʾץȥ���ϲ�
 a='1';
 Go(1,-1,3000);	//ǰ��ä��
 Go(1,0,10);	//ǰ��һ�񵽴�A����ǰʮ�� 
 delay_MS(1000);
 }
 else Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 //�ϲ�A1û��ʶ��ʶ���ϲ�A2��
 if(flaga!=1&&flaga!=2&&flaga!=3){
 Go(4,-1,RightDistans);	//����һ�ξ���
 delay_MS(3000);
 Go(3,-1,500);	//����һ�ξ���ץȡ
 delay_MS(1000);
 catch1();      //ץȡ
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,-1,3000);	//����ä��
 Go(2,0,10);	//����һ�� 
 delay_MS(1000);
 Go(3,-1,240);	//����һ�ξ���a��A�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put1();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 flaga=4;
 a='1';
 Go(1,-1,3000);	//ǰ��ä��
 Go(1,0,10);	//ǰ��һ�񵽴�A����ǰʮ�� 
 }
 
 delay_MS(1000);
 Go(4,1,5);     //����һ��׼��ʶ��B����
 //A����ʶ����ϣ�ͣ����B����ǰ��ʮ�֣���ץȡ�ϲ�A1��flaga=1,ץȡ�ϲ�A2����flaga=2,��ûץflaga=0
 
 //B����
 
 delay_MS(1000);
 Go(3,-1,LeftDistans);	//����һ�ξ���a���������
 //ʶ��B1��
 if(flagb!=1&&flagb!=2){
 delay_MS(3000);
 while(a!='s')
{
 putchar0(Shelf_B_DOWN);    //����B�����ϲ���a���
 delay_MS(1000);
 a=getchar0();     //��ȡһ���ַ�
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ
 delay_MS(1000);
 catch1();      //ץȡ
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,2,10);	//����ǰ������ 
 delay_MS(1000);
 Go(3,1,10);	//����һ��
 delay_MS(1000);
 Go(4,-1,220);	//����һ�ξ��뵽B�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put1();		//����
 delay_MS(1000);
 Server5(37,80);//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		
 delay_MS(1000);
 Go(1,2,5);     //�ص�B��������ʮ��
 delay_MS(1000);
 flagb=3;
 a='1';
 }
 else Go(4,0,5);		//����ֱ�ӻص�Bǰ�����ʮ��
 delay_MS(1000);
 //�ϲ�B1û��ʶ��ʶ���ϲ�B2��
 Go(4,-1,RightDistans);	//����һ�ξ���
 //ʶ��B2��
 delay_MS(3000);
 if(flagb!=1&&flagb!=2&&flagb!=3){
 Go(3,-1,500);	//����һ�ξ���ץȡ
 catch1();      //ץȡ
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,2,10);	//�������� 
 delay_MS(1000);
 Go(3,1,10);	//����һ��
 delay_MS(1000);
 Go(4,-1,220);	//����һ�ξ��뵽B�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put1();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		//�ص�B��������ʮ��
 delay_MS(1000);
 flagb=2;
 a='1';
 Go(1,2,5);    //ǰ������ص�B����ǰʮ��
 delay_MS(1000);
 }
 Go(4,1,5);    //����һ��׼��ʶ��C����,��C����ǰ��
  
 //C����
 delay_MS(1000);
 Go(3,-1,LeftDistans);	//����һ�ξ���a���������
 //ʶ��C1��
 delay_MS(3000);
 if(flagc!=1&&flagc!=2){
 while(a!='s')
{
 putchar0(Shelf_C_UP);    //����C������e���
 delay_MS(1000);
 a=getchar0();     //��ȡһ���ַ�
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ
 delay_MS(1000); 
 catch1();      //ץȡ
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,2,10);	//����ǰ������ 
 delay_MS(1000);
 Go(4,1,5);	//����һ��
 delay_MS(1000);
 Go(3,-1,240);	//����һ�ξ��뵽C�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put1();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(2000);
 Go(3,0,5);		//����һ�ξ��뵽C�������Ե�ʮ��
 delay_MS(1000);
 Go(1,2,5);		//ǰ������C����ǰ��ʮ��
 delay_MS(1000);
 flagc=3;
 a='1';
 }
 else Go(4,0,5);//����ֱ�ӻص�Cǰ�����ʮ��
 delay_MS(1000);
 //C1û��ʶ��C2�е�
 Go(4,-1,RightDistans);	//����һ�ξ���
delay_MS(3000);
 if(flagc!=1&&flagc!=2&&flagc!=3){
 while(a!='s')
{
 putchar0(Shelf_C_UP);    //����C������e���
 delay_MS(1000);
 a=getchar0();     //��ȡһ���ַ�
 delay_MS(1000);
 };
 delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ*/
 Go(3,-1,500);	//����һ�ξ���ץȡ
 catch1();      //ץȡ
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,2,10);	//����ǰ������ 
 delay_MS(1000);
 Go(4,1,10);	//����һ��
 delay_MS(1000);
 Go(3,-1,240);//����һ�ξ��뵽C�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put1();		//����
 delay_MS(1000);
 Server5(37,80);//ˮƽǰת  
 delay_MS(2000);
 Go(3,0,5);		//����һ�ξ��뵽C�������Ե�ʮ��
 delay_MS(1000);
 flagc=4;
 a='1';
 Go(1,2,5);		//ǰ������Cǰ��ʮ��
 delay_MS(1000);
 }
 Go(4,1,5);		//����һ��Dǰ��ʮ��
 delay_MS(1000);
//׼��ʶ��D����
 //D����
Go(3,-1,240);	//����һ�ξ���a���������
 //ʶ��D1��
 delay_MS(3000);
if(flagd!=1&&flagd!=2){
while(a!='s')
{
putchar0(Shelf_D_UP);    //����A�����ϲ���b���
delay_MS(1000);
a=getchar0();     //��ȡһ���ַ�
delay_MS(1000);
};
delay_MS(1000);
 a=getchar0();
 delay_MS(1000);
 }
 if(a=='t'){    //���ʶ����ȷ
 delay_MS(1000); 
 catch1();      //ץȡ
 delay_MS(1000); 
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,-1,3000);	//����ä��
 Go(2,0,10);	//����ǰ��һ�� 
 delay_MS(1000);
 Go(4,-1,220);	//����һ�ξ���a��D�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put1();		//����
 delay_MS(1000);
 Server5(37,80); 	//ˮƽǰת  
 delay_MS(1000);
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 flagd=3;  
 a='1';  
 Go(1,-1,3000);	//ǰ��ä��
 Go(1,0,10);	//ǰ��һ�񵽴�D����ǰʮ��
 delay_MS(1000); 
 }
 else Go(4,0,5);		//�ص�Dǰ����ʮ��
 delay_MS(1000);
 //�ϲ�D1û��ʶ��ʶ���ϲ�D2��
 Go(4,-1,220);	//����һ�ξ���
 if(flagd!=1&&flagc!=2&&flagc!=3){
 delay_MS(1000); 
 catch1();      //ץȡ
 Go(3,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 Go(2,-1,3000);	//����ä��
 Go(2,0,10);	//����һ�� 
 delay_MS(1000);
 Go(4,-1,220);	//����һ�ξ���a��D�Ż���
 delay_MS(1000);
 Server5(7,80); //ˮƽ��ת
 delay_MS(1000);
 put1();		//����
 delay_MS(1000);
 Server5(37,80);//ˮƽǰת  
 delay_MS(1000);
 Go(4,0,5);		//�ص�����ʮ��
 delay_MS(1000);
 flagd=4;
 a='1';
 Go(1,-1,3000);	//ǰ��ä��
 Go(1,0,10);	//ǰ��һ�񵽴�D����ǰʮ�� 
 delay_MS(1000);
 }
 Go(3,0,5);     //����һ�񵽴�D����ǰʮ��
 delay_MS(1000);
 }