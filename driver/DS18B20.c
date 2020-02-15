#include "DS18B20.h"



static void DS18B20_GPIO_Config(void) {		
	GPIO_InitTypeDef GPIO_InitStructure;
	DS18B20_GPIO_BUS ( DS18B20_GPIO_CLK, ENABLE); 															   
  	GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_Init ( DS18B20_PORT , &GPIO_InitStructure );
}

static void DS18B20_Mode_IPU(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
    GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}

static void DS18B20_Mode_Out_PP(void) {
 	GPIO_InitTypeDef GPIO_InitStructure;													   
  	GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}

static void DS18B20_Rst(void) {
	DS18B20_Mode_Out_PP();	
	DS18B20_LOW();
	DS18B20_DELAY_US(750);
	DS18B20_HIGH();
	DS18B20_DELAY_US(15);
}

static uint8_t DS18B20_Presence(void) {
	uint8_t pulse_time = 0;
	
	/* 主机设置为上拉输入 */
	DS18B20_Mode_IPU();
	
	/* 等待存在脉冲的到来，存在脉冲为一个60~240us的低电平信号 
	 * 如果存在脉冲没有来则做超时处理，从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲
	 */
	while( DS18B20_READ() && pulse_time<100 )
	{
		pulse_time++;
		DS18B20_DELAY_US(1);
	}	
	/* 经过100us后，存在脉冲都还没有到来*/
	if( pulse_time >=100 )
		return 1;
	else
		pulse_time = 0;
	
	/* 存在脉冲到来，且存在的时间不能超过240us */
	while( !DS18B20_READ() && pulse_time<240 )
	{
		pulse_time++;
		DS18B20_DELAY_US(1);
	}	
	if( pulse_time >=240 )
		return 1;
	else
		return 0;
}


static uint8_t DS18B20_ReadBit(void) {
	uint8_t dat;
	
	/* 读0和读1的时间至少要大于60us */	
	DS18B20_Mode_Out_PP();
	/* 读时间的起始：必须由主机产生 >1us <15us 的低电平信号 */
	DS18B20_LOW();
	DS18B20_DELAY_US(10);
	
	/* 设置成输入，释放总线，由外部上拉电阻将总线拉高 */
	DS18B20_Mode_IPU();
	//Delay_us(2);
	
	if( DS18B20_READ() == SET )
		dat = 1;
	else
		dat = 0;
	
	/* 这个延时参数请参考时序图 */
	DS18B20_DELAY_US(45);
	
	return dat;
}

static uint8_t DS18B20_ReadByte(void) {
	uint8_t i, j, dat = 0;	
	
	for(i=0; i<8; i++) 
	{
		j = DS18B20_ReadBit();		
		dat = (dat) | (j<<i);
	}
	
	return dat;
}

static void DS18B20_WriteByte(uint8_t dat) {
	uint8_t i, testb;
	DS18B20_Mode_Out_PP();
	
	for( i=0; i<8; i++ )
	{
		testb = dat&0x01;
		dat = dat>>1;		
		/* 写0和写1的时间至少要大于60us */
		if (testb)
		{			
			DS18B20_LOW();
			/* 1us < 这个延时 < 15us */
			DS18B20_DELAY_US(8);
			
			DS18B20_HIGH();
			DS18B20_DELAY_US(58);
		}		
		else
		{			
			DS18B20_LOW();
			/* 60us < Tx 0 < 120us */
			DS18B20_DELAY_US(70);
			
			DS18B20_HIGH();			
			/* 1us < Trec(恢复时间) < 无穷大*/
			DS18B20_DELAY_US(2);
		}
	}
}


static void DS18B20_SkipRom ( void ) {
	DS18B20_Rst();	   
	
	DS18B20_Presence();	 
	
	DS18B20_WriteByte(0XCC);		/* 跳过 ROM */
	
}


static void DS18B20_MatchRom ( void ) {
	DS18B20_Rst();	   
	
	DS18B20_Presence();	 
	
	DS18B20_WriteByte(0X55);		/* 匹配 ROM */
	
}

float DS18B20_GetTemp_SkipRom ( void ) {
	uint8_t tpmsb, tplsb;
	short s_tem;
	float f_tem;
	
	
	DS18B20_SkipRom ();
	DS18B20_WriteByte(0X44);				/* 开始转换 */
	
	
	DS18B20_SkipRom ();
  DS18B20_WriteByte(0XBE);				/* 读温度值 */
	
	tplsb = DS18B20_ReadByte();		 
	tpmsb = DS18B20_ReadByte(); 
	
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	if( s_tem < 0 )		/* 负温度 */
		f_tem = (~s_tem+1) * 0.0625;	
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem; 	
	
	
}

void DS18B20_ReadId ( uint8_t * ds18b20_id ) {
	uint8_t uc;
	
	
	DS18B20_WriteByte(0x33);       //读取序列号
	
	for ( uc = 0; uc < 8; uc ++ )
	  ds18b20_id [ uc ] = DS18B20_ReadByte();
	
}



float DS18B20_GetTemp_MatchRom ( uint8_t * ds18b20_id ) {
	uint8_t tpmsb, tplsb, i;
	short s_tem;
	float f_tem;
	
	
	DS18B20_MatchRom ();            //匹配ROM
	
  for(i=0;i<8;i++)
		DS18B20_WriteByte ( ds18b20_id [ i ] );	
	
	DS18B20_WriteByte(0X44);				/* 开始转换 */

	
	DS18B20_MatchRom ();            //匹配ROM
	
	for(i=0;i<8;i++)
		DS18B20_WriteByte ( ds18b20_id [ i ] );	
	
	DS18B20_WriteByte(0XBE);				/* 读温度值 */
	
	tplsb = DS18B20_ReadByte();		 
	tpmsb = DS18B20_ReadByte(); 
	
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	if( s_tem < 0 )		/* 负温度 */
		f_tem = (~s_tem+1) * 0.0625;	
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem; 	
}


uint8_t DS18B20_Init(void) {
    
    DS18B20_GPIO_Config ();
	
	DS18B20_HIGH();
	
	DS18B20_Rst();
	
	return DS18B20_Presence ();

}










