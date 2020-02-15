#ifndef __DS18B20_H
#define __DS18B20_H
 
/*********************************************************
*                       DHT11 INC                        *  
**********************************************************/
#include "stm32f10x.h"
#include "DHT11.h"
#include "delay.h"

/*********************************************************
*                   DS18B20  GPIO����                          
**********************************************************/
#define DS18B20_PIN                 GPIO_Pin_1
#define DS18B20_PORT                GPIOA

#define DS18B20_GPIO_BUS            RCC_APB2PeriphClockCmd
#define DS18B20_GPIO_CLK            RCC_APB2Periph_GPIOA

/*********************************************************
*                   DS18B20  �ߵ͵�ƽ����                         
**********************************************************/

#define DS18B20_HIGH()              GPIO_SetBits(DS18B20_PORT, DS18B20_PIN)
#define DS18B20_LOW()               GPIO_ResetBits(DS18B20_PORT, DS18B20_PIN)

/*********************************************************
*                   DS18B20  ��ƽ��ȡ                        
**********************************************************/

#define DS18B20_READ()              GPIO_ReadInputDataBit(DS18B20_PORT, DS18B20_PIN)

/*********************************************************
*                   DS18B20  ��ʱ����                        
**********************************************************/

#define DS18B20_DELAY_US(TIM)       delay_us(TIM)


/*********************************************************
*                   ��������                       
**********************************************************/
uint8_t DS18B20_Init(void);
float DS18B20_GetTemp_MatchRom ( uint8_t * ds18b20_id );
void DS18B20_ReadId ( uint8_t * ds18b20_id );
float DS18B20_GetTemp_SkipRom ( void );


#endif 


