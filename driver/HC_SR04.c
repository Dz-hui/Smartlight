/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-17 13:04:25
*@FilePath: \F1_DEMO\driver\HC_SR04.c
*@Drscription: 
***********************************************************************/

#include "HC_SR04.h"

/***********************************************************************
*******************************ȫ�ֱ���**********************************
***********************************************************************/
float count = 0;
/*���뿪�󣬿�ʼ����*/
uint32_t leaf_count =0;
/***********************************************************************
*@Function: void TIM_NVIC_Config (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-03 14:14:58
*@Drscription: NVIC����
***********************************************************************/
void TIM_NVIC_Config (void)
{
    NVIC_InitTypeDef  NVIC_InitStruct;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&NVIC_InitStruct);
}

/***********************************************************************
*@Function: void PIN_Init (void)
*@Input: PA1->����   PA2->���  TIM5 CH3
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-02 17:53:10
*@Drscription: ��ʼ������
***********************************************************************/
void PIN_Config (void)
{
    /*������ʱ��*/
    RCC_APB2PeriphClockCmd(TRIG_CLOCK_PORT|
                           ECHO_CLOCK_PORT,ENABLE);
    GPIO_InitTypeDef  GPIO_InitStruct;
    /*���������*/
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin=TRIG_PIN;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PIN_PORT,&GPIO_InitStruct);
    GPIO_ResetBits(TRIG_PIN_PORT,TRIG_PIN);
    /*���������*/
    GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN_FLOATING ;
    GPIO_InitStruct.GPIO_Pin = ECHO_PIN;
    GPIO_Init(ECHO_PIN_PORT,&GPIO_InitStruct);
}

/***********************************************************************
*@Function: void TIMX_Config (void)
*@Input: TIM5
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-03 13:27:59
*@Drscription: ��ʱ����ʼ��
***********************************************************************/
void TIMX_Config (void)
{
    /*����ʱ��ʱ��*/
    RCC_APB1PeriphClockCmd(HC_TIMX_CLOCK_PORT,ENABLE);
    /*1us����һ��*/
    /*��ʱ��ʱ������*/
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 1000-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(HC_TIMX_PORT,&TIM_TimeBaseInitStruct);
    /*����жϸ��±�־λ*/
    TIM_ClearFlag(HC_TIMX_PORT,TIM_FLAG_Update);
    /*ʹ�ܶ�ʱ���ж�*/
    TIM_ITConfig(HC_TIMX_PORT,TIM_IT_Update,ENABLE);
      /*ʹ�ܶ�ʱ��*/
    TIM_Cmd(HC_TIMX_PORT,ENABLE);
}

/***********************************************************************
*@Function: void STARUP (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-04 19:46:14
*@Drscription: ��������ʼ�ź�
***********************************************************************/
void STARUP (void)
{
    GPIO_SetBits(TRIG_PIN_PORT,TRIG_PIN);
    sdelay_us(10);
    GPIO_ResetBits(TRIG_PIN_PORT,TRIG_PIN);
}

/***********************************************************************
*@Function: void  HCSR04_Config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-04 20:04:57
*@Drscription: ����������
***********************************************************************/
void  HCSR04_Config(void)
{
    TIM_NVIC_Config();
    PIN_Config();
    TIMX_Config();
    
}

/***********************************************************************
*@Function: void MEASURE (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-04 20:22:47
*@Drscription: ��ຯ��
***********************************************************************/
float MEASURE (void)
{
    //uint8_t adc_v[100];
    STARUP();      
    sdelay_us(100);
    #if 0
    for (int i=8;i>0;i--)
    {
        while(GPIO_ReadInputDataBit(ECHO_PIN_PORT,ECHO_PIN)!=1); 
        while(GPIO_ReadInputDataBit(ECHO_PIN_PORT,ECHO_PIN)!=0);
    }
    #endif
    while(GPIO_ReadInputDataBit(ECHO_PIN_PORT,ECHO_PIN)!=1); 
    count = 0;
    while(GPIO_ReadInputDataBit(ECHO_PIN_PORT,ECHO_PIN)!=0);
    count = ((((float)count/(float)2)/(float)1000) * (float)340)*(float)100;
    //sprintf((char*)adc_v,"collect=%.2f",count);
    //OLED_ShowStr(1,2, adc_v,1);
    return count;
    
}

/***********************************************************************
*@Function: void TIM2_IRQHandler (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-04 20:05:59
*@Drscription: ��ʱ���ж�
***********************************************************************/
void TIM2_IRQHandler (void)
{
    if(TIM_GetITStatus(HC_TIMX_PORT,TIM_IT_Update)!=RESET)
    {
        TIM_ClearITPendingBit(HC_TIMX_PORT,TIM_IT_Update);
        
        count++;
    }
}

void ENTRY_Standby (void)
{   
    //uint8_t adc_collect[100];
    
    uint32_t leaf_Ornot=0;
    leaf_Ornot = MEASURE();
    if(leaf_Ornot<300)
    {
        leaf_count=0;
    }
    else if(leaf_Ornot>300 && leaf_Ornot<1000)
    {
        leaf_count++;
        //sprintf((char*)adc_collect,"collect=%d",leaf_count);
        //OLED_ShowStr(1,1, adc_collect,1);
        if(leaf_count==100)
        {
            UNWORK();
            leaf_count=0;
        }

    }
}

