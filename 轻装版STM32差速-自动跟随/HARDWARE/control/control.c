#include "control.h"	

float velocity_KP=6;     // С���ٶȻ�PI����
float velocity_KI=6;
int sensor[2];
int count = 0;
int Count = 0;
u8 UltrasonicWave_Voltage_Counter=0;

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	int Velocity=0,Turn=0;
	sensor[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	sensor[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);

	
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
//		Count++;
//			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
////			
//		  Led_Flash(100);
//			Encoder_Right=-Read_Encoder(2);                           //===��ȡ��������ֵ����Ϊ�����������ת��180�ȵģ����Զ�����һ��ȡ������֤�������һ��
//			Encoder_Left=Read_Encoder(4);                           //===��ȡ��������ֵ
//			UltrasonicWave_Voltage_Counter++;
//			if(UltrasonicWave_Voltage_Counter==10)									 //===100ms��ȡһ�γ������������Լ���ѹ
//			{
//				UltrasonicWave_Voltage_Counter=0;
//				Voltage=Get_battery_volt();		                         //===��ȡ��ص�ѹ		
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
//			Moto1=Incremental_PI_A(Encoder_Left,Target_A);                 //===�������ֵ������PWM
//			Moto2=Incremental_PI_B(Encoder_Right,Target_B);                 //===�������ֵ������PWM
//			Xianfu_Pwm();  																					 //===PWM�޷�
//			Turn_Off(Voltage);																 //===���Ƕ��Լ���ѹ�Ƿ�����
//			Set_Pwm(Moto1,Moto2);                                    //===��ֵ��PWM�Ĵ���  
	}
}

/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}


int velocity(void)
{  
		float Velocity;
		float kp_chaoshengbo_zhixian=0.15;//ֱ�߳�����PID�����Ʋ���
		float line_distanceL,line_distanceR;//�������ľ���
		float set_distance=800;							//����С����800mm֮��
	
		line_distanceL=distanceL-set_distance;
		line_distanceR=distanceR-set_distance;
		//=============�Զ����沿��=======================//
		if((line_distanceL>0&&line_distanceR>0)||(line_distanceL<0&&line_distanceR<0))		
		{
			Velocity=kp_chaoshengbo_zhixian*((line_distanceL+line_distanceR)/2);
		}		

		if(distanceL>4000||distanceR>4000) Velocity=0;
		return Velocity;
}

int turn(void)//ת�����
{
	
	  float Turn;
	  float Kp1=0.2; 											//���������Ʋ���ת��PID����  
	  float cha1;
		//=============�Զ����沿��=======================/
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
�������ܣ�С���˶���ѧģ��
��ڲ������ٶȺ�ת��
����  ֵ����
**************************************************************************/
void Kinematic_Analysis(int velocity,int turn)
{
		Target_A=velocity+turn; 
		Target_B=velocity-turn;      //���ֲ���
}
