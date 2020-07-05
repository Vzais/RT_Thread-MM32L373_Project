#include "blue_uart2.h"
#include "stdio.h"
#include "pwm.h"
#include "led.h"
/**
******************************************************************************
* @file    uart_loop.c
* @author  AE Team
* @version V1.3.9
* @date    28/08/2019
* @brief   This file provides all the uart_loop firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/

//////////////////////////////////////////////////////////////////
/*#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

#endif

#ifdef USE_IAR
PUTCHAR_PROTOTYPE
{
    while((UART1->CSR & UART_IT_TXIEN) == 0); //循环发送,直到发送完毕
    UART1->TDR = (ch & (uint16_t)0x00FF);
    return ch;
}

#else
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
_sys_exit(int x)
{
    x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
    while((UART2->CSR & UART_IT_TXIEN) == 0); //循环发送,直到发送完毕
    UART2->TDR = (ch & (uint16_t)0x00FF);
    return ch;
}

#endif*/


/********************************************************************************************************
**函数信息 ：UartPortInit(UART_TypeDef* UARTx)
**功能描述 ：初始化串口
**输入参数 ：UART_TypeDef* UARTx ，选择UART1、UART2、UART3
**输出参数 ：无
********************************************************************************************************/
void UartPortInit(UART_TypeDef* UARTx)
{
    UART_InitTypeDef       UART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;

    if(UARTx == UART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
    }
    else if(UARTx == UART2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
    }
    else if(UARTx == UART3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE);
    }

    UART_InitStructure.UART_BaudRate =  115200; //波特率115200
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;//数据位
    UART_InitStructure.UART_StopBits = UART_StopBits_1;//停止位
    UART_InitStructure.UART_Parity = UART_Parity_No ;
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;//输入输出模式
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
    UART_Init(UARTx, &UART_InitStructure);
    UART_Cmd(UARTx, ENABLE);  //UART 模块使能

    if(UARTx == UART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;   //uart1_tx  pa9
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;  //uart1_rx  pa10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure);

    }

    if(UARTx == UART2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;   //uart1_tx  pa2
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;  //uart1_rx  pa3
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure);

    }

    if(UARTx == UART3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;   //uart3_tx  pc10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;  //uart3_rx  pc11
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOC, &GPIO_InitStructure);

    }

    //printf("请发送小于等于1个字节的数据！\r\n");

}

/********************************************************************************************************
**函数信息 ：uart_send(UART_TypeDef* UARTx,char c)
**功能描述 ：串口发送字节
**输入参数 ：UART_TypeDef* UARTx ，选择UART1、UART2、UART3
**输入参数 ：char c ,串口发送的字节
**输出参数 ：无
********************************************************************************************************/
void uart_send(UART_TypeDef* UARTx, char c)
{
    UART_SendData(UARTx, (uint16_t)c);

    while(1)
    {
        if(UART_GetITStatus(UARTx, UART_IT_TXIEN))

        {
            UART_ClearITPendingBit(UARTx, UART_IT_TXIEN);
            break;
        }

    }
}

/********************************************************************************************************
**函数信息 ：unsigned char inbyte(UART_TypeDef* UARTx)
**功能描述 ：串口接收函数
**输入参数 ：UART_TypeDef* UARTx ，选择UART1、UART2、UART3
**输出参数 ：unsigned char 串口接收返回的字节
********************************************************************************************************/
unsigned char inbyte(UART_TypeDef* UARTx)
{
    unsigned char temp;

    while(1)
    {
        if(UART_GetITStatus(UARTx, UART_IT_RXIEN))
        {
            UART_ClearITPendingBit(UARTx, UART_IT_RXIEN);  //清除接受中断位
            break;
        }
    }
    temp = (uint8_t)UART_ReceiveData(UARTx);
    if(temp == 0xd)
    {
        return 0;
    }
    return temp;
}


/********************************************************************************************************
**函数信息 ：void Uart1RxTest(UART_TypeDef* UARTx)
**功能描述 ：串口接收函数测试
**输入参数 ：UART_TypeDef* UARTx ，选择UART1、UART2、UART3
**输出参数 ：无
********************************************************************************************************/

void Uart1RxTest(UART_TypeDef* UARTx)
{
    unsigned char temp;

    temp = inbyte(UARTx);
    if(temp == 'H')             //左转
    {
        direct = 1;
    }
    else if(temp == 'J')        //右转
    {
        direct = 2; 
    }
    else if(temp == 'G')        //前进
    {
        direct = 3;  
    }
    else if(temp == 'K')        //后退
    {
        direct = 4;
    }
    else if(temp == 'E')        //加速
    {
        speed_up += 50;
        if(speed_up >= 899)
        {
            speed_up = 899;
        }
    }
    else if(temp == 'F')        //减速
    {
        speed_up -=50;
        if(speed_up <= 100)
        {
            speed_up = 100;
        }
    }
    else if(temp == 'I')        //停止
    {
        direct = 5; 
    }
    else if(temp == 'A')        //A水泵
    {
        WATER_PUMPA = !WATER_PUMPA;
    }
    else if(temp == 'B')        //B水泵
    {
        WATER_PUMPB = !WATER_PUMPB;
    }    
    else if(temp == 'C')        //C水泵
    {
        WATER_PUMPC = !WATER_PUMPC;
    }
    else if(temp == 'D')        //D水泵
    {
        WATER_PUMPD= !WATER_PUMPD;
    }
    if(direct == 1)
    {
        pwm1 = 899;
        pwm2 = speed_up;
        pwm3 = speed_up;
        pwm4 = 899;    
    }
    else if(direct == 2)
    {
        pwm1 = speed_up;
        pwm2 = 899;
        pwm3 = 899;
        pwm4 = speed_up;  
    }
    else if(direct == 3)
    {
        pwm1 = speed_up;
        pwm2 = 899;
        pwm3 = speed_up;
        pwm4 = 899;      
    }
    else if(direct == 4)
    {
        pwm1 = 899;
        pwm2 = speed_up;
        pwm3 = 899;
        pwm4 = speed_up;      
    }
    else //if(direct == 5)
    {
        pwm1 = 0;
        pwm2 = 0;
        pwm3 = 0;
        pwm4 = 0;                     
    }
        
    if(temp != 0)
    {
        uart_send(UARTx,temp);       //回显发送命令
    }
    temp = 0;
}


/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
