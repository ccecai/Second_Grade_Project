#include "control.h"	
#include "delay.h"
#include "Track.h"
/**************************************************************************
 ��  �� ���������
 �Ա���ַ��https://shop119207236.taobao.com
 ΢�Ź��ںš���������ˡ�
 ��̨�ظ���ƽ��С��������ȡƽ��С��ȫ��DIY����
 ��̨�ظ������ӿ������ߡ�����ȡ���ӹ���ʦ�ر���������
 ��̨�ظ�������������ϡ�����ȡ����������ϰ�
 ֪���������� 
**************************************************************************/
/**************************************************************************
�������ܣ����еĿ��ƴ��붼��������
         Timer3 10ms��ʱ�ж�
**************************************************************************/

#define SPEED_Y 40 //ǰ������趨�ٶ�
#define SPEED_Z 100//��������趨�ٶ� 


//��Բ�ͬ���Ͳ�������sys.h������define�ĵ������
float velocity_KP=SPD_KP;     // С���ٶȻ�PI����
float velocity_KI=SPD_KI;

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	static u8 Voltage_Counter=0;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		  Led_Flash(100);
			Encoder_Right=-Read_Encoder(2);                           //===��ȡ��������ֵ����Ϊ�����������ת��180�ȵģ����Զ�����һ��ȡ������֤�������һ��
			Encoder_Left=Read_Encoder(4);                           //===��ȡ��������ֵ
		
			Voltage_Counter++;
			if(Voltage_Counter==10)									 //===100ms��ȡһ�γ������������Լ���ѹ
			{
				Voltage_Counter=0;
				Voltage=Get_battery_volt();		                         //===��ȡ��ص�ѹ		
			}
			if(KEY_Press(100))																				//���������л�ģʽ������ģʽ�л���ʼ��
			{
				if(++CTRL_MODE>=101) CTRL_MODE=97;
				Mode_Change=1;
			}
			
			Get_RC();
//			Kinematic_Analysis(Velocity,Turn);
			Read_Sensor();
			Moto1=Incremental_PI_A(Encoder_Left,Target_A);                 //===�������ֵ������PWM
			Moto2=Incremental_PI_B(Encoder_Right,Target_B);                 //===�������ֵ������PWM
			Xianfu_Pwm();  																					 //===PWM�޷�
			Turn_Off(Voltage);																 //===���Ƕ��Լ���ѹ�Ƿ�����
			Set_Pwm(Moto1,Moto2);                                    //===��ֵ��PWM�Ĵ���  
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

void Get_RC()
{
	static u8 SR04_Counter =0;
	static int MAX_VEL=80,MAX_TURN=40;
	float RATE_VEL = 128/MAX_VEL;
	float RATE_TURN = 128/MAX_TURN;
	float step=1;  //�����ٶȿ��Ʋ���ֵ��
	float LY,RX;  //PS2�ֱ����Ʊ���
	int Yuzhi=2;  		//PS2���Ʒ�����ֵ
	
	if(CTRL_MODE ==98)//����APP����
	{
		switch(Flag_Direction)   //�������
		{
			case 0: 
				if(myabs(Velocity)>step)
				{
					if(Velocity>0) Velocity-=step;
					else Velocity+=step;
				}
				else Velocity=0;
				Turn=0;        	 
				break;	 //ֹͣ
			case 1:      Velocity+=step;  	 				 Turn=0;       		 break;//ǰ��
			case 2:      Velocity+=step;  	 	 			 Turn+=step;   	 	 break;//��ǰ
			case 3:      Velocity=0;      				 	 Turn+=step;   		 break;//��ת
			case 4:      Velocity-=step;  					 Turn-=step; 			 break;//�Һ�
			case 5:      Velocity-=step;  					 Turn=0;       		 break;//����
			case 6:      Velocity-=step;  					 Turn+=step;   		 break;//���
			case 7:      Velocity=0;     	 			 	 Turn-=step;			 break;//��ת
			case 8:      Velocity+=step; 	 				 Turn-=step;			 break; //��ǰ
			default:     break;	 
		}
	}
	else if(CTRL_MODE == 100)//PS2����
	{
		if(PS2_Plugin)
		{
			LY=PS2_LY-128; //��ȡƫ��
			RX=PS2_RX-128; //��ȡƫ��
			if(LY>-Yuzhi&&LY<Yuzhi)LY=0; //����С�Ƕȵ�����
			if(RX>-Yuzhi&&RX<Yuzhi)RX=0; //����С�Ƕȵ�����
			if(Velocity>-LY/RATE_VEL) Velocity-=step;
			else if(Velocity<-LY/RATE_VEL) Velocity+=step;
			Turn=RX/RATE_TURN;
		}
		else
		{
			Velocity=0,Turn=0;
		}
	}
	else if(CTRL_MODE == 97)
	{
		SR04_Counter++;
		if(SR04_Counter>=20)									         //100ms��ȡһ�γ�����������
		{
			SR04_Counter=0;
			SR04_StartMeasure();												 //��ȡ��������ֵ
		}
		if(SR04_Distance<=100)
		{
			Turn=40;
//			Turn_Off1();
////			delay_ms(500);
		}
		else
			Turn=0;
	}
//	else if(CTRL_MODE == 99)
//	{
//		Tracking();
//		switch(TkSensor)
//		{
//			case 15:
//				Velocity=0;
//				Turn=0;
//				break;
//			case 9:
//				Velocity--;
//				Turn=0;
//				break;
//			case 2://����ת
//				Velocity--;
//				Turn=15;
//				break;
//			case 4://����ת
//				Velocity--;
//				Turn=-15;
//				break;
//			case 8:
//				Velocity=-10;
//				Turn=-80;
//				break;
//			case 1:
//				Velocity=-10;
//				Turn=80;
//				break;
//		}
//	}
	
	if(Velocity>80)Velocity=MAX_VEL;
	else if(Velocity<-80)Velocity=-MAX_VEL;
	if(Turn>40)Turn=MAX_TURN;
	else if(Turn<-40)Turn=-MAX_TURN;
}
//void Tracking()
//{
//	TkSensor=0;
//	TkSensor+=(C1<<3);
//	TkSensor+=(C2<<2);
//	TkSensor+=(C3<<1);
//	TkSensor+=C4;
//}
