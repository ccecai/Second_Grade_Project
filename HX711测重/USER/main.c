//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-10-31
//  最近修改   : 
//  功能描述   : OLED I2C接口演示例程(STM32F103系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND  电源地
//              VCC  3.3v电源
//              D0   PA0（SCL）
//              D1   PA1（SDA）
//              RES  PA2（SPI模块改成IIC模块需要接此引脚，IIC模块用户请忽略）
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "HX711.h"
#include "usart.h"


int main(void)
{	
	int car = 0;
	int dis;
	int i;
	int flag;
	int sum;
	int final=0;
	int once = 0;
	int finalweight = 0;
   int yuzhi = 800;
	int Rxdata = 0;
	delay_init();
	OLED_Init();
//	Serial_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
  uart_init(115200);	 	//串口初始化为115200
	OLED_Refresh();
	OLED_Clear();
//	OLED_ShowNum(0,0,111,5,16,1);
	Init_HX711pin();
	Get_Maopi();				//称毛皮重量
	delay_ms(2000);
	Get_Maopi();				//重新获取毛皮重量
	delay_ms(2000);
	OLED_Refresh();
	OLED_Clear();
		while(1)
	{
		Get_Weight();
		dis = abs(Weight_Shiwu-car);
		OLED_ShowNum(0,0,Weight_Shiwu,6,16,1);
    OLED_Refresh();
		//以下为取稳定值部分，dis是前一次测量的重量与目前测量重量的差值绝对值，
		//flag用于记录前后测量差值是否一直小于阈值，如果前一次
		//测量小于阈值后一次又大于阈值，则flag清零，不过这个没啥用 ：）
		//有用的是i，如果连续小于测i++，如果中途有一次大于阈值，那么i就是0，sum也为0.当i可以计数到30，就代表连续30次测量的差值都小于阈值
		//那么就可以认为，这是一个稳定的值，同时，sum也连续积累了30个稳定的值之和所以除以30，就是这30个稳定值的平均数final，显示出来
		//就是OLED第二行显示的数字
		//至于finalweight，是一个可以刷新的值，是取测量的稳定值中最大的那个，这里因为项目需要没用这个参数
    if (dis<yuzhi)		
		{
			flag=1;
			i++;
			sum=sum+Weight_Shiwu;
		}
		else if(dis>=yuzhi)
		{
			flag=0;//flag没有用
			i=0;
			sum = 0;
			final = 0;
		}
		car = Weight_Shiwu;//没啥用这里
		if(i==30)
		{
			final = sum/30;
			once++;//没有用
			
		}
    if(final>finalweight){
			finalweight=final;//让finalweight一直取测量的最大稳定重量，因为我们要设置侧重区间的信号，所以这个没有用
		}
		OLED_ShowNum(0,16,final,6,16,1);//显示刚刚测出来的稳定值
		OLED_Refresh();
		
//		OLED_Clear();

		
//		printf("净重量 = %d g\r\n",Weight_Shiwu); //打印 
//		delay_ms(1000);
     

	}
//	u8 t=' ';
//	delay_init();
//	OLED_Init();
//	OLED_ColorTurn(0);//0正常显示，1 反色显示
//  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
//    uart_init(115200);	 	//串口初始化为115200
//	while(1)
//	{
//		printf("%d",1);
//		delay_ms(1000);
//		OLED_ShowPicture(0,0,128,64,BMP1,1);
//		OLED_Refresh();
//		delay_ms(500);
//		OLED_Clear();
//		OLED_ShowChinese(0,0,0,16,1);//中
//		OLED_ShowChinese(18,0,1,16,1);//景
//		OLED_ShowChinese(36,0,2,16,1);//园
//		OLED_ShowChinese(54,0,3,16,1);//电
//		OLED_ShowChinese(72,0,4,16,1);//子
//		OLED_ShowChinese(90,0,5,16,1);//技
//		OLED_ShowChinese(108,0,6,16,1);//术
//		OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
//		OLED_ShowString(20,32,"2014/05/01",16,1);
//		OLED_ShowString(0,48,"ASCII:",16,1);  
//		OLED_ShowString(63,48,"CODE:",16,1);
//		OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	   
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,48,t,3,16,1);
//		OLED_Refresh();
//		delay_ms(500);
//		OLED_Clear();
//		OLED_ShowChinese(0,0,0,16,1);  //16*16 中
//	  OLED_ShowChinese(16,0,0,24,1); //24*24 中
//		OLED_ShowChinese(24,20,0,32,1);//32*32 中
//	  OLED_ShowChinese(64,0,0,64,1); //64*64 中
//		OLED_Refresh();
//	  delay_ms(500);
//  	OLED_Clear();
//		OLED_ShowString(0,0,"ABC",8,1);//6*8 “ABC”
//		OLED_ShowString(0,8,"ABC",12,1);//6*12 “ABC”
//	  OLED_ShowString(0,20,"ABC",16,1);//8*16 “ABC”
//		OLED_ShowString(0,36,"ABC",24,1);//12*24 “ABC”
//	  OLED_Refresh();
//		delay_ms(500);
//		OLED_ScrollDisplay(11,4,1);
//	}
}

