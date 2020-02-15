#include "tim.h"

uint32_t tim_updata;
extern uint8_t key_status;

void tim1_init(void) {

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInitStruct.TIM_Period = 7200 - 1;     //1ms = x * 0.1 
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;  //得到0.1ms,即10KHz, 72MHz/7200 = 10KHz
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
    
    TIM_ClearFlag(TIM1,TIM_FLAG_Update);
    
    TIM_ITConfig(TIM1,TIM_IT_Update,DISABLE);
    
    TIM_Cmd(TIM1,ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&NVIC_InitStruct);
}


/*
 定时器中断处理
 */
void TIM1_UP_IRQHandler(void) {

    if(TIM_GetITStatus(TIM1,TIM_IT_Update) !=RESET ) {
            
        tim_updata++;
        
        if(tim_updata==100) {
        
            tim_updata=0;
        }
        TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
    }
}




















