/**
 * @file main.c
 * @author �Ǻ��е�����
 * @date 2022-08-08
 * @copyright Copyright (c) 2022
 * KEY:P9.0 P8.2 P8.4 P8.5
 * ENCODER:CHA P4.4 CHB P4.5 CHC P5.0 CHD P5.1
 * OLED:D0 P6.0 D1 P4.3 CS P1.5 DC P6.1 RES P4.0
 * PWM: CHA P7.6 CHB P7.7 CHC P7.5 CHD P7.4
 */
/*��ϸ�ܽż�ͼ*/
#include "headfile.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "exti.h"
#include "motor.h"
extern int16 vin1,vin2;
int Encoder_L,Encoder_R;
/*����״̬����*/
uint8 Enocder=20;
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;
/*��һ�ο���״̬����*/
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;
/*���ر�־λ*/
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;
int encoder_L = 0;
int encoder_R = 0;
int Cezhong_flag = 0;
int mode_flag = 0;
int Send_flag = 0;
int Send_flag_copy = 0;
int main(void)
{
  CLOCK_Init();
//  uart_init(115200);
  uart3_init(115200);
  delay_init();
  /*������ʼ��*/
  KEY_Init();
  /*��������ʼ��*/
  EXTI_Init();
  /*OLED��ʼ��*/
  OLED_Init();
  OLED_Clear(0);
  UART_NVIC_Init();
  TimA1_Init(10000 - 1, 1);
  /*��ʱ���жϣ����ڴ������ݣ������жϷ���������ʹ��pid������*/
  TimA0_Init(5000 - 1, 48);
  MAP_Interrupt_enableMaster();
  /*�����ж����ȼ���ע���ж����ȼ���������Ϊһ�����������bug*/
  Interrupt_setPriority(INT_TA0_0, 1 << 5);
  Interrupt_setPriority(INT_TA2_0, 1 << 5);
  Interrupt_setPriority(INT_PORT4, 1 << 5);
  Interrupt_setPriority(INT_PORT5, 1 << 5);
  /*����жϱ�־λ*/
  GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN4);
  GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN5);
  GPIO_clearInterrupt(GPIO_PORT_P5, GPIO_PIN0);
  GPIO_clearInterrupt(GPIO_PORT_P5, GPIO_PIN1);
  /*PID��ʼ��*/
  Pid_L_Init(&pidLeft);
  Pid_R_Init(&pidRight);
  Pid_dir_Init(&pidDir);
	//led��ʼ��
	GPIO_setAsInputPin(GPIO_PORT_P4,GPIO_PIN1);
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN2);
  MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
	
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
	GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
	GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
	
	
  while (1)
  {
		
//				if(Send_flag == 0)
//			{
//				UART_send_short(UART3,0);
//			}
//			if(Send_flag == 1)
//			{
//				UART_send_short(UART3,1);
//			}
		
		
		if(GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN1) == 0)
		{
			do{
				
			}while(GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN1) == 0);
			Cezhong_flag++;
			if(Cezhong_flag == 2)
			{
					for(int i =0;i<10000;i++)
				{
					GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
					GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN2);
					GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
				}
					GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
					GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
					GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
//				  Send_flag = 1;
//				UART_send_short(UART3,1);
			}
			if(Cezhong_flag == 3)
			{
					for(int i =0;i<10000;i++)
				{
					GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
					GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN2);
					GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
				} 
					GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
					GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
					GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);
//					Send_flag = 0;UART_send_short(UART3,0);
			}
			
		}
		
	
    // UART_send_Byte(UART2, 0x0a);
    // GUI_ShowNum(30, 50, 1234567890, 10, 8, 1);
    // GUI_ShowCHinese(0, 30, 16, "ȫ�����Ӽ���", 1);
    // GUI_ShowString(45, 0, "16x16", 8, 1);
    // GUI_ShowString(0, 15, "6x8:ABCDEFGHIJKLMNOPQRSTUVWXYZ", 8, 1);
    // delay_ms(500);
    // OLED_Clear(0);
    /*���水��״̬*/
		printf("%d,%d\n",Encoder_L,Encoder_R);
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
    /*��ȡ��ǰ����״̬*/
    key1_status = KEY1;
    key2_status = KEY2;
    key3_status = KEY3;
    key4_status = KEY4;
    /*��⵽��������֮��  ���ſ���λ��־λ*/
    if (key1_status && !key1_last_status)
      key1_flag = 1;
    if (key2_status && !key2_last_status)
      key2_flag = 1;
    if (key3_status && !key3_last_status)
      key3_flag = 1;
    if (key4_status && !key4_last_status)
      key4_flag = 1;
    /*��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�*/
    if (key1_flag)
    {
      key1_flag = 0; //ʹ�ð���֮��Ӧ�������־λ
    }
    if (key2_flag)
    {
      key2_flag = 0; //ʹ�ð���֮��Ӧ�������־λ
    }
    if (key3_flag)
    {
      key3_flag = 0; //ʹ�ð���֮��Ӧ�������־λ
    }
    if (key4_flag)
    {
      key4_flag = 0; //ʹ�ð���֮��Ӧ�������־λ
    }
    delay_ms(20);
  }
}
