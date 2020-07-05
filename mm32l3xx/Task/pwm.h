#ifndef _PWN_H_
#define _PWN_H_

#include "stdint.h"
#include "HAL_tim.h"
#include "HAL_rcc.h"
#include "MM32l3xx.h"
#include "HAL_gpio.h"

extern uint8_t direct;
extern uint16_t pwm1;
extern uint16_t pwm2;
extern uint16_t pwm3;
extern uint16_t pwm4;
extern uint16_t speed_up;
extern uint16_t speed_down ;
void Pwm_Init(void);
void Pwm_Out(uint16_t pwm1,uint16_t pwm2,uint16_t pwm3,uint16_t pwm4);

#endif

