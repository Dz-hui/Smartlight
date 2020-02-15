#include "DHT11.h"

uint8_t temp=0;
uint8_t humi=0;


void DHT11_Init (void)
{
    RCC_APB2PeriphClockCmd(DHT11_CLK,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin=DHT11_PIN;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(DHT11_PORT,&GPIO_InitStruct);
}

void DHT11_MODE_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin=DHT11_PIN;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(DHT11_PORT,&GPIO_InitStruct);
}

void DHT11_MODE_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;


    GPIO_InitStruct.GPIO_Pin=DHT11_PIN;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(DHT11_PORT,&GPIO_InitStruct);
}
    
uint8_t DHT11_Read_Byte(void)
{
    uint8_t i,data;
    for(i=0;i<8;i++)
    {
        if(DHT11_READ==0)
        {
            while(DHT11_READ==0);
        }
        sdelay_us (40);   //40us
        if(DHT11_READ==1)
        {
            while(DHT11_READ==1);
            data|=(uint8_t)0x01<<(7-i);
        }
        else
            data&=(uint8_t)~0x01<<(7-i);
                     
    }
    return data;
}

uint8_t DHT11_ReadData(uint8_t *temp,uint8_t *humi)
{
    uint8_t buf[5];
    uint8_t i;
    for(i=0;i<5;i++)
    {
        buf[i]=DHT11_Read_Byte();
        
    }
    if(buf[0]+buf[1]+buf[2]+buf[3]==buf[4])
    {
        *temp=buf[2];
        *humi=buf[0];
        return 1;
    }
    else
        return 0;    
}





void DHT11_Data(void)
{
    uint8_t temperature[100];
    uint8_t humidity[100];
    DHT11_Init ();
    DHT11_OUT_L;
    sdelay_us(20000);
    DHT11_OUT_H;
    sdelay_us(18);
    DHT11_MODE_IN();
    while(DHT11_READ==1);
    if(DHT11_READ==0)
    {    
        while(DHT11_READ==0);
        while(DHT11_READ==1);
        DHT11_ReadData(&temp,&humi);
        sprintf((char*)temperature,"temperature:%dc",temp);
        sprintf((char*)humidity,"humidity:%d%%",humi);
        OLED_ShowStr(0,4, temperature,2);
        OLED_ShowStr(0,6,humidity,2);
    }
    DHT11_MODE_OUT();
    DHT11_OUT_H;
	sdelay_ms(1500);
    
}    
