#include "delay.h"


/*********************************************************
*
*               һ������ľ�׼��ʱ����       
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
* ϵͳ�δ�ʱ����ʼ��
* �ж�ʱ��1us
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
                  systick us��ʱ����  
**********************************************************/

void sdelay_us(uint32_t timedelay) {
     
    SysTick->LOAD = fac_us * timedelay;
    SysTick->VAL = 0;                           //��յ�ǰ�Ĵ���ֵ
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   
    while(!(SysTick->CTRL & (1<<16)));
    SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

/*********************************************************
                  systick ms��ʱ����  
**********************************************************/

void sdelay_ms(uint32_t timedelay) {

    SysTick->LOAD = fac_ms * timedelay;
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    while(!(SysTick->CTRL & (1<<16)));
    SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}


/*********************************************************
                  systick �жϷ�����  
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
                  systick ��������  
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


