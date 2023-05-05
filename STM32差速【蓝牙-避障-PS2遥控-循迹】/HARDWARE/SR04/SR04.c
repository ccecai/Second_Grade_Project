#include "SR04.h"
#include "timer.h"
/**************************************************************************
 作  者 ：大鱼电子
 淘宝地址：https://shop119207236.taobao.com
 微信公众号【大鱼机器人】
 后台回复【平衡小车】：获取平衡小车全套DIY资料
 后台回复【电子开发工具】：获取电子工程师必备开发工具
 后台回复【电子设计资料】：获取电子设计资料包
 知乎：张巧龙 
**************************************************************************/
#define	TRIG_PIN       GPIO_Pin_10   //TRIG       
#define	ECHO_PIN       GPIO_Pin_11		//ECHO   
/*
 * 函数名：SR04_Configuration
 * 描述  ：超声波模块的初始化
 * 输入  ：无
 * 输出  ：无	
 */
void SR04_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					 //PB10接TRIG
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //设为推挽输出模式
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
	  GPIO_Init(GPIOB, &GPIO_InitStructure);	                 //初始化外设GPIO 

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				     //PB11接ECH0
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //设为输入
	  GPIO_Init(GPIOB,&GPIO_InitStructure);						 //初始化GPIOB
	
	 //GPIOB.11	  中断线以及中断初始化配置
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);

 	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器	
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}


void EXTI15_10_IRQHandler(void)
{
	u8 i = 0;
	u8 fac_us=SystemCoreClock/8000000;
	u32 tnow;
	float tcnt=0;
	float Distance[10];
	Flag_Direction=16;
	delay_us(1700);		//避障代码有问题，无法精确测量出距离，此时延迟较高原因为希望可以探测到较远距离（原为10）
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
		while(i!=10){
			SysTick->LOAD=65535;					//LOAD的值
			SysTick->VAL=65535;        					//刚进入时的计数器值
			SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	
			while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN));//等待低电平
			tnow=SysTick->VAL;
			SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
			tcnt+=65535-tnow;
			Distance[i]=tcnt*340/fac_us/1000/7.25;			//计算距离，未完成待修正
			i++;
		}
		SR04_Distance = (Distance[0]+Distance[1]+Distance[2]+Distance[3]+Distance[4]+Distance[5]+Distance[6]+Distance[7]+Distance[8]+Distance[9])/10;
		i = 0;
	}
	EXTI_ClearITPendingBit(EXTI_Line11);  //清除EXTI11线路挂起位
}		

/*
 * 函数名：SR04_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
void SR04_StartMeasure(void)
{
  GPIO_SetBits(GPIOB,TRIG_PIN); 		  //送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有说
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(GPIOB,TRIG_PIN);
}

/******************* (C) 1209 Lab *****END OF FILE************/

void hc_sr04_calculate(void)
{
	float temp;
	while(ECHO_PIN==1);
	SR04_StartMeasure();//启动hc_sr04超声波传感器
	while(ECHO_PIN==0);
	delay_ms(500);
	TIM_SetCounter(TIM5,0);//清空计数器
	TIM_Cmd(TIM5,ENABLE);//开启定时器
	while(ECHO_PIN==1);//如果hc_sr04返回低电平说明还未检测到前面有障碍物，就一直执行该程序
	TIM_Cmd(TIM5,DISABLE);//停止计数
	temp=TIM_GetCounter(TIM5)*340/(2*1000);
	SR04_Distance = temp;
}

