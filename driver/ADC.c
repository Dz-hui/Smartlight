/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-17 13:04:08
*@FilePath: \F1_DEMO\driver\ADC.c
*@Drscription: 
***********************************************************************/
#include "ADC.h"

void ADC_PIN_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct); 
}


void ADC_INIT(void)
{
   ADC_PIN_INIT();
   ADC_InitTypeDef ADC_InitStruct;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
   ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
   ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
   ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
   ADC_InitStruct.ADC_NbrOfChannel = 1;
   ADC_InitStruct.ADC_ScanConvMode = DISABLE;
   ADC_Init(ADC1,&ADC_InitStruct);
   
   ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_55Cycles5);//配置ADC为转换顺序1，采样时间为55个时钟周期
   
   ADC_Cmd(ADC1,ENABLE);//ADC使能
   
   ADC_SoftwareStartConvCmd(ADC1,ENABLE);//使能软件触发转换
}

/***********************************************************************
*@Function: void MEASURE (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-05 21:38:45
*@Drscription: 测得电压
***********************************************************************/
float ADC_MEASURE (void)
{
    //uint8_t adc_collect[100];
    //uint8_t adc_v[100];
    float collect=0;
    uint16_t ADC_collect=0;
    ADC_collect = ADC_GetConversionValue(ADC1);
    //sprintf((char*)adc_collect,"ADC_collect=%d",ADC_collect);
    //OLED_ShowStr(1,1, adc_collect,1);
    collect=((float)ADC_collect/(float)4096);
    //printf("collect=%.2f\n\n",collect);
    //sprintf((char*)adc_v,"collect=%.2f",collect);
    //OLED_ShowStr(1,2, adc_v,1);

    return collect;
}
