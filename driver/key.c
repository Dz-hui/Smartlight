/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-17 12:58:45
*@FilePath: \F1_DEMO\driver\key.c
*@Drscription: 
***********************************************************************/
#include "key.h"

extern   int8_t brightness=0;
//extern   uint8_t mode =0;
uint32_t key_count =0;
uint8_t  key_flag=0;
uint8_t mode =0;

/***********************************************************************
*@Function: void KEY_EXTI_NVIC(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-08 10:38:53
*@Drscription: �����ж�NVIC����
***********************************************************************/
#if 0
void KEY_EXTI_NVIC(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitTypeDef  NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
    NVIC_Init(&NVIC_InitStruct);
}

/***********************************************************************
*@Function: void KEY_EXIT_Config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-08 14:07:35
*@Drscription: �����ж�����
***********************************************************************/
void KEY_EXIT_Config(void)
{
    /*��ѡ��GPIO����ΪEXTI��ʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    /*
    **ѡ���ж���0
    **ʹ���ж���
    **ѡ���ж�ģʽ
    **�½��ش���
    */
    EXTI_InitTypeDef  EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line=EXTI_Line3;
    EXTI_InitStruct.EXTI_LineCmd=ENABLE;
    EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);
    /*ѡ��key1Ϊ�ж�Դ*/
    GPIO_EXTILineConfig(KEY1_EXTI_PORT,KEY1_EXTI_PIN);
}
#endif

/***********************************************************************
*@Function: void KEYCOUNT_TIM_NVIC(void)
*@Input: TIM4
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 21:09:15
*@Drscription: ������ʱ��NVIC����
***********************************************************************/
void KEYCOUNT_TIM_NVIC(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitTypeDef  NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
    NVIC_Init(&NVIC_InitStruct);
}

/***********************************************************************
*@Function: void KEYCOUNT_TIM_Config (void)
*@Input: TIM4
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 20:59:11
*@Drscription: 
***********************************************************************/
void KEYCOUNT_TIM_Config (void)
{
    /*
    **��ʱ������Ƶ
    **���ϼ���ģʽ
    **��ʱ1us
    **��װ����900
    **��Ƶϵ��100
    **��ʹ���ظ�������
    */
    RCC_APB1PeriphClockCmd(KEYCOUNT_TIM_CLOCK,ENABLE);
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period=10-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler=3600-1;
    TIM_TimeBaseInit(KEYCOUNT_TIM,&TIM_TimeBaseInitStruct);
    /*����жϱ�־λ*/
    TIM_ClearFlag(KEYCOUNT_TIM,TIM_FLAG_Update);
    /*�����ж�Ϊ�����ж�*/
    TIM_ITConfig(KEYCOUNT_TIM,TIM_IT_Update,ENABLE);
    TIM_Cmd(KEYCOUNT_TIM,DISABLE);
}

/***********************************************************************
*@Function: void KEY_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 17:34:47
*@Drscription: ��������
***********************************************************************/
void KEY_config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_APB2PeriphClockCmd(KEY1_CLOCK|
                           KEY2_CLOCK,
                           ENABLE);
    
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin=KEY1_GPIO_PIN;
    GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin=KEY2_GPIO_PIN;
    GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStruct);
}

/***********************************************************************
*@Function:void KEY_Init (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 21:20:37
*@Drscription: ������ʱ����ʼ��
***********************************************************************/
void KEY_Init (void)
{
    //KEY_EXTI_NVIC();
    //KEY_EXIT_Config();
    KEY_config();
    KEYCOUNT_TIM_NVIC();
    KEYCOUNT_TIM_Config();
    
}

/***********************************************************************
*@Function: uint8_t  KEY_Scan(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 17:34:10
*@Drscription: ����ɨ��
***********************************************************************/
uint8_t  KEY_Scan(void)
{
     static uint8_t flag=1;
    #if 1
   if (flag && ((KEY1_READ()==KEY_ON) || (KEY2_READ()==KEY_ON)))
    {
        flag=0;
        if(KEY1_READ()==KEY_ON)    
        {
            /*ʹ�ܶ�ʱ��*/
            TIM_Cmd(KEYCOUNT_TIM,ENABLE);
            //return 1;
        }      
        if (KEY2_READ()==KEY_ON)    
        {
            return 2;
        }
    } 
    if ((  (KEY1_READ()==KEY_OFF )&&
                (KEY2_READ()==KEY_OFF)
            ))
    {
        TIM_Cmd(KEYCOUNT_TIM,DISABLE);
        flag = 1; 
        if(key_count>0 && key_count<4000)
        {
            key_count=0;
            return 1;
        }
        else if (key_count>4000)
        {
            key_count=0;
            return 3;
        }
    }
        

    #endif
}

/***********************************************************************
*@Function: void KEY (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 17:35:21
*@Drscription: ��������
***********************************************************************/
uint8_t KEY(void)
{
    uint8_t ket_status = 0;
    //uint8_t ket_flag = 0;
    //ket_flag = key_flag;
    ket_status = KEY_Scan();
    #if 1
    /*������--   ÿ�μ�20%*/
    if(ket_status==1)
    {
        /*����*/
        //OLED_CLS();
        brightness+=2;
        /*������ȼӵ�100����Ϊ100*/
        if(brightness==10 || brightness>10)
        {
            brightness=10;
        }
        //key_flag=0;
    }
    /*��ģʽ*/
    else if( ket_status==3)
    {
        /*����*/
        //OLED_CLS();
        mode=1-mode;
    }
    /*������++*/
    if(ket_status==2)
    {
        /*����*/
        //OLED_CLS();
        brightness-=2; 
        /*����Ϊ0ʱ����һֱΪ0*/
        if(brightness==0 ||brightness<0)
        {
            brightness=0;
        }
    
    }
    return  mode;
    #endif

}

/***********************************************************************
*@Function: void TIM7_IRQHandler(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-07 21:18:44
*@Drscription: ���������жϺ���
***********************************************************************/
void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(KEYCOUNT_TIM,TIM_IT_Update)!=RESET)
    {
        //printf("�������\n");
        key_count ++;
    }
    TIM_ClearITPendingBit(KEYCOUNT_TIM,TIM_IT_Update);
}

#if 0
void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3)==SET)
    {
        TIM_Cmd(KEYCOUNT_TIM,DISABLE);
        //printf("%d\n",key_count);
        if(key_count>0 && key_count<1000000)
        {
            key_flag =1;
        }
        else
        {
            key_flag =2;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line3);
}
#endif
