#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
/**************************************************************************
 ��  �� ���������
 �Ա���ַ��https://shop119207236.taobao.com
 ΢�Ź��ںš���������ˡ�
 ��̨�ظ���ƽ��С��������ȡƽ��С��ȫ��DIY����
 ��̨�ظ������ӿ������ߡ�����ȡ���ӹ���ʦ�ر���������
 ��̨�ظ�������������ϡ�����ȡ����������ϰ�
 ֪���������� 
**************************************************************************/
#define PI 3.14159265
void EXTI9_5_IRQHandler(void);
int balance_UP(float Angle,float Mechanical_balance,float Gyro);
int velocity(void);
int turn(void);
void Kinematic_Analysis(int velocity,int turn);
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
#endif
