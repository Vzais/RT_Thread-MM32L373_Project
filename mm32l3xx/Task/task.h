#ifndef _TASK_H_
#define _TASK_H_

#include "pwm.h"
#include "led.h"
#include "blue_uart2.h"
#include "key.h"
#include <rtthread.h>

void KEY_Task_Init(void);
void KEY_Task_Entry(void *parameter);
void Blue_Task_Init(void);
void Blue_Task_Entry(void *parameter);
void PWN_Task_Init(void);
void PWM_Task_Entry(void *parameter);
#endif

