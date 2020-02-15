#ifndef __DELAY_H
#define __DELAY_H

/*
*****************************************************************************************
*                                       INC                     
*****************************************************************************************
*/

#include "stm32f10x.h"
#include "core_cm3.h"

#define OS_USE                                                              0

#if OS_USE

#include "includes.h"

#endif

/*
*****************************************************************************************
*                                       精准软件定时                     
*****************************************************************************************
*/

/*

*精确延时函数
*使用方法：
*delay_us(0.4);   //延时0.4us
*delay_ms(1456);  //延时1.456s
*delay_s(21.4345);//延时21.4345秒
*/
#define  SYSCLK                             SystemCoreClock/1000000                 //指明CPU工作频率为(SystemCoreClock/1000000)MHz
#define  A                                  6                                       //一次循环所花的周期数
#define  B                                  3                                       //调用、初始化、返回总共所用的周期数
#define  delay_us(nus)                      wait(((nus)*(SYSCLK)-(B))/(A))
#define  delay_ms(nms)                      delay_us((nms)*1000)
#define  delay_s(ns)                        delay_ms((ns)*1000)


/*
*****************************************************************************************
*                                    函数声明                    
*****************************************************************************************
*/

void wait(unsigned long n);
void sdelay_init(void);
void sdelay_us(uint32_t timedelay);
void sdelay_ms(uint32_t timedelay);
void SysTick_Handler(void);
void SystickTimeCount(void);

#if OS_USE
void sdelay_osschedlock(void);
void sdelay_osschedunlock(void);
#endif

#endif
/*****************************************************************************************/
