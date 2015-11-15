#include <Servo.h>
//底盘步进
#define step0_clk 36
#define step0_CW  38
#define step0_EN  40

#define step1_clk 30
#define step1_CW  32
#define step1_EN  34

#define step2_clk 31
#define step2_CW  33
#define step2_EN  35

#define step3_clk 37
#define step3_CW  39
#define step3_EN  41

//收集步进
#define StepA_ENA 42
#define StepA_IN1 44
#define StepA_IN2 46
#define StepA_IN3 48
#define StepA_IN4 50
#define StepA_ENB 52

#define StepB_ENA 43
#define StepB_IN1 45
#define StepB_IN2 47
#define StepB_IN3 49
#define StepB_IN4 51
#define StepB_ENB 53

//丝杆步进
#define StepS_clk 24
#define StepS_CW  26
#define StepS_EN  28

//舵机
#define Steer0     9
#define Steer1	  10

#define col       22

Servo Collect, Push;

//初始化
void setup(){
	Serial.begin(9600);
	pinMode(step0_clk, OUTPUT);
	pinMode(step0_CW,  OUTPUT);
	pinMode(step0_EN,  OUTPUT); digitalWrite(step0_EN,  HIGH);
	pinMode(step1_clk, OUTPUT);
	pinMode(step1_CW,  OUTPUT);
	pinMode(step1_EN,  OUTPUT); digitalWrite(step1_EN,  HIGH);
	pinMode(step2_clk, OUTPUT);
	pinMode(step2_CW,  OUTPUT); 
	pinMode(step2_EN,  OUTPUT); digitalWrite(step2_EN,  HIGH);
	pinMode(step3_clk, OUTPUT);
	pinMode(step3_CW,  OUTPUT);
	pinMode(step3_EN,  OUTPUT); digitalWrite(step3_EN,  HIGH);
	
	pinMode(StepA_ENA, OUTPUT); digitalWrite(StepA_ENA, HIGH);
	pinMode(StepA_IN1, OUTPUT);
	pinMode(StepA_IN2, OUTPUT);
	pinMode(StepA_IN3, OUTPUT);
	pinMode(StepA_IN4, OUTPUT);
	pinMode(StepA_ENB, OUTPUT); digitalWrite(StepA_ENB, HIGH);
	pinMode(StepB_ENA, OUTPUT); digitalWrite(StepB_ENA, HIGH);
	pinMode(StepB_IN1, OUTPUT);
	pinMode(StepB_IN2, OUTPUT);
	pinMode(StepB_IN3, OUTPUT);
	pinMode(StepB_IN4, OUTPUT);
	pinMode(StepB_ENB, OUTPUT); digitalWrite(StepB_ENB, HIGH);
	
	pinMode(StepS_clk, OUTPUT);
	pinMode(StepS_CW,  OUTPUT);
	pinMode(StepS_EN,  OUTPUT); digitalWrite(StepS_EN,  HIGH);

	Collect.attach(Steer0);
	Push.attach(Steer1);
	delay(10000);
}

//底盘四步进电机控制函数，函数参数分别代表时间及速度，使用TB6560
//前进
void GoForward(int time, int speed){
	digitalWrite(step0_EN, LOW);
	digitalWrite(step0_CW, HIGH);
	digitalWrite(step2_EN, LOW);
	digitalWrite(step2_CW, LOW);
	int i;
	int turn = (int)(time / (float) speed * 500);
	for (i = 0; i < turn; i++){
		digitalWrite(step0_clk, LOW);
		digitalWrite(step2_clk, LOW);
		delayMicroseconds(speed);
		digitalWrite(step0_clk, HIGH);
		digitalWrite(step2_clk, HIGH);
		delayMicroseconds(speed);
	}
	digitalWrite(step0_EN, HIGH);
	digitalWrite(step2_EN, HIGH);
}

//后退
void GoBack(int time, int speed){
	digitalWrite(step0_EN, LOW);
	digitalWrite(step0_CW, LOW);
	digitalWrite(step2_EN, LOW);
	digitalWrite(step2_CW, HIGH);
	int i;
	int turn = (int)(time / (float) speed * 500);
	for (i = 0; i < turn; i++){
		digitalWrite(step0_clk, LOW);
		digitalWrite(step2_clk, LOW);
		delayMicroseconds(speed);
		digitalWrite(step0_clk, HIGH);
		digitalWrite(step2_clk, HIGH);
		delayMicroseconds(speed);
	}
	digitalWrite(step0_EN, HIGH);
	digitalWrite(step2_EN, HIGH);
}

//左行
void GoLeft(int time, int speed){
	digitalWrite(step1_EN, LOW);
	digitalWrite(step1_CW, HIGH);
	digitalWrite(step3_EN, LOW);
	digitalWrite(step3_CW, LOW);
	int i;
	int turn = (int)(time / (float) speed * 500);
	for (i = 0; i < turn; i++){
		digitalWrite(step1_clk, LOW);
		digitalWrite(step3_clk, LOW);
		delayMicroseconds(speed);
		digitalWrite(step1_clk, HIGH);
		digitalWrite(step3_clk, HIGH);
		delayMicroseconds(speed);
	}
	digitalWrite(step1_EN, HIGH);
	digitalWrite(step3_EN, HIGH);
}


//右行
void GoRight(int time, int speed){
	digitalWrite(step1_EN, LOW);
	digitalWrite(step1_CW, LOW);
	digitalWrite(step3_EN, LOW);
	digitalWrite(step3_CW, HIGH);
	int i;
	int turn = (int)(time / (float) speed * 500);
	for (i = 0; i < turn; i++){
		digitalWrite(step1_clk, LOW);
		digitalWrite(step3_clk, LOW);
		delayMicroseconds(speed);
		digitalWrite(step1_clk, HIGH);
		digitalWrite(step3_clk, HIGH);
		delayMicroseconds(speed);
	}
	digitalWrite(step1_EN, HIGH);
	digitalWrite(step3_EN, HIGH);
}

