/*
  本文件用来创建多个实时运行的任务
  
*/

#include "task.h"

/*KEY*/ 
#define THREAD_KEY_PRIORITY   8
#define THREAD_KEY_STACK_SIZE 1024
#define THREAD_KEY_TIMESLICE  5

/*Blue*/  
#define THREAD_BLUE_PRIORITY   9
#define THREAD_BLUE_STACK_SIZE 1024
#define THREAD_BLUE_TIMESLICE  5

/*PWM*/ 
#define THREAD_PWM_PRIORITY   10
#define THREAD_PWM_STACK_SIZE 1024
#define THREAD_PWM_TIMESLICE  5

void KEY_Task_Init(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("KEY",
							 KEY_Task_Entry, RT_NULL,
							 THREAD_KEY_STACK_SIZE,
							 THREAD_KEY_PRIORITY,
							 THREAD_KEY_TIMESLICE);
	if(tid != RT_NULL)
	{
	   rt_thread_startup(tid); 	
	}
}

void KEY_Task_Entry(void *parameter)
{
    Key_Init();
    while(1)
    {
        Key_Task();   
    }
}
void Blue_Task_Init(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("BLUE",
							 Blue_Task_Entry, RT_NULL,
							 THREAD_BLUE_STACK_SIZE,
							 THREAD_BLUE_PRIORITY,
							 THREAD_BLUE_TIMESLICE);
	if(tid != RT_NULL)
	{
	   rt_thread_startup(tid); 	
	}
}

void Blue_Task_Entry(void *parameter)
{
    LED_Init();
    UartPortInit(UART2);
    while(1)
    {
        Uart1RxTest(UART2);     
        rt_thread_mdelay(50); 
    }
}

void PWN_Task_Init(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("PWM",
							 PWM_Task_Entry, RT_NULL,
							 THREAD_PWM_STACK_SIZE,
							 THREAD_PWM_PRIORITY,
							 THREAD_PWM_TIMESLICE);
	if(tid != RT_NULL)
	{
	   rt_thread_startup(tid); 	
	}
}

void PWM_Task_Entry(void *parameter)
{
    Pwm_Init();
    while(1)
    {
        Pwm_Out(pwm1,pwm2,pwm3,pwm4);   
        rt_thread_mdelay(100);        
    }
}


