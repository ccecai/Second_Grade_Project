#ifndef __MOTOR_H
#define __MOTOR_H
#include "headfile.h"

void Pid_L_Init(PID *inPID);
void Pid_R_Init(PID *inPID);
float PID_Calculate(PID *inPID, float processValue);
void pwm_duty(uint8_t tim_x, uint16_t ccr);
int32 Xian_Fu(int32 shuJu, int32 low, int32 high);
void motor1_forward(uint16 duty);
void motor1_back(uint16 duty);
void motor2_forward(uint16 duty);
void motor2_back(uint16 duty);
void Motor_Control(int16 motor1, int16 motor2);
void Pid_dir_Init(PID *inPID);
int PID_calculate(PID *pid, int Encoder);
void Pid_slow_Init(PID *inPID);
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
#endif
