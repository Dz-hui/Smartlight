/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-07 15:16:10
*@FilePath: \大创\DEMO\Hardware\PWM.h
*@Drscription: 
***********************************************************************/
#ifndef __PWM__H
#define __PWM__H

#include "main.h"

/*开时钟宏定义*/
#define GPIOB_CLK_ENABLE()      RCC_APB2PeriphClockCmd(LED_PIN_CLOCK,ENABLE)
#define TIM3_CLK_ENABLE()       RCC_APB1PeriphClockCmd(PWM_TIM_CLOCK,ENABLE)

/*宏定义*/
#define LED_PIN_CLOCK           RCC_APB2Periph_GPIOB
#define PWM_TIM_CLOCK           RCC_APB2Periph_TIM1

#define LED_B_PIN               GPIO_Pin_15
#define LED_B_S_PIN             GPIO_PinSource15
#define LED_B_PORT              GPIOB

#define PWM_TIM                 TIM1

/*函数*/
void LED_GPIO_Config(void);
void BASE_TIM_Config (void);
void TIM_OC_Config(void);
void PWM_TIMx_Config(void);


#endif 
