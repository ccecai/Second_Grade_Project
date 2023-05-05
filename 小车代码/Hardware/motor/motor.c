#include "motor.h"
/*PWM限幅*/
#define PWMMAX 10000
/*速度环PID初始化*/

float velocity_KP = 274;
float velocity_KI = 1.37;

void Pid_L_Init(PID *inPID)
{
    inPID->kp = 500;
    inPID->ki = 2.5;
    inPID->kd = 2500;
    inPID->setPoint = 0;
    inPID->maximum = 5000;
    inPID->minimum = -5000;
    inPID->lastError = 0;
    inPID->preError = 0;
    inPID->deadBand = 0;
    inPID->result = 0;
}
void Pid_R_Init(PID *inPID)
{
    inPID->kp = 500;
    inPID->ki = 2.5;
    inPID->kd = 2500;
    inPID->setPoint = 0;
    inPID->maximum = 5000;
    inPID->minimum = -5000;
    inPID->lastError = 0;
    inPID->preError = 0;
    inPID->deadBand = 0;
    inPID->result = 0;
}

void Pid_dir_Init(PID *inPID)
{
    inPID->kp = 40;
    inPID->ki = 0;
    inPID->kd = 0;
    inPID->setPoint = 0;
    inPID->maximum = 5000;
    inPID->minimum = -5000;
    inPID->lastError = 0;
    inPID->preError = 0;
    inPID->deadBand = 0;
    inPID->result = 0;
}

void Pid_slow_Init(PID *inPID)
{
    inPID->kp = 8;
    inPID->ki = 0.001;
    inPID->kd = 1;
    inPID->setPoint = 200;
    inPID->maximum = 5000;
    inPID->minimum = -5000;
    inPID->lastError = 0;
    inPID->preError = 0;
    inPID->deadBand = 0;
    inPID->result = 0;
}
/*速度环PID*/
float PID_Calculate(PID *inPID, float processValue)
{
    float thisError;
    float increment;
    float pError, dError, iError;

    thisError = inPID->setPoint - processValue; //得到偏差值
    pError = thisError - inPID->lastError;
    iError = 0;
    dError = thisError - 2 * (inPID->lastError) + inPID->preError;

    if (inPID->result > inPID->maximum)
    {
        if (thisError <= 0)
        {
            iError = thisError;
        }
    }
    else if (inPID->result < inPID->minimum)
    {
        if (thisError >= 0)
        {
            iError = thisError;
        }
    }
    else
    {
        iError = thisError;
    }

    increment = inPID->kp * pError + inPID->ki * iError + inPID->kd * dError; //增量计算

    inPID->preError = inPID->lastError; //存放偏差用于下次运算
    inPID->lastError = thisError;
    inPID->result += increment;

    return inPID->result;
}

/*限幅函数*/
int32 Xian_Fu(int32 shuJu, int32 low, int32 high)
{
    if (shuJu >= 0)
    {
        if (shuJu > high)
            return high;
        else
            return shuJu;
    }
    else
    {
        if (shuJu < low)
            return low;
        else
            return shuJu;
    }
}

void motor1_forward(uint16 duty)
{
    pwm_duty(2, duty);
    pwm_duty(4, 0);
}
void motor1_back(uint16 duty)
{
    pwm_duty(2, 0);
    pwm_duty(4, duty);
}
void motor2_forward(uint16 duty)
{
    pwm_duty(3, duty);
    pwm_duty(1, 0);
}
void motor2_back(uint16 duty)
{
    pwm_duty(3, 0);
    pwm_duty(1, duty);
}

void Motor_Control(int16 motor1, int16 motor2)
{
    motor1 = Xian_Fu(motor1, -PWMMAX + 100, PWMMAX - 100);
    motor2 = Xian_Fu(motor2, -PWMMAX + 100, PWMMAX - 100);
    if (motor1 >= 0) //正转
    {
        motor1_forward(motor1);
    }
    else if (motor1 < 0)
    {
        motor1_back(-motor1);
    }
    if (motor2 >= 0) //正转
    {
        motor2_forward(motor2);
    }
    else if (motor2 < 0)
    {
        motor2_back(-motor2);
    }
}

void pwm_duty(uint8_t tim_x, uint16_t ccr)
{
    switch (tim_x)
    {
    case 1:
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, ccr);
        break;
    case 2:
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, ccr);
        break;
    case 3:
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, ccr);
        break;
    case 4:
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, ccr);
        break;
    default:
        break;
    }
}

int PID_calculate(PID *pid, int Encoder)
{
    static float Bias, Pwm, Integral_bias, Last_Bias;
    Bias = Encoder - pid->setPoint;                                                //计算偏差
    Integral_bias += Bias;                                                         //求出偏差的积分
    Pwm = pid->kp * Bias + pid->ki * Integral_bias + pid->kd * (Bias - Last_Bias); //位置式PID控制器
    Last_Bias = Bias;                                                              //保存上一次偏差
    return Pwm;                                 	//增量输出  
	
	
}


int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
