                                          /***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-17 20:00:59
*@Drscription: 
***********************************************************************/
#include "PWM.h"

/***********************************************************************
*@Function: void LED_GPIO_Config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 15:44:57
*@Drscription: LED����������
***********************************************************************/
void LED_GPIO_Config(void)
{
    /*��ledʱ��*/
    RCC_APB2PeriphClockCmd(LED_PIN_CLOCK,ENABLE);
    /*�����ö˿�ʱ�ӵ�ƽ*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    /*
    **LED  GPIO����
    **����ģʽ
    **�������
    **�Ȳ�����Ҳ������
    **�����ٶ�50MHZ
    */
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin=LED_B_PIN;
    GPIO_Init(LED_B_PORT,&GPIO_InitStruct);
}

/***********************************************************************
*@Function: void BASE_TIM_Config (void)

*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 15:46:29
*@Drscription: ��ʱ��ʱ������
***********************************************************************/
void BASE_TIM_Config (void)
{
    /*�򿪶�ʱ��ʱ��*/
    RCC_APB2PeriphClockCmd(PWM_TIM_CLOCK,ENABLE);
    /*
    **ʱ�Ӳ���Ƶ
    **���ϼ���ģʽ
    **��װ��ֵ10
    **��Ƶϵ��36000
    **�ظ�������Ϊ0
    */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period=10-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler=36000-1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(PWM_TIM,&TIM_TimeBaseInitStruct);
    /*ʹ�ܶ�ʱ��*/
    TIM_Cmd(PWM_TIM,ENABLE);
}

/***********************************************************************
*@Function: void TIM_OC_Config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 15:51:04
*@Drscription: PWM����
***********************************************************************/
void TIM_OC_Config(void)
{
    /*
    **����PWM1ģʽ
    **����Ϊ0                                        
    **ʹ������Ƚ�
    **���ü���Ϊ�ߵ�ƽ
    */
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1 ;
    TIM_OCInitStruct.TIM_Pulse = 10 ;
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High ;
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable ;
    TIM_OCInitStruct.TIM_OCNIdleState=TIM_OCNIdleState_Set ;
    #if 0
    TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_Pulse=5;
    TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;
    #endif
    TIM_OC3Init(PWM_TIM,&TIM_OCInitStruct);
    TIM_OC3PreloadConfig(PWM_TIM,TIM_OCPreload_Enable);
    /*ʹ�ܿ���PWM���*/
    TIM_CtrlPWMOutputs(PWM_TIM,ENABLE);
    /*ʹ����װ�ؼĴ���*/
    TIM_ARRPreloadConfig(PWM_TIM,ENABLE);
    /*ʹ�ܶ�ʱ��*/
    TIM_Cmd(PWM_TIM,ENABLE);
}

/***********************************************************************
*@Function: void PWM_TIMx_Config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 15:57:32
*@Drscription: ���pwm��ʱ����ʼ��
***********************************************************************/
void PWM_TIMx_Config(void)
{
    BASE_TIM_Config ();
    TIM_OC_Config();
}    

