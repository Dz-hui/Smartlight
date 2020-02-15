/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-07 16:51:04
*@FilePath: \��\DEMO\Hardware\APP.c
*@Drscription: 
***********************************************************************/
#include "APP.h"

extern int8_t brightness;
//extern uint8_t mode;

/***********************************************************************
*@Function: void APP_Init(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-08 20:15:23
*@Drscription: ���������ʼ��
***********************************************************************/
void APP_Init(void)
{
    /*OLED��ʼ��*/
    I2C_Configuration();
    OLED_Init();
    OLED_ON();
    OLED_CLS();

    /*��ʱ������ʼ��*/
    sdelay_init();

    /*LED��ʼ��*/
    LED_GPIO_Config();
    //printf("led\n");

    /*PWM��ʼ��*/
    PWM_TIMx_Config();
    //printf("tim\n");

    /*������ʼ��*/
    KEY_Init();

    /*�������贫������ʼ��*/
    ADC_INIT();

    /*��Դ�������*/
    EADC_INIT();

    /*��������ʼ��*/
    HCSR04_Config();
    OLED_ShowStr(1,0,(uint8_t*)"Init_complete",1);
}
/***********************************************************************
*@Function: void WORKING (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-08 20:16:59
*@Drscription: ����״̬
***********************************************************************/
void WORKING (void)
{
    uint8_t mode;
    float light_collect;
    uint8_t brightness_mode[100];
    float power;
    /*DHT11������ʪ��*/
    DHT11_Data();
    ADC_MEASURE();
    power=EADC_MEASURE();
    /*�������*/
    mode=KEY();
    #if 1
    /*mode==1�����ֶ�ģʽ   mode==0 �����Զ�ģʽ*/
    if(mode==1)
    {
        /*OLED��ӡ��ǰģʽ*/
        OLED_ShowStr(1,0,(uint8_t*)"Manual mode",1);
        /*�ֶ�ģʽ������*/
        TIM_SetCompare3(PWM_TIM,brightness);
        /*OLED��ӡ��ǰ����ֵ*/
        sprintf((char*)brightness_mode,"brightness:%2d%%",(10-brightness));
        OLED_ShowStr(1,2,brightness_mode,2);
    }
    if(mode==0)
    {
        /*��ӡ��ǰģʽ*/
        OLED_ShowStr(1,0,(uint8_t*)"Automatic mode",1);
        light_collect=ADC_MEASURE();
        light_collect=(1-light_collect)*10;
        sprintf((char*)brightness_mode,"brightness:%2d%%",(10-(uint8_t)light_collect));
        OLED_ShowStr(1,2,brightness_mode,2);
        /*�Զ���������*/
        TIM_SetCompare3(PWM_TIM,(uint8_t)light_collect);
    }
    if(power>4)
    {
        OLED_ShowStr(1,1,"POWER:Battery powered",1);
    }
    else
    {
        OLED_ShowStr(1,1,"POWER:USB powered",1);
    }
    /*�������������룬���������*/
    ENTRY_Standby();
    #endif 
}

/***********************************************************************
*@Function: void UNWORK (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-08 20:17:20
*@Drscription: ����˯��ģʽ
***********************************************************************/
void UNWORK (void)
{
    /*�򿪵�Դ������*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    /*����˯��ģʽ*/
    PWR_EnterSTANDBYMode();
}
