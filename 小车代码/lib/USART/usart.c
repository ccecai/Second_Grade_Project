#include "usart.h"
#include "baudrate_calculate.h"
/*****************   ����˵��   *****************
 *
 * ���������Խӱ�׼���������ĺ���:
 * int fputc(int ch, FILE *f);
 * int fgetc(FILE *f);
 * Դ��ΪBiliBiliƽ̨UP�� ��CloudBoyStudio�� ��д
 * �ڴ�Ҳ���л
 * ʹ��ʱ�ǵù�ѡħ�������Use MicroLIB
 *
 *****************   ˵������   *****************/
int fputc(int ch, FILE *f)
{
    UART_transmitData(EUSCI_A0_BASE, ch & 0xFF);
    return ch;
}

int fgetc(FILE *f)
{
    while (EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG !=
           UART_getInterruptStatus(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG))
        ;
    return UART_receiveData(EUSCI_A0_BASE);
}

/*****************************************************************
 *Function:uart_init(uint32_t baudRate)
 *Description:��ʼ������
 *Input:�������Ϊ������
 *Output:��
 *Return:��
 *Others:
 * �ٵ�Ƶʱ��Ƶ���£��߲�����ʹ�ô���ʱ������,
 * ����35768Hz��19200������,
 * ��ʹ�ô��������ʱ���Գ��Խ��Ͳ����ʡ�
 * ��baudrate_calculate��������ȥ�ļ��ڲ鿴��
 *****************************************************************/
void uart3_init(uint32_t baudRate)
{
#ifdef EUSCI_A_UART_7_BIT_LEN
    //�̼���v3_40_01_02
    //Ĭ��SMCLK 48MHz ������ 115200
    const eUSCI_UART_ConfigV1 uartConfig =
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
            26,                                            // BRDIV = 26
            0,                                             // UCxBRF = 0
            111,                                           // UCxBRS = 111
            EUSCI_A_UART_NO_PARITY,                        // No Parity
            EUSCI_A_UART_LSB_FIRST,                        // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
            EUSCI_A_UART_MODE,                             // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
            EUSCI_A_UART_8_BIT_LEN                         // 8 bit data length
        };
    eusci_calcBaudDividers((eUSCI_UART_ConfigV1 *)&uartConfig, baudRate); //���ò�����
#else
    //�̼���v3_21_00_05
    //Ĭ��SMCLK 48MHz ������ 115200
    const eUSCI_UART_Config uartConfig =
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
            26,                                            // BRDIV = 26
            0,                                             // UCxBRF = 0
            111,                                           // UCxBRS = 111
            EUSCI_A_UART_NO_PARITY,                        // No Parity
            EUSCI_A_UART_LSB_FIRST,                        // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
            EUSCI_A_UART_MODE,                             // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
        };
    eusci_calcBaudDividers((eUSCI_UART_Config *)&uartConfig, baudRate); //���ò�����
#endif
    // GPIO����
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P9, GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    //��ʼ������
    MAP_UART_initModule(EUSCI_A3_BASE, &uartConfig);
    //��������
    MAP_UART_enableModule(EUSCI_A3_BASE);
}
void uart_init(uint32_t baudRate)
{
#ifdef EUSCI_A_UART_7_BIT_LEN
    //�̼���v3_40_01_02
    //Ĭ��SMCLK 48MHz ������ 115200
    const eUSCI_UART_ConfigV1 uartConfig =
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
            26,                                            // BRDIV = 26
            0,                                             // UCxBRF = 0
            111,                                           // UCxBRS = 111
            EUSCI_A_UART_NO_PARITY,                        // No Parity
            EUSCI_A_UART_LSB_FIRST,                        // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
            EUSCI_A_UART_MODE,                             // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
            EUSCI_A_UART_8_BIT_LEN                         // 8 bit data length
        };
    eusci_calcBaudDividers((eUSCI_UART_ConfigV1 *)&uartConfig, baudRate); //���ò�����
#else
    //�̼���v3_21_00_05
    //Ĭ��SMCLK 48MHz ������ 115200
    const eUSCI_UART_Config uartConfig =
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
            26,                                            // BRDIV = 26
            0,                                             // UCxBRF = 0
            111,                                           // UCxBRS = 111
            EUSCI_A_UART_NO_PARITY,                        // No Parity
            EUSCI_A_UART_LSB_FIRST,                        // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
            EUSCI_A_UART_MODE,                             // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
        };
    eusci_calcBaudDividers((eUSCI_UART_Config *)&uartConfig, baudRate); //���ò�����
