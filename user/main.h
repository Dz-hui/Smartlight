/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-17 12:58:46
*@FilePath: \F1_DEMO\user\main.h
*@Drscription: 
***********************************************************************/
#ifndef __main_h
#define __main_h

#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "oled_i2c.h"
#include "delay.h"
#include "tim.h"
#include "DHT11.h"
#include "ds18b20.h"
#include "pwm.h"
#include "HC_SR04.h"
#include "ADC.h"
#include "APP.h"
#include "electric_ADC.h"

typedef enum {

    moto_p_run = 0,
    moto_stop = 1,
    moto_n_run = 3,
    
}moto_status;

typedef struct {

    float temperaure;

    float humidity;

    moto_status moto;

    uint8_t relay_status;
}THcrtl;


#endif
