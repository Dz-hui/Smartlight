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
*                                       ��׼�����ʱ                     
*****************************************************************************************
*/

/*

*��ȷ��ʱ����
*ʹ�÷�����
*delay_us(0.4);   //��ʱ0.4us
*delay_ms(1456);  //��ʱ1.456s
*delay_s(21.4345);//��ʱ21.4345��
*/
#define  SYSCLK                             SystemCoreClock/1000000                 //ָ��CPU����Ƶ��Ϊ(SystemCoreClock/1000000)MHz
#define  A                                  6                                       //һ��ѭ��������������
#define  B                                  3                                       //���á���ʼ���������ܹ����õ�������
#define  delay_us(nus)                      wait(((nus)*(SYSCLK)-(B))/(A))
#define  delay_ms(nms)                      delay_us((nms)*1000)
#define  delay_s(ns)                        delay_ms((ns)*1000)


/*
*****************************************************************************************
*                                    ��������                    
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
