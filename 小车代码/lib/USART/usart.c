#include "usart.h"
#include "baudrate_calculate.h"
/*****************   函数说明   *****************
 *
 * 以上两条对接标准输入输出库的函数:
 * int fputc(int ch, FILE *f);
 * int fgetc(FILE *f);
 * 源码为BiliBili平台UP主 “CloudBoyStudio” 编写
 * 在此也表感谢
 * 使用时记得勾选魔术棒里的Use MicroLIB
 *
 *****************   说明结束   *****************/
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
 *Description:初始化串口
 *Input:输入参数为波特率
 *Output:无
 *Return:无
 *Others:
 * ①低频时钟频率下，高波特率使得传输时误差过大,
 * 比如35768Hz下19200波特率,
 * 会使得传输出错，这时可以尝试降低波特率。
 * ②baudrate_calculate的问题请去文件内查看。
 *****************************************************************/
void uart3_init(uint32_t baudRate)
{
#ifdef EUSCI_A_UART_7_BIT_LEN
    //固件库v3_40_01_02
    //默认SMCLK 48MHz 比特率 115200
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
    eusci_calcBaudDividers((eUSCI_UART_ConfigV1 *)&uartConfig, baudRate); //配置波特率
#else
    //固件库v3_21_00_05
    //默认SMCLK 48MHz 比特率 115200
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
    eusci_calcBaudDividers((eUSCI_UART_Config *)&uartConfig, baudRate); //配置波特率
#endif
    // GPIO复用
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P9, GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    //初始化串口
    MAP_UART_initModule(EUSCI_A3_BASE, &uartConfig);
    //开启串口
    MAP_UART_enableModule(EUSCI_A3_BASE);
}
void uart_init(uint32_t baudRate)
{
#ifdef EUSCI_A_UART_7_BIT_LEN
    //固件库v3_40_01_02
    //默认SMCLK 48MHz 比特率 115200
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
    eusci_calcBaudDividers((eUSCI_UART_ConfigV1 *)&uartConfig, baudRate); //配置波特率
#else
    //固件库v3_21_00_05
    //默认SMCLK 48MHz 比特率 115200
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
    eusci_calcBaudDividers((eUSCI_UART_Config *)&uartConfig, baudRate); //配置波特率
#endif
    // GPIO复用
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    //初始化串口
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);
    MAP_UART_initModule(EUSCI_A1_BASE, &uartConfig);
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);

    //开启串口
    MAP_UART_enableModule(EUSCI_A0_BASE);
    MAP_UART_enableModule(EUSCI_A1_BASE);
    MAP_UART_enableModule(EUSCI_A2_BASE);
}
/*****************************************************************
 *Function:UART_NVIC_Init(void)
 *Description:初始化串口中断
 *Input:无
 *Output:无
 *Return:无
 *Others:未开启总中断，需自己开启
 *Data:2021/09/15
 *Author:星海中的绿洲
 *****************************************************************/
void UART_NVIC_Init(void)
{
    /*开启串口相关中断*/
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    /*开启串口端口中断*/
    Interrupt_enableInterrupt(INT_EUSCIA0);
    /*开启串口相关中断*/
    UART_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    /*开启串口端口中断*/
    Interrupt_enableInterrupt(INT_EUSCIA1);
    /*开启串口相关中断*/
    UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    /*开启串口端口中断*/
    Interrupt_enableInterrupt(INT_EUSCIA2);
    /*开启串口相关中断*/
    UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    /*开启串口端口中断*/
    Interrupt_enableInterrupt(INT_EUSCIA3);
}
/*************************************************
 * 函  数  名:UART_send_Byte
 * 功       能:发送一个字节数据
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          Data:要发送的8位数据
 * 注意事项:无
 *************************************************/
void UART_send_Byte(UART_CHA_enum UART_CHA, uint8 Data)
{
    switch (UART_CHA)
    {
    case (UART0):
        while (!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG))
            ; //等待上一次发送完成
        EUSCI_A0->TXBUF = Data;
        break;
    case (UART1):
        while (!(EUSCI_A1->IFG & EUSCI_A_IFG_TXIFG))
            ; //等待上一次发送完成
        EUSCI_A1->TXBUF = Data;
        break;
    case (UART2):
        while (!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG))
            ; //等待上一次发送完成
        EUSCI_A2->TXBUF = Data;
        break;
    case (UART3):
        while (!(EUSCI_A3->IFG & EUSCI_A_IFG_TXIFG))
            ; //等待上一次发送完成
        EUSCI_A3->TXBUF = Data;
        break;
    default:;
    }
}
/*************************************************
 * 函  数  名:UART_recv_Byte
 * 功       能:接收一个字节数据
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 * 注意事项:无
 *************************************************/
uint8 UART_recv_Byte(UART_CHA_enum UART_CHA)
{
    uint8 result;
    switch (UART_CHA)
    {
    case (UART0):
        result = EUSCI_A0->RXBUF;
        break; //取出缓冲区数据
    case (UART1):
        result = EUSCI_A1->RXBUF;
        break; //取出缓冲区数据
    case (UART2):
        result = EUSCI_A2->RXBUF;
        break; //取出缓冲区数据
    case (UART3):
        result = EUSCI_A3->RXBUF;
        break; //取出缓冲区数据
    default:;
    }
    return result;
}
/*************************************************
 * 函  数  名:UART_send_string
 * 功       能:发送一个字符串
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          txt:所要发送的字符串
 * 注意事项:无
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
 * 函  数  名:UART_send_short
 * 功       能:发送一个16位整型
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          num:所要发送的16位整型变量
 * 注意事项:从高位开始发送
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
 * 函  数  名:UART_send_int
 * 功       能:发送一个32位整型
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          num:所要发送的32位整型变量
 * 注意事项:从高位开始发送
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

