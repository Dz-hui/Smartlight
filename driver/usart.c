#include "usart.h"

/**********************************************************
*                     debug´®¿Ú³õÊ¼»¯  
**********************************************************/
void USART1_Init(void) {

    GPIO_InitTypeDef USART1_GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    
    UART_GPIO_BUS(UART_GPIO_CLK,ENABLE);
    USART_BUS(USART_CLK,ENABLE);
    
    
    USART1_GPIO_InitStruct.GPIO_Mode = UART_GPIO_TX_Mode;
    USART1_GPIO_InitStruct.GPIO_Pin = UART_GPIO_TX;
    USART1_GPIO_InitStruct.GPIO_Speed = UART_GPIO_TX_Speed;
    GPIO_Init(UART_GPIO_PORT, &USART1_GPIO_InitStruct);
        
    USART1_GPIO_InitStruct.GPIO_Pin = UART_GPIO_RX;
	USART1_GPIO_InitStruct.GPIO_Mode = UART_GPIO_RX_Mode;
	GPIO_Init(UART_GPIO_PORT, &USART1_GPIO_InitStruct);
     
	USART_InitStruct.USART_BaudRate = USART_BAUDRATE;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No ;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART_PORT, &USART_InitStruct);
	USART_Cmd(USART_PORT, ENABLE);	
}

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx,ch);
		
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	temp_h = (ch&0XFF00)>>8;
	temp_l = ch&0XFF;
	USART_SendData(pUSARTx,temp_h);	
    
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


int fputc(int ch, FILE *f)
{
		USART_SendData(USART_PORT, (uint8_t) ch);
		
		while (USART_GetFlagStatus(USART_PORT, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


int fgetc(FILE *f)
{
		while (USART_GetFlagStatus(USART_PORT, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART_PORT);
}

