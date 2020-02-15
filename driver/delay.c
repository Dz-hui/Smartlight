#include "delay.h"


/*********************************************************
*
*               一个神奇的精准延时雏形       
*
**********************************************************/
void  wait(unsigned long n)
{
    #if OS_USE
    
    sdelay_osschedlock();
    #endif
    
        do{
        n--;
        }while(n);
    #if OS_USE   
    sdelay_osschedunlock();
    #endif
}

/*********************************************************
* 系统滴答定时器初始化
* 中断时间1us
**********************************************************/
uint32_t sdelaytime = 0;

uint32_t fac_us = 0;
uint32_t fac_ms = 0;

void sdelay_init(void) {

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   
    fac_us = (SystemCoreClock /1000000)/8;
    fac_ms = (SystemCoreClock/1000)/8;
}
/*********************************************************
                  systick us延时函数  
**********************************************************/

void sdelay_us(uint32_t timedelay) {
     
    SysTick->LOAD = fac_us * timedelay;
    SysTick->VAL = 0;                           //清空当前寄存器值
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   
    while(!(SysTick->CTRL & (1<<16)));
    SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

/*********************************************************
                  systick ms延时函数  
**********************************************************/

void sdelay_ms(uint32_t timedelay) {

    SysTick->LOAD = fac_ms * timedelay;
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    while(!(SysTick->CTRL & (1<<16)));
    SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}


/*********************************************************
                  systick 中断服务函数  
**********************************************************/
void SysTick_Handler(void) {
    
    #if OS_USE
    OSIntEnter();
    #endif
    SystickTimeCount();
    #if OS_USE
    OSIntExit();
    #endif
}

/*********************************************************
                  systick 计数函数  
**********************************************************/
void SystickTimeCount(void) {
    sdelaytime--;
}


#if OS_USE

void sdelay_osschedlock(void) {

    OS_ERR err;
    OSSchedLock(&err);
}

void sdelay_osschedunlock(void) {

    OS_ERR err;
    OSSchedUnlock(&err);
}



#endif


