#ifndef __HEADFILE_H
#define __HEADFILE_H

#include "key.h"
#include "gpio.h"
#include <driverlib.h>
#include "delay.h"
#include "clock.h"
#include <stdint.h>
#include <stdbool.h>
#include "oled.h"
typedef enum
{
    UART0,
    UART1,
    UART2,
    UART3
} UART_CHA_enum; //���ڿ�ѡͨ��ö��
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int16_t int16;
typedef int32_t int32;
typedef struct
{
    float setPoint;  //�趨ֵ
    float kp;        //����ϵ��proportiongain
    float ki;        //����ϵ��integralgain
    float kd;        //΢��ϵ��derivativegain
    float lastError; //ǰһ��ƫ��
    float preError;  //ǰ����ƫ��
    float deadBand;  //����
    float result;    //���ֵ
    float maximum;   //���ֵ
    float minimum;   //��Сֵ
} PID;
extern int encoder_L;
extern int encoder_R;
extern PID pidLeft, pidRight, pidDir;
#endif
