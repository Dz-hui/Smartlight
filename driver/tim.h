#ifndef __tim_h
#define __tim_h

#include "stm32f10x.h"
#include "led.h"
#include "main.h"




void tim1_init(void);
void TIM1_UP_IRQHandler(void);

#endif