#endif
    // GPIO����
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    //��ʼ������
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);
    MAP_UART_initModule(EUSCI_A1_BASE, &uartConfig);
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);

    //��������
    MAP_UART_enableModule(EUSCI_A0_BASE);
    MAP_UART_enableModule(EUSCI_A1_BASE);
    MAP_UART_enableModule(EUSCI_A2_BASE);
}
/*****************************************************************
 *Function:UART_NVIC_Init(void)
 *Description:��ʼ�������ж�
 *Input:��
 *Output:��
 *Return:��
 *Others:δ�������жϣ����Լ�����
 *Data:2021/09/15
 *Author:�Ǻ��е�����
 *****************************************************************/
void UART_NVIC_Init(void)
{
    /*������������ж�*/
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    /*�������ڶ˿��ж�*/
    Interrupt_enableInterrupt(INT_EUSCIA0);
    /*������������ж�*/
    UART_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    /*�������ڶ˿��ж�*/
    Interrupt_enableInterrupt(INT_EUSCIA1);
    /*������������ж�*/
    UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    /*�������ڶ˿��ж�*/
    Interrupt_enableInterrupt(INT_EUSCIA2);
    /*������������ж�*/
    UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    /*�������ڶ˿��ж�*/
    Interrupt_enableInterrupt(INT_EUSCIA3);
}
/*************************************************
 * ��  ��  ��:UART_send_Byte
 * ��       ��:����һ���ֽ�����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          Data:Ҫ���͵�8λ����
 * ע������:��
 *************************************************/
void UART_send_Byte(UART_CHA_enum UART_CHA, uint8 Data)
{
    switch (UART_CHA)
    {
    case (UART0):
        while (!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG))
            ; //�ȴ���һ�η������
        EUSCI_A0->TXBUF = Data;
        break;
    case (UART1):
        while (!(EUSCI_A1->IFG & EUSCI_A_IFG_TXIFG))
            ; //�ȴ���һ�η������
        EUSCI_A1->TXBUF = Data;
        break;
    case (UART2):
        while (!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG))
            ; //�ȴ���һ�η������
        EUSCI_A2->TXBUF = Data;
        break;
    case (UART3):
        while (!(EUSCI_A3->IFG & EUSCI_A_IFG_TXIFG))
            ; //�ȴ���һ�η������
        EUSCI_A3->TXBUF = Data;
        break;
    default:;
    }
}
/*************************************************
 * ��  ��  ��:UART_recv_Byte
 * ��       ��:����һ���ֽ�����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 * ע������:��
 *************************************************/
uint8 UART_recv_Byte(UART_CHA_enum UART_CHA)
{
    uint8 result;
    switch (UART_CHA)
    {
    case (UART0):
        result = EUSCI_A0->RXBUF;
        break; //ȡ������������
    case (UART1):
        result = EUSCI_A1->RXBUF;
        break; //ȡ������������
    case (UART2):
        result = EUSCI_A2->RXBUF;
        break; //ȡ������������
    case (UART3):
        result = EUSCI_A3->RXBUF;
        break; //ȡ������������
    default:;
    }
    return result;
}
/*************************************************
 * ��  ��  ��:UART_send_string
 * ��       ��:����һ���ַ���
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          txt:��Ҫ���͵��ַ���
 * ע������:��
 *************************************************/
void UART_send_string(UART_CHA_enum UART_CHA, char *txt)
{
    int i;
    for (i = 0; txt[i]; i++)
    {
        UART_send_Byte(UART_CHA, txt[i]);
    }
}
/*************************************************
 * ��  ��  ��:UART_send_short
 * ��       ��:����һ��16λ����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          num:��Ҫ���͵�16λ���ͱ���
 * ע������:�Ӹ�λ��ʼ����
 *************************************************/
void UART_send_short(UART_CHA_enum UART_CHA, uint16 num)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        UART_send_Byte(UART_CHA, (num & 0xff00) >> 8);
        num = num << 8;
    }
}
/*************************************************
 * ��  ��  ��:UART_send_int
 * ��       ��:����һ��32λ����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          num:��Ҫ���͵�32λ���ͱ���
 * ע������:�Ӹ�λ��ʼ����
 *************************************************/
void UART_send_int(UART_CHA_enum UART_CHA, uint32 num)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        UART_send_Byte(UART_CHA, (num & 0xff000000) >> 24);
        num = num << 8;
    }
}

