#include "key.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "HAL_device.h"
#include "led.h"

uint8_t mode_cnt = 0;

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOA,GPIOB,GPIOCʱ��

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PA0,K2��WK_UP��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA0
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_10 | GPIO_Pin_11; //PB10,PB11,K3,K4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó���������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10,11
}

uint8_t Key_Scan(uint8_t mode)
{
    static u8 key_up = 1; //�������ɿ���־
    if(mode)key_up = 1; //֧������
    if(key_up && (KEY1 == 1 || WK_UP == 0 || KEY3 == 0 || KEY4 == 0))
    {
        rt_thread_mdelay(10);//ȥ����
        key_up = 0;
        if(KEY1 == 1)return KEY1_PRES;
        else if(WK_UP == 0)return WKUP_PRES;
        else if(KEY3 == 0)return KEY3_PRES;
        else if(KEY4 == 0)return KEY4_PRES;
    }
    else if(KEY1 ==0 && KEY3 == 1 && KEY4 == 1 && WK_UP == 1)key_up = 1;
    return 0;// �ް�������
}

void Key_Task(void)
{
    mode_cnt = Key_Scan(0);		//�õ���ֵ
    switch(mode_cnt)
    {
        case KEY1_PRES://K1Ĭ�ϲ���PC13,Ĭ������reset��λ���������԰���K1�Ḵλ
            LED1 = !LED1;
            break;
        case WKUP_PRES:
            LED2 = !LED2;
            break;
        case KEY3_PRES:
            LED1 = !LED1;
            break;
        case KEY4_PRES:
            LED2 = !LED2;
            break;
        default:
            rt_thread_mdelay(100);
    }
}



