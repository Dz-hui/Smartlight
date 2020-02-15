#ifndef __USART_H
#define __USART_H

/*********************************************************
*                       INC
**********************************************************/
#include "stm32f10x.h"
#include "stdio.h"
/*********************************************************
*                    GPIO DEFINE 
**********************************************************/
#define UART_GPIO_PORT                  GPIOA
#define UART_GPIO_BUS                   RCC_APB2PeriphClockCmd
#define UART_GPIO_CLK                   RCC_APB2Periph_GPIOA


#define UART_GPIO_TX                    GPIO_Pin_9
#define UART_GPIO_TX_Mode               GPIO_Mode_AF_PP     
#define UART_GPIO_TX_Speed              GPIO_Speed_50MHz

#define UART_GPIO_RX                    GPIO_Pin_10
#define UART_GPIO_RX_Mode               GPIO_Mode_IN_FLOATING

/*********************************************************
*                    USART DEFINE 
**********************************************************/
#define USART_PORT                      USART1
#define USART_BUS                       RCC_APB2PeriphClockCmd                       
#define USART_CLK                       RCC_APB2Periph_USART1
#define USART_BAUDRATE                  115200

/*********************************************************
*                     FUNCTION 
**********************************************************/
void USART1_Init(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif
