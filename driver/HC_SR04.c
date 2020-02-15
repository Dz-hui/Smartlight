/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-17 13:04:25
*@FilePath: \F1_DEMO\driver\HC_SR04.c
*@Drscription: 
***********************************************************************/

#include "HC_SR04.h"

/***********************************************************************
*******************************全局变量**********************************
***********************************************************************/
float count = 0;
/*人离开后，开始计数*/
uint32_t leaf_count =0;
/***********************************************************************
*@Function: void TIM_NVIC_Config (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-03 14:14:58
*@Drscription: NVIC配置
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
*@Input: PA1->输入   PA2->输出  TIM5 CH3
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-02 17:53:10
*@Drscription: 初始化引脚
***********************************************************************/
void PIN_Config (void)
{
    /*开引脚时钟*/
    RCC_APB2PeriphClockCmd(TRIG_CLOCK_PORT|
                           ECHO_CLOCK_PORT,ENABLE);
    GPIO_InitTypeDef  GPIO_InitStruct;
    /*输入口配置*/
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin=TRIG_PIN;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PIN_PORT,&GPIO_InitStruct);
    GPIO_ResetBits(TRIG_PIN_PORT,TRIG_PIN);
    /*输出口配置*/
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
*@Drscription: 定时器初始化
***********************************************************************/
void TIMX_Config (void)
{
    /*开定时器时钟*/
    RCC_APB1PeriphClockCmd(HC_TIMX_CLOCK_PORT,ENABLE);
    /*1us计数一次*/
    /*定时器时基配置*/
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 1000-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(HC_TIMX_PORT,&TIM_TimeBaseInitStruct);
    /*清除中断更新标志位*/
    TIM_ClearFlag(HC_TIMX_PORT,TIM_FLAG_Update);
    /*使能定时器中断*/
    TIM_ITConfig(HC_TIMX_PORT,TIM_IT_Update,ENABLE);
      /*使能定时器*/
    TIM_Cmd(HC_TIMX_PORT,ENABLE);
}

/***********************************************************************
*@Function: void STARUP (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-04 19:46:14
*@Drscription: 超声波起始信号
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
*@Drscription: 超声波配置
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
*@Drscription: 测距函数
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
*@Drscription: 定时器中断
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

