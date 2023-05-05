#include "control.h"	

float velocity_KP=6;     // 小车速度环PI参数
float velocity_KI=6;
int sensor[2];
int count = 0;
int Count = 0;
u8 UltrasonicWave_Voltage_Counter=0;

void TIM3_IRQHandler(void)   //TIM3中断
{
	int Velocity=0,Turn=0;
	sensor[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	sensor[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);

	
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
//		Count++;
//			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
////			
//		  Led_Flash(100);
//			Encoder_Right=-Read_Encoder(2);                           //===读取编码器的值，因为两个电机的旋转了180度的，所以对其中一个取反，保证输出极性一致
//			Encoder_Left=Read_Encoder(4);                           //===读取编码器的值
//			UltrasonicWave_Voltage_Counter++;
//			if(UltrasonicWave_Voltage_Counter==10)									 //===100ms读取一次超声波的数据以及电压
//			{
//				UltrasonicWave_Voltage_Counter=0;
//				Voltage=Get_battery_volt();		                         //===读取电池电压		
//			}
//			Velocity=velocity();
//			Turn=turn();
//			if(sensor[0] == 0)
//			{
//				Turn = 10;
//			}
//			else if(sensor[1] == 0)
//			{
//				Turn = -10;
//			}
//			Kinematic_Analysis(Velocity,Turn);
//			Moto1=Incremental_PI_A(Encoder_Left,Target_A);                 //===计算左轮电机最终PWM
//			Moto2=Incremental_PI_B(Encoder_Right,Target_B);                 //===计算右轮电机最终PWM
//			Xianfu_Pwm();  																					 //===PWM限幅
//			Turn_Off(Voltage);																 //===检查角度以及电压是否正常
//			Set_Pwm(Moto1,Moto2);                                    //===赋值给PWM寄存器  
	}
}

/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}


int velocity(void)
{  
		float Velocity;
		float kp_chaoshengbo_zhixian=0.15;//直线超声波PID环控制参数
		float line_distanceL,line_distanceR;//超声波的距离
		float set_distance=800;							//控制小车在800mm之内
	
		line_distanceL=distanceL-set_distance;
		line_distanceR=distanceR-set_distance;
		//=============自动跟随部分=======================//
		if((line_distanceL>0&&line_distanceR>0)||(line_distanceL<0&&line_distanceR<0))		
		{
			Velocity=kp_chaoshengbo_zhixian*((line_distanceL+line_distanceR)/2);
		}		

		if(distanceL>4000||distanceR>4000) Velocity=0;
		return Velocity;
}

int turn(void)//转向控制
{
	
	  float Turn;
	  float Kp1=0.2; 											//超声波控制部分转向PID参数  
	  float cha1;
		//=============自动跟随部分=======================/
			cha1=distanceL-distanceR;
		if(distanceL>20&&distanceL<4000&&distanceR>20&&distanceR<4000)
		{
			if(cha1<0) 	
			{

					Turn=cha1*Kp1;
			}
			else if(cha1>0) 	
			{	
					Turn=cha1*Kp1;
			}
		}
		else 
		{
				Turn=0;
		}		
		return Turn;
}
/**************************************************************************
函数功能：小车运动数学模型
入口参数：速度和转角
返回  值：无
**************************************************************************/
void Kinematic_Analysis(int velocity,int turn)
{
		Target_A=velocity+turn; 
		Target_B=velocity-turn;      //后轮差速
}
