
#include "isr.h"
#include "usart.h"
#include "headfile.h"
#include "motor.h"
PID pidLeft, pidRight, pidDir;
/*vc:x方向速度 vw:角速度*/
float vc = 20, vw = 420;
extern int Encoder_L,Encoder_R,Cezhong_flag ,Send_flag;
int16 v1, v2, vin1, vin2;
void TA0_0_IRQHandler(void)
{
    static int i = 0;
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    i++;
		/*方向环计算*/
//		pidDir.setPoint=0;
//    vw = PID_calculate(&pidDir, offset);
    Xian_Fu(vw, -10000 + 100, 10000 - 100);
		/*速度环周期慢于方向环*/
//    if (i == 3)
//    {
        /*逆运动学解算PID驱动*/
        pidLeft.setPoint = vc;
        pidRight.setPoint = vc;
				encoder_R = -encoder_R;
//				encoder_L = -encoder_L;
				Encoder_L = encoder_L;
				Encoder_R = encoder_R;
        v1 = PID_Calculate(&pidLeft, encoder_L);
        v2 = PID_Calculate(&pidRight, encoder_R);
				/*并级PID*/
        vin1 = v1+vw-i*0.12;
        vin2 = v2;
//				if(i==210)
//				{
//					Send_flag = 1;
//				}
				if(i >= 210&& i <= 1710)
				{
						UART_send_short(UART3,1);
						pwm_duty(2, 0);
						pwm_duty(3, 0);
				}
				
				else if(Cezhong_flag < 4){
					Motor_Control((int16)(vin1), (int16)(vin2));
		
				}
        if(Cezhong_flag == 4)
				{
					pwm_duty(2, 0);
					pwm_duty(3, 0);
					
				}
				
        encoder_L = 0;
        encoder_R = 0;
//        i = 0;
//    }
}
void TA1_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
}
void TA2_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
}
void PORT1_IRQHandler(void)
{
    uint16_t flag;
    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P1, flag);
}
void PORT2_IRQHandler(void)
{
    uint16_t flag;
    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P2, flag);
}
void PORT3_IRQHandler(void)
{
    uint16_t flag;
    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P3, flag);
}

void PORT4_IRQHandler(void)
{
    uint16_t flag;

    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P4, flag);

    /*左轮编码器线A*/
    if (flag & GPIO_PIN4)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN5) == 0)
            encoder_L++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN5) == 1)
            encoder_L--;
    }

    /*左轮编码器线B*/
    if (flag & GPIO_PIN5)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN4) == 0)
            encoder_L--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN4) == 1)
            encoder_L++;
    }
}

void PORT5_IRQHandler(void)
{
    uint16_t flag;

    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P5, flag);

    /*右轮编码器线A*/
    if (flag & GPIO_PIN0)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0)
            encoder_R++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 1)
            encoder_R--;
    }

    /*右轮编码器线B*/
    if (flag & GPIO_PIN1)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN0) == 0)
            encoder_R--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN0) == 1)
            encoder_R++;
    }
}

void EUSCIA0_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) //接收中断
    {
        /***********************以下添加用户的处理函数*********************/
        /***********************用户处理函数添加结束行*********************/
    }
}

void EUSCIA1_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A1_BASE);
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************用户处理函数添加结束行*********************/
    }
}

void EUSCIA2_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) //接收中断
    {
        /***********************用户处理函数添加结束行*********************/
    }
}

void EUSCIA3_IRQHandler()
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A3_BASE);
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) //接收中断
    {
        /***********************以下添加用户的处理函数*********************/
       
        /***********************用户处理函数添加结束行*********************/
    }
}
