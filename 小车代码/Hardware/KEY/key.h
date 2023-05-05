#ifndef __KEY_H
#define __KEY_H

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

#define KEY1 GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN0)
#define KEY2 GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN5)
#define KEY3 GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN4)
#define KEY4 GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)

#define KEY1_PRES 1 // KEY0
#define KEY2_PRES 2 // KEY1
#define KEY3_PRES 3 // KEY0
#define KEY4_PRES 4 // KEY1

void KEY_Init(void); // IO初始化
// uint8_t KEY_Scan(uint8_t mode); //按键扫描函数
#endif
