#ifndef _KEY_H_
#define _KEY_H_

#include "HAL_gpio.h"
#include "HAL_rcc.h"
#include "stdint.h"


#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��ȡ����1
#define WK_UP GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//��ȡ����2 
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//��ȡ����3
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//��ȡ����4

#define KEY1_PRES	1		//KEY1 
#define WKUP_PRES	2		//WK_UP  
#define KEY3_PRES	3		//KEY3 
#define KEY4_PRES	4		//KEY4 

void Key_Init(void);
uint8_t Key_Scan(uint8_t mode);
void Key_Task(void);
#endif





