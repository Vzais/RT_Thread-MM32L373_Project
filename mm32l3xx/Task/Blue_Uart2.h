#ifndef _BLUE_UART2_H_
#define _BLUE_UART2_H_

#include "HAL_device.h"
#include  <stdio.h>

void UartPortInit(UART_TypeDef* UARTx);
void Uart1RxTest(UART_TypeDef* UARTx);
void uart_send(UART_TypeDef* UARTx, char c);
#endif

