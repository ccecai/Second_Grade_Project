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
} UART_CHA_enum; //串口可选通道枚举
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int16_t int16;
typedef int32_t int32;
typedef struct
{
    float setPoint;  //设定值
    float kp;        //比例系数proportiongain
    float ki;        //积分系数integralgain
    float kd;        //微分系数derivativegain
    float lastError; //前一拍偏差
    float preError;  //前两拍偏差
    float deadBand;  //死区
    float result;    //输出值
    float maximum;   //最大值
    float minimum;   //最小值
} PID;
extern int encoder_L;
extern int encoder_R;
extern PID pidLeft, pidRight, pidDir;
#endif
