#ifndef __USRAT3_H
#define __USRAT3_H 
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

void uart2_init(u32 bound);
void USART2_IRQHandler(void);

void uart3_init(u32 bound);
void USART3_IRQHandler(void);
void BluetoothCMD(u8 Uart_Receive);
#endif

