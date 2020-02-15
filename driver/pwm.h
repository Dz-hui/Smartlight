/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-07 15:16:10
*@FilePath: \��\DEMO\Hardware\PWM.h
*@Drscription: 
***********************************************************************/
#ifndef __PWM__H
#define __PWM__H

#include "main.h"

/*��ʱ�Ӻ궨��*/
#define GPIOB_CLK_ENABLE()      RCC_APB2PeriphClockCmd(LED_PIN_CLOCK,ENABLE)
#define TIM3_CLK_ENABLE()       RCC_APB1PeriphClockCmd(PWM_TIM_CLOCK,ENABLE)

/*�궨��*/
#define LED_PIN_CLOCK           RCC_APB2Periph_GPIOB
#define PWM_TIM_CLOCK           RCC_APB2Periph_TIM1

#define LED_B_PIN               GPIO_Pin_15
#define LED_B_S_PIN             GPIO_PinSource15
#define LED_B_PORT              GPIOB

#define PWM_TIM                 TIM1

/*����*/
void LED_GPIO_Config(void);
void BASE_TIM_Config (void);
void TIM_OC_Config(void);
void PWM_TIMx_Config(void);


#endif 
