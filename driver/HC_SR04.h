/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-06 20:00:01
*@FilePath: \The IAR project of stm32f103c8t6\device\hc-sr04\HC_SR04.h
*@Drscription: 
***********************************************************************/
#ifndef _HCSR04_H_
#define _HCSR04_H_


#include "main.h"

/*���ź궨��*/
#define  TRIG_CLOCK_PORT            RCC_APB2Periph_GPIOA
#define  ECHO_CLOCK_PORT            RCC_APB2Periph_GPIOA
#define  TRIG_PIN_PORT              GPIOA
#define  ECHO_PIN_PORT              GPIOA
#define  TRIG_PIN                   GPIO_Pin_11
#define  ECHO_PIN                   GPIO_Pin_10
/*��ʱ���궨��*/
#define  HC_TIMX_CLOCK_PORT            RCC_APB1Periph_TIM2
#define  HC_TIMX_PORT                  TIM2
/***********************************************************************
********************************����************************************
***********************************************************************/
/*NVIC����*/
void TIM_NVIC_Config (void);
/*���ų�ʼ������*/
void PIN_Config (void);
/*��ʱ����ʼ��*/
void TIMX_Config (void);
/*��������ʼ�ź�*/
void STARUP (void);
/*����������*/
void  HCSR04_Config(void);
/*��ຯ��*/
float MEASURE (void);

void ENTRY_Standby (void);









#endif

