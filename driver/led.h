#ifndef __led_h
#define __led_h

#include "stm32f10x.h"


#define LED1_BUS                        RCC_APB2PeriphClockCmd
#define LED1_CLK                        RCC_APB2Periph_GPIOA
#define LED1_PORT                       GPIOA
#define LED1                            GPIO_Pin_3                           

#define LED2_BUS                        RCC_APB2PeriphClockCmd
#define LED2_CLK                        RCC_APB2Periph_GPIOA
#define LED2_PORT                       GPIOA
#define LED2                            GPIO_Pin_4   




void led_init(void);
void led_on(uint32_t LEDx);
void led_off(uint32_t LEDx);
void led_toggle(uint32_t LEDx);


void relay_init(void);
void relay_on(void);
void relay_off(void);
void relay_toggle(void);

#endif 
