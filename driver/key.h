/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-07 17:01:20
*@FilePath: \´ó´´\DEMO\Hardware\key.h
*@Drscription: 
***********************************************************************/
#ifndef __key__H
#define __key__H


#include"main.h"

void KEY_EXTI_NVIC(void);
void KEY_EXIT_Config(void);
void KEYCOUNT_TIM_NVIC(void);
void KEYCOUNT_TIM_Config (void);
void KEY_config(void);
void KEY_Init (void);
uint8_t  KEY_Scan(void);
uint8_t KEY(void);


#define KEYCOUNT_TIM_CLOCK    RCC_APB1Periph_TIM4
#define KEYCOUNT_TIM          TIM4

#define KEY_ON          0U
#define KEY_OFF         1U

#define KEY1_CLOCK      RCC_APB2Periph_GPIOA
#define KEY2_CLOCK      RCC_APB2Periph_GPIOA

#define KEY1_GPIO_PORT  GPIOA
#define KEY2_GPIO_PORT  GPIOA

#define KEY1_GPIO_PIN   GPIO_Pin_3
#define KEY2_GPIO_PIN   GPIO_Pin_4

#define KEY1_EXTI_PORT  GPIO_PortSourceGPIOA
#define KEY1_EXTI_PIN   GPIO_PinSource3

#define KEY1_READ()        GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PIN)
#define KEY2_READ()        GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PIN)



#endif