//左转
void TurnLeft(int time, int speed){
	digitalWrite(step1_EN, LOW);
	digitalWrite(step1_CW, HIGH);
	digitalWrite(step3_EN, LOW);
	digitalWrite(step3_CW, HIGH);
	digitalWrite(step0_EN, LOW);
	digitalWrite(step0_CW, HIGH);
	digitalWrite(step2_EN, LOW);
	digitalWrite(step2_CW, HIGH);
	int i;
	int turn = (int)(time / (float) speed * 500);
	for (i = 0; i < turn; i++){
		digitalWrite(step1_clk, LOW);
		digitalWrite(step3_clk, LOW);
		digitalWrite(step0_clk, LOW);
		digitalWrite(step2_clk, LOW);
		delayMicroseconds(speed);
		digitalWrite(step1_clk, HIGH);
		digitalWrite(step3_clk, HIGH);
		digitalWrite(step0_clk, HIGH);
		digitalWrite(step2_clk, HIGH);
		delayMicroseconds(speed);
	}
	digitalWrite(step1_EN, HIGH);
	digitalWrite(step3_EN, HIGH);
}

//右转
void TurnRight(int time, int speed){
	digitalWrite(step1_EN, LOW);
	digitalWrite(step1_CW, LOW);
	digitalWrite(step3_EN, LOW);
	digitalWrite(step3_CW, LOW);
	digitalWrite(step0_EN, LOW);
	digitalWrite(step0_CW, LOW);
	digitalWrite(step2_EN, LOW);
	digitalWrite(step2_CW, LOW);
	int i;
	int turn = (int)((time / (float) speed) * 500);
	for (i = 0; i < turn; i++){
		digitalWrite(step1_clk, LOW);
		digitalWrite(step3_clk, LOW);
		digitalWrite(step0_clk, LOW);
		digitalWrite(step2_clk, LOW);
		delayMicroseconds(speed);
		digitalWrite(step1_clk, HIGH);
		digitalWrite(step3_clk, HIGH);
		digitalWrite(step0_clk, HIGH);
		digitalWrite(step2_clk, HIGH);
		delayMicroseconds(speed);
	}
	digitalWrite(step1_EN, HIGH);
	digitalWrite(step3_EN, HIGH);
}

//丝杆步进，使用模块内部脉冲
//上升
void GoUp(int time){
	digitalWrite(StepS_EN, LOW);
	digitalWrite(StepS_CW, LOW);
	delay(time);
	digitalWrite(StepS_EN, HIGH);
}

//下降
void GoDown(int time){
	digitalWrite(StepS_EN, LOW);
	digitalWrite(StepS_CW, HIGH);
	delay(time);
	digitalWrite(StepS_EN, HIGH);
}

//收集槽步进电机控制，使用L298N模块
void CollectPushBack(int time, int speed){
	digitalWrite(StepA_ENA, 1);
	digitalWrite(StepA_ENB, 1);
	
	int i;
	int turn = time / speed / 4;
	for (i = 0; i < turn; i++){
		digitalWrite(StepA_IN1, 0);
		digitalWrite(StepA_IN2, 1);
		digitalWrite(StepA_IN3, 1);
		digitalWrite(StepA_IN4, 0);
		delay(speed);
		
		digitalWrite(StepA_IN1, 0);
		digitalWrite(StepA_IN2, 1);
		digitalWrite(StepA_IN3, 0);
		digitalWrite(StepA_IN4, 1);
		delay(speed);
		
		digitalWrite(StepA_IN1, 1);
		digitalWrite(StepA_IN2, 0);
		digitalWrite(StepA_IN3, 0);
		digitalWrite(StepA_IN4, 1);
		delay(speed);
		
		digitalWrite(StepA_IN1, 1);
		digitalWrite(StepA_IN2, 0);
		digitalWrite(StepA_IN3, 1);
		digitalWrite(StepA_IN4, 0);
		delay(speed);
	}
	digitalWrite(StepA_ENA, 0);
	digitalWrite(StepA_ENB, 0);
}

void CollectPushOut(int time, int speed){
	digitalWrite(StepA_ENA, 1);
	digitalWrite(StepA_ENB, 1);
	
	int i;
	int turn = time / speed / 4;
	for (i = 0; i < turn; i++){
		digitalWrite(StepA_IN1, 1);
		digitalWrite(StepA_IN2, 0);
		digitalWrite(StepA_IN3, 1);
		digitalWrite(StepA_IN4, 0);
		delay(speed);
		
		digitalWrite(StepA_IN1, 1);
		digitalWrite(StepA_IN2, 0);
		digitalWrite(StepA_IN3, 0);
		digitalWrite(StepA_IN4, 1);
		delay(speed);
		
		digitalWrite(StepA_IN1, 0);
		digitalWrite(StepA_IN2, 1);
		digitalWrite(StepA_IN3, 0);
		digitalWrite(StepA_IN4, 1);
		delay(speed);
		
		digitalWrite(StepA_IN1, 0);
		digitalWrite(StepA_IN2, 1);
		digitalWrite(StepA_IN3, 1);
		digitalWrite(StepA_IN4, 0);
		delay(speed);
	}
	digitalWrite(StepA_ENA, 0);
	digitalWrite(StepA_ENB, 0);
}

//串口通信，发送后接收
int Search(int i){
	Serial.write(i);
	while (1){
		if (Serial.available()){
			return Serial.read();
		}
	}
}