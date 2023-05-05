#include "stm32f10x.h"                  // Device header
#include "motor.h"
u8 sensor[5];

extern int Target_A,Target_B;
extern int Turn_flag1,Turn_flag2;
int Zhuanwan_flag = 0;
int Count = 0;
extern int count;



void Read_Sensor(void)
{
	
				sensor[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
				sensor[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
				sensor[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
				sensor[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	count++;
	if(sensor[0]==0&&sensor[1]==1&&sensor[2]==1&&sensor[3]==0)
	{
		Target_A = 50;
		Target_B = 50;
//		Turn_flag1 = 0;
	}
	else if(sensor[0]==0&&sensor[1]==1&&sensor[2]==0&&sensor[3]==0)
	{
		Target_A = 42;
		Target_B = 50;
//		Turn_flag1 = 0;
	}
//	else if(sensor[0]==1&&sensor[1]==0&&sensor[2]==0&&sensor[3]==0) 
//	{
//		Target_A = 20;
//		Target_B = 50;
////		Turn_flag1 = 1;
//	}
//	
	else if(sensor[0]==0&&sensor[1]==0&&sensor[2]==1&&sensor[3]==0)
	{
		Target_A = 50;	
		Target_B = 42;
//		Turn_flag1 = 0;
		
	}
//	else if(sensor[0]==0&&sensor[1]==0&&sensor[2]==0&&sensor[3]==1)
//	{
//		Target_A = 88;
//		Target_B = 70;
//	}
	else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==0&&sensor[3]==0) 
	{
		Target_A = 42;
		Target_B = 50;
//		
//		Turn_flag1 = 1;
	}
	
	else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==0&&sensor[3]==0) 
	{
		Target_A = 50;
		Target_B = 42;
//		
//		Turn_flag1 = 1;
	}
	
	else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==0)
	{
		Target_A = 50;
		Target_B = 50;
//		Turn_flag1 = 0;
	}
	else if(count>=1845&&count<=1925)
	{
		Target_A = 15;
		Target_B = 50;
//		Turn_flag1 = 0;
	}
//	else if(sensor[0] == 1)
//	{
//		Count++;
//		if(Count == 7 || Count == 8)
//		{
//			Target_A = 15;
//			Target_B = 50;
//			
//		}
//		delay_ms(500);
//	}
//	else if(sensor[0]==0&&sensor[1]==1&&sensor[2]==1&&sensor[3]==0)
//	{
//		Target_A = 0;
//		Target_B = 0;
////		Turn_flag1 = 0;
//	}
//	else if(sensor[0]==0&&sensor[1]==0&&sensor[2]==0&&sensor[3]==0)
//	{
//		Target_A = 40;
//		Target_B = 88;
//	}
}
void Read_Turn_Sensor(void)
{
	if(sensor[0]==1&&sensor[1]==0&&sensor[2]==0&&sensor[3]==0) 
	{
		Target_A = 19;
		Target_B = 50;
//		Turn_flag1 = 1;
	}
}



