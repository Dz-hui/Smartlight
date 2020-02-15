/***********************************************************************
*@Author: Dz_hui
*@Date: 2019-12-07 16:51:04
*@FilePath: \大创\DEMO\Hardware\APP.c
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
*@Drscription: 所有外设初始化
***********************************************************************/
void APP_Init(void)
{
    /*OLED初始化*/
    I2C_Configuration();
    OLED_Init();
    OLED_ON();
    OLED_CLS();

    /*延时函数初始化*/
    sdelay_init();

    /*LED初始化*/
    LED_GPIO_Config();
    //printf("led\n");

    /*PWM初始化*/
    PWM_TIMx_Config();
    //printf("tim\n");

    /*按键初始化*/
    KEY_Init();

    /*光敏电阻传感器初始化*/
    ADC_INIT();

    /*电源电量检测*/
    EADC_INIT();

    /*超声波初始化*/
    HCSR04_Config();
    OLED_ShowStr(1,0,(uint8_t*)"Init_complete",1);
}
/***********************************************************************
*@Function: void WORKING (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-08 20:16:59
*@Drscription: 工作状态
***********************************************************************/
void WORKING (void)
{
    uint8_t mode;
    float light_collect;
    uint8_t brightness_mode[100];
    float power;
    /*DHT11测量温湿度*/
    DHT11_Data();
    ADC_MEASURE();
    power=EADC_MEASURE();
    /*按键检测*/
    mode=KEY();
    #if 1
    /*mode==1进入手动模式   mode==0 进入自动模式*/
    if(mode==1)
    {
        /*OLED打印当前模式*/
        OLED_ShowStr(1,0,(uint8_t*)"Manual mode",1);
        /*手动模式调亮度*/
        TIM_SetCompare3(PWM_TIM,brightness);
        /*OLED打印当前亮度值*/
        sprintf((char*)brightness_mode,"brightness:%2d%%",(10-brightness));
        OLED_ShowStr(1,2,brightness_mode,2);
    }
    if(mode==0)
    {
        /*打印当前模式*/
        OLED_ShowStr(1,0,(uint8_t*)"Automatic mode",1);
        light_collect=ADC_MEASURE();
        light_collect=(1-light_collect)*10;
        sprintf((char*)brightness_mode,"brightness:%2d%%",(10-(uint8_t)light_collect));
        OLED_ShowStr(1,2,brightness_mode,2);
        /*自动调节亮度*/
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
    /*超声波测量距离，检测有无人*/
    ENTRY_Standby();
    #endif 
}

/***********************************************************************
*@Function: void UNWORK (void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2019-12-08 20:17:20
*@Drscription: 进入睡眠模式
***********************************************************************/
void UNWORK (void)
{
    /*打开电源管理器*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    /*进入睡眠模式*/
    PWR_EnterSTANDBYMode();
}
