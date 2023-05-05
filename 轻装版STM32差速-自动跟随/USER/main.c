#include "stm32f10x.h"                  // Device header
 
#include "sys.h"
  
float Voltage;  															 //电池电压采样相关的变量
float UltrasonicWave_Distance;                 //超声波测距
int   Encoder_Left,Encoder_Right;         		 //左右编码器的脉冲计数
int 	Moto1=0,Moto2=0,Target_A=0,Target_B=0;												 //计算出来的最终赋给电机的PWM
int 	Flag_Qian,Flag_Hou,Flag_Left,Flag_Right; //蓝牙遥控相关的变量
u8    flag_UltrasonicWave=0;									 //超声波是否超出安全距离标志位
u8    key=0;								 									 //按键的键值

u8 key_mode, mode;   

void Bizhang_Init(void);

/***********************************************************************/
 unsigned char   dat1[3],dat2[3];
 unsigned char   num1,num2;
 int             distanceL,distanceR;	

/***********************************************************************/

int main(void)	
{ 
//	LED_Init();                    //=====初始化与 LED 连接的IO
//	KEY_Init();                    //=====初始化与按键连接的IO
//	delay_init();	    	           //=====延时函数初始化	
//	uart1_init(128000);	           //=====串口1初始化
//	uart3_init(115200);            //=====初始化串口3
//	uart2_init(115200);            //=====初始化串口3
	NVIC_Configuration();					 //=====中断优先级分组,其中包含了所有的中断优先级的配置,方便管理和一次性修改。
//	Adc_Init();                    //=====初始化ADC
//	Encoder_Init_TIM2();           //=====初始化编码器2
//	Encoder_Init_TIM4();           //=====初始化编码器4
	
//	delay_ms(1000);								 //=====延时1s 解决小车上电轮子乱转的问题
//	OLED_Init();
//	OLED_Clear();
//	oled_first_show();
//	delay_ms(1000);								 //=====延时1s 解决小车上电轮子乱转的问题
//	Motor_Init();									 //=====初始化与电机连接的硬件IO接口 
//	Timer3_Init(100,7199);           //=====10MS进一次中断服务函数，中断服务函数在control.c
//	Bizhang_Init();
//	
	
	LED_Init();	
TIM1_PWM_Init(200,450);   			 //=====初始化PWM 10KHZ,用于驱动电机。 
TIM_SetCompare1(TIM1,200/2);
  while(1)	
	{
//		oled_show();
//		delay_ms(50); //20HZ的显示频率，屏幕无需时刻刷新。
	} 	
}


void Bizhang_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
  	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOB的时钟
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能的时钟
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//IO管脚模式配置为浮空输入，这样就能获取传感器传回来的数字信号(高低电平)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
} 



