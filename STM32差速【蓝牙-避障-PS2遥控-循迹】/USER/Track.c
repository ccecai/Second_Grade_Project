#include "stm32f10x.h"                  // Device header

u8 sensor[4];

extern int Target_A,Target_B;

void Read_Sensor(void)
{
				sensor[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
				sensor[1]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
				sensor[2]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
				sensor[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	if(sensor[0]==0&&sensor[1]==1&&sensor[2]==1&&sensor[3]==0)
	{
		Target_A = 70;
		Target_B = 70;
	}
	else if(sensor[0]==1&&sensor[1]==0&&sensor[2]==0&&sensor[3]==0)
	{
		Target_A = 15;
		Target_B = 70;
	}
	else if(sensor[0]==0&&sensor[1]==0&&sensor[2]==0&&sensor[3]==1)
	{
		Target_A = 70;
		Target_B = 15;
	}
	else if(sensor[0]==0&&sensor[1]==1&&sensor[2]==0&&sensor[3]==0)
	{
		Target_A = 70;
		Target_B = 70;
	}
	else if(sensor[0]==0&&sensor[1]==0&&sensor[2]==1&&sensor[3]==0)
	{
		Target_A = 70;
		Target_B = 70;
	}
}
