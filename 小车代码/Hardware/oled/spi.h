//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RCT6,����ԭ��MiniSTM32������,��Ƶ72MHZ������12MHZ
//QDtech-OLEDҺ������ for STM32
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/8/27
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
// OLEDģ��               STM32��Ƭ��
//   VCC         ��       DC 5V/3.3V      //OLED����Դ��
//   GND         ��          GND          //OLED����Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������Ϊ4����SPI
// OLEDģ��               STM32��Ƭ��
//   D1          ��          PB15        //OLED��SPIд�ź�
//=======================================Һ���������߽���==========================================//
// OLEDģ��               STM32��Ƭ��
//   CS          ��          PB11        //OLED��Ƭѡ�����ź�
//   RES         ��          PB12        //OLED����λ�����ź�
//   DC          ��          PB10        //OLED������/����ѡ������ź�
//   D0          ��          PB13        //OLED��SPIʱ���ź�
//=========================================����������=========================================//
//��ģ�鲻���������ܣ����Բ���Ҫ����������
****************************************************************************************************/	
/***************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
****************************************************************************************************/
#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

//�����Գ���ʹ�õ������ģ��SPI�ӿ�����
//SPI���������Ŷ����ʱ�����Ŷ��嶼���������޸�
//�޸����Ŷ������Ҫ��Ӧ�޸�oled.c��OLED_Init_GPIO�����������ų�ʼ��

//--------------SPI�������Ŷ���-----------------------
#define OLED_MOSI      GPIO_PIN3  //OLED��SPIд�����ź�4.3
#define OLED_CLK       GPIO_PIN0 //OLED��SPIʱ���ź�6.0


//--------------SPI�˿ڲ�������---------------------
#define	OLED_MOSI_SET()  	GPIO_setOutputHighOnPin(GPIO_PORT_P4,OLED_MOSI)
#define	OLED_MOSI_CLR()  	GPIO_setOutputLowOnPin(GPIO_PORT_P4,OLED_MOSI)

#define	OLED_CLK_SET()  	GPIO_setOutputHighOnPin(GPIO_PORT_P6,OLED_CLK ) 
#define	OLED_CLK_CLR()  	GPIO_setOutputLowOnPin(GPIO_PORT_P6,OLED_CLK )   

//SPIд���ݺ���
void SPI_WriteByte(uint8_t Data);
#endif
