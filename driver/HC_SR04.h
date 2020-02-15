/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-06 20:00:01
*@FilePath: \The IAR project of stm32f103c8t6\device\hc-sr04\HC_SR04.h
*@Drscription: 
***********************************************************************/
#ifndef _HCSR04_H_
#define _HCSR04_H_


#include "main.h"

/*引脚宏定义*/
#define  TRIG_CLOCK_PORT            RCC_APB2Periph_GPIOA
#define  ECHO_CLOCK_PORT            RCC_APB2Periph_GPIOA
#define  TRIG_PIN_PORT              GPIOA
#define  ECHO_PIN_PORT              GPIOA
#define  TRIG_PIN                   GPIO_Pin_11
#define  ECHO_PIN                   GPIO_Pin_10
/*定时器宏定义*/
#define  HC_TIMX_CLOCK_PORT            RCC_APB1Periph_TIM2
#define  HC_TIMX_PORT                  TIM2
/***********************************************************************
********************************函数************************************
***********************************************************************/
/*NVIC配置*/
void TIM_NVIC_Config (void);
/*引脚初始化函数*/
void PIN_Config (void);
/*定时器初始化*/
void TIMX_Config (void);
/*超声波起始信号*/
void STARUP (void);
/*超声波配置*/
void  HCSR04_Config(void);
/*测距函数*/
float MEASURE (void);

void ENTRY_Standby (void);









#endif

