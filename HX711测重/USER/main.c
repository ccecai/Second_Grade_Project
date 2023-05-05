//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-10-31
//  ����޸�   : 
//  ��������   : OLED I2C�ӿ���ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              D0   PA0��SCL��
//              D1   PA1��SDA��
//              RES  PA2��SPIģ��ĳ�IICģ����Ҫ�Ӵ����ţ�IICģ���û�����ԣ�
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018-10-31
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
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	OLED_Refresh();
	OLED_Clear();
//	OLED_ShowNum(0,0,111,5,16,1);
	Init_HX711pin();
	Get_Maopi();				//��ëƤ����
	delay_ms(2000);
	Get_Maopi();				//���»�ȡëƤ����
	delay_ms(2000);
	OLED_Refresh();
	OLED_Clear();
		while(1)
	{
		Get_Weight();
		dis = abs(Weight_Shiwu-car);
		OLED_ShowNum(0,0,Weight_Shiwu,6,16,1);
    OLED_Refresh();
		//����Ϊȡ�ȶ�ֵ���֣�dis��ǰһ�β�����������Ŀǰ���������Ĳ�ֵ����ֵ��
		//flag���ڼ�¼ǰ�������ֵ�Ƿ�һֱС����ֵ�����ǰһ��
		//����С����ֵ��һ���ִ�����ֵ����flag���㣬�������ûɶ�� ����
		//���õ���i���������С�ڲ�i++�������;��һ�δ�����ֵ����ôi����0��sumҲΪ0.��i���Լ�����30���ʹ�������30�β����Ĳ�ֵ��С����ֵ
		//��ô�Ϳ�����Ϊ������һ���ȶ���ֵ��ͬʱ��sumҲ����������30���ȶ���ֵ֮�����Գ���30��������30���ȶ�ֵ��ƽ����final����ʾ����
		//����OLED�ڶ�����ʾ������
		//����finalweight����һ������ˢ�µ�ֵ����ȡ�������ȶ�ֵ�������Ǹ���������Ϊ��Ŀ��Ҫû���������
    if (dis<yuzhi)		
		{
			flag=1;
			i++;
			sum=sum+Weight_Shiwu;
		}
		else if(dis>=yuzhi)
		{
			flag=0;//flagû����
			i=0;
			sum = 0;
			final = 0;
		}
		car = Weight_Shiwu;//ûɶ������
		if(i==30)
		{
			final = sum/30;
			once++;//û����
			
		}
    if(final>finalweight){
			finalweight=final;//��finalweightһֱȡ����������ȶ���������Ϊ����Ҫ���ò���������źţ��������û����
		}
		OLED_ShowNum(0,16,final,6,16,1);//��ʾ�ող�������ȶ�ֵ
		OLED_Refresh();
		
//		OLED_Clear();

		
//		printf("������ = %d g\r\n",Weight_Shiwu); //��ӡ 
//		delay_ms(1000);
     

	}
//	u8 t=' ';
//	delay_init();
//	OLED_Init();
//	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
//  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
//	while(1)
//	{
//		printf("%d",1);
//		delay_ms(1000);
//		OLED_ShowPicture(0,0,128,64,BMP1,1);
//		OLED_Refresh();
//		delay_ms(500);
//		OLED_Clear();
//		OLED_ShowChinese(0,0,0,16,1);//��
//		OLED_ShowChinese(18,0,1,16,1);//��
//		OLED_ShowChinese(36,0,2,16,1);//԰
//		OLED_ShowChinese(54,0,3,16,1);//��
//		OLED_ShowChinese(72,0,4,16,1);//��
//		OLED_ShowChinese(90,0,5,16,1);//��
//		OLED_ShowChinese(108,0,6,16,1);//��
//		OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
//		OLED_ShowString(20,32,"2014/05/01",16,1);
//		OLED_ShowString(0,48,"ASCII:",16,1);  
//		OLED_ShowString(63,48,"CODE:",16,1);
//		OLED_ShowChar(48,48,t,16,1);//��ʾASCII�ַ�	   
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,48,t,3,16,1);
//		OLED_Refresh();
//		delay_ms(500);
//		OLED_Clear();
//		OLED_ShowChinese(0,0,0,16,1);  //16*16 ��
//	  OLED_ShowChinese(16,0,0,24,1); //24*24 ��
//		OLED_ShowChinese(24,20,0,32,1);//32*32 ��
//	  OLED_ShowChinese(64,0,0,64,1); //64*64 ��
//		OLED_Refresh();
//	  delay_ms(500);
//  	OLED_Clear();
//		OLED_ShowString(0,0,"ABC",8,1);//6*8 ��ABC��
//		OLED_ShowString(0,8,"ABC",12,1);//6*12 ��ABC��
//	  OLED_ShowString(0,20,"ABC",16,1);//8*16 ��ABC��
//		OLED_ShowString(0,36,"ABC",24,1);//12*24 ��ABC��
//	  OLED_Refresh();
//		delay_ms(500);
//		OLED_ScrollDisplay(11,4,1);
//	}
}

