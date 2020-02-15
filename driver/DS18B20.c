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
	
	/* ��������Ϊ�������� */
	DS18B20_Mode_IPU();
	
	/* �ȴ���������ĵ�������������Ϊһ��60~240us�ĵ͵�ƽ�ź� 
	 * �����������û����������ʱ�����ӻ����յ������ĸ�λ�źź󣬻���15~60us���������һ����������
	 */
	while( DS18B20_READ() && pulse_time<100 )
	{
		pulse_time++;
		DS18B20_DELAY_US(1);
	}	
	/* ����100us�󣬴������嶼��û�е���*/
	if( pulse_time >=100 )
		return 1;
	else
		pulse_time = 0;
	
	/* �������嵽�����Ҵ��ڵ�ʱ�䲻�ܳ���240us */
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
	
	/* ��0�Ͷ�1��ʱ������Ҫ����60us */	
	DS18B20_Mode_Out_PP();
	/* ��ʱ�����ʼ���������������� >1us <15us �ĵ͵�ƽ�ź� */
	DS18B20_LOW();
	DS18B20_DELAY_US(10);
	
	/* ���ó����룬�ͷ����ߣ����ⲿ�������轫�������� */
	DS18B20_Mode_IPU();
	//Delay_us(2);
	
	if( DS18B20_READ() == SET )
		dat = 1;
	else
		dat = 0;
	
	/* �����ʱ������ο�ʱ��ͼ */
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
		/* д0��д1��ʱ������Ҫ����60us */
		if (testb)
		{			
			DS18B20_LOW();
			/* 1us < �����ʱ < 15us */
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
			/* 1us < Trec(�ָ�ʱ��) < �����*/
			DS18B20_DELAY_US(2);
		}
	}
}


static void DS18B20_SkipRom ( void ) {
	DS18B20_Rst();	   
	
	DS18B20_Presence();	 
	
	DS18B20_WriteByte(0XCC);		/* ���� ROM */
	
}


static void DS18B20_MatchRom ( void ) {
	DS18B20_Rst();	   
	
	DS18B20_Presence();	 
	
	DS18B20_WriteByte(0X55);		/* ƥ�� ROM */
	
}

float DS18B20_GetTemp_SkipRom ( void ) {
	uint8_t tpmsb, tplsb;
	short s_tem;
	float f_tem;
	
	
	DS18B20_SkipRom ();
	DS18B20_WriteByte(0X44);				/* ��ʼת�� */
	
	
	DS18B20_SkipRom ();
  DS18B20_WriteByte(0XBE);				/* ���¶�ֵ */
	
	tplsb = DS18B20_ReadByte();		 
	tpmsb = DS18B20_ReadByte(); 
	
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	if( s_tem < 0 )		/* ���¶� */
		f_tem = (~s_tem+1) * 0.0625;	
	else
		f_tem = s_tem * 0.0625;
	
	return f_tem; 	
	
	
}

void DS18B20_ReadId ( uint8_t * ds18b20_id ) {
	uint8_t uc;
	
	
	DS18B20_WriteByte(0x33);       //��ȡ���к�
	
	for ( uc = 0; uc < 8; uc ++ )
	  ds18b20_id [ uc ] = DS18B20_ReadByte();
	
}



float DS18B20_GetTemp_MatchRom ( uint8_t * ds18b20_id ) {
	uint8_t tpmsb, tplsb, i;
	short s_tem;
	float f_tem;
	
	
	DS18B20_MatchRom ();            //ƥ��ROM
	
  for(i=0;i<8;i++)
		DS18B20_WriteByte ( ds18b20_id [ i ] );	
	
	DS18B20_WriteByte(0X44);				/* ��ʼת�� */

	
	DS18B20_MatchRom ();            //ƥ��ROM
	
	for(i=0;i<8;i++)
		DS18B20_WriteByte ( ds18b20_id [ i ] );	
	
	DS18B20_WriteByte(0XBE);				/* ���¶�ֵ */
	
	tplsb = DS18B20_ReadByte();		 
	tpmsb = DS18B20_ReadByte(); 
	
	
	s_tem = tpmsb<<8;
	s_tem = s_tem | tplsb;
	
	if( s_tem < 0 )		/* ���¶� */
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










