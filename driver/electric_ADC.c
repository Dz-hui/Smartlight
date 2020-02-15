/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-29 11:23:14
*@FilePath: \F1_DEMO\driver\electric_ADC.c
*@Drscription: 
***********************************************************************/
#include "electric_ADC.h"

void EADC_PIN_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct); 
}


void EADC_INIT(void)
{
   ADC_PIN_INIT();
   ADC_InitTypeDef ADC_InitStruct;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
   ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
   ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
   ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
   ADC_InitStruct.ADC_NbrOfChannel = 1;
   ADC_InitStruct.ADC_ScanConvMode = DISABLE;
   ADC_Init(ADC2,&ADC_InitStruct);
   
   ADC_RegularChannelConfig(ADC2,ADC_Channel_6,1,ADC_SampleTime_55Cycles5);//配置ADC为转换顺序1，采样时间为55个时钟周期
   
   ADC_Cmd(ADC2,ENABLE);//ADC使能
   
   ADC_SoftwareStartConvCmd(ADC2,ENABLE);//使能软件触发转换
}

float EADC_MEASURE (void)
{
    uint8_t adc_v[100];
    float collect=0;
    uint16_t ADC_collect=0;
    ADC_collect = ADC_GetConversionValue(ADC1);
    collect=((float)ADC_collect*(float)3.3/(float)4096);
    sprintf((char*)adc_v,"POWER=%f",collect);
    OLED_ShowStr(1,3, adc_v,1);
    return collect;
}
