#include "motor.h"
/*PWM�޷�*/
#define PWMMAX 10000
/*�ٶȻ�PID��ʼ��*/

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
/*�ٶȻ�PID*/
float PID_Calculate(PID *inPID, float processValue)
{
    float thisError;
    float increment;
    float pError, dError, iError;

    thisError = inPID->setPoint - processValue; //�õ�ƫ��ֵ
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

    increment = inPID->kp * pError + inPID->ki * iError + inPID->kd * dError; //��������

    inPID->preError = inPID->lastError; //���ƫ�������´�����
    inPID->lastError = thisError;
    inPID->result += increment;

    return inPID->result;
}

/*�޷�����*/
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
    if (motor1 >= 0) //��ת
    {
        motor1_forward(motor1);
    }
    else if (motor1 < 0)
    {
        motor1_back(-motor1);
    }
    if (motor2 >= 0) //��ת
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
    Bias = Encoder - pid->setPoint;                                                //����ƫ��
    Integral_bias += Bias;                                                         //���ƫ��Ļ���
    Pwm = pid->kp * Bias + pid->ki * Integral_bias + pid->kd * (Bias - Last_Bias); //λ��ʽPID������
    Last_Bias = Bias;                                                              //������һ��ƫ��
    return Pwm;                                 	//�������  
	
	
}


int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
