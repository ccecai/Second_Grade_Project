#include "stm32f10x.h"                  // Device header
 
#include "sys.h"
  
float Voltage;  															 //��ص�ѹ������صı���
float UltrasonicWave_Distance;                 //���������
int   Encoder_Left,Encoder_Right;         		 //���ұ��������������
int 	Moto1=0,Moto2=0,Target_A=0,Target_B=0;												 //������������ո��������PWM
int 	Flag_Qian,Flag_Hou,Flag_Left,Flag_Right; //����ң����صı���
u8    flag_UltrasonicWave=0;									 //�������Ƿ񳬳���ȫ�����־λ
u8    key=0;								 									 //�����ļ�ֵ

u8 key_mode, mode;   

void Bizhang_Init(void);

/***********************************************************************/
 unsigned char   dat1[3],dat2[3];
 unsigned char   num1,num2;
 int             distanceL,distanceR;	

/***********************************************************************/

int main(void)	
{ 
//	LED_Init();                    //=====��ʼ���� LED ���ӵ�IO
//	KEY_Init();                    //=====��ʼ���밴�����ӵ�IO
//	delay_init();	    	           //=====��ʱ������ʼ��	
//	uart1_init(128000);	           //=====����1��ʼ��
//	uart3_init(115200);            //=====��ʼ������3
//	uart2_init(115200);            //=====��ʼ������3
	NVIC_Configuration();					 //=====�ж����ȼ�����,���а��������е��ж����ȼ�������,��������һ�����޸ġ�
//	Adc_Init();                    //=====��ʼ��ADC
//	Encoder_Init_TIM2();           //=====��ʼ��������2
//	Encoder_Init_TIM4();           //=====��ʼ��������4
	
//	delay_ms(1000);								 //=====��ʱ1s ���С���ϵ�������ת������
//	OLED_Init();
//	OLED_Clear();
//	oled_first_show();
//	delay_ms(1000);								 //=====��ʱ1s ���С���ϵ�������ת������
//	Motor_Init();									 //=====��ʼ���������ӵ�Ӳ��IO�ӿ� 
//	Timer3_Init(100,7199);           //=====10MS��һ���жϷ��������жϷ�������control.c
//	Bizhang_Init();
//	
	
	LED_Init();	
TIM1_PWM_Init(200,450);   			 //=====��ʼ��PWM 10KHZ,������������� 
TIM_SetCompare1(TIM1,200/2);
  while(1)	
	{
//		oled_show();
//		delay_ms(50); //20HZ����ʾƵ�ʣ���Ļ����ʱ��ˢ�¡�
	} 	
}


void Bizhang_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��
  	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOB��ʱ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ��ù��ܵ�ʱ��
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//IO�ܽ�ģʽ����Ϊ�������룬�������ܻ�ȡ�������������������ź�(�ߵ͵�ƽ)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
} 



