/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-07 15:16:10
*@FilePath: \大创\DEMO\Hardware\DHT11.h
*@Drscription: 
***********************************************************************/
#ifndef __DHT11__H
#define __DHT11__H

#include "main.h"


//DATA线引脚为PD6

#define DHT11_OUT_H         GPIO_SetBits(DHT11_PORT,DHT11_PIN)
#define DHT11_OUT_L         GPIO_ResetBits(DHT11_PORT,DHT11_PIN)
#define DHT11_READ          GPIO_ReadInputDataBit(DHT11_PORT,DHT11_PIN)

#define DHT11_CLK           RCC_APB2Periph_GPIOB
#define DHT11_PIN           GPIO_Pin_13
#define DHT11_PORT          GPIOB

void DHT11_Init (void);
void DHT11_MODE_IN(void);
void DHT11_MODE_OUT(void);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_ReadData(uint8_t *temp,uint8_t *humi);
void DHT11_Data(void);



#endif
