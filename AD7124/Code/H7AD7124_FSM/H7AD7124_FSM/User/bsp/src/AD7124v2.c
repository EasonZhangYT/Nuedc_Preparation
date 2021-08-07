#include "bsp.h"
#include "AD7124.h" 

//////////////////////////////////////////////////////////////////////////////////	 
AD7124REGSTRUCT   AD7124REG={0};
volatile	AD7124Struct AD7124={0};
volatile	AD7124Struct sAD7124Signle[2]={{0},{0}};
void AD7124Init(void)
{
	volatile int i,itemp=0;
	
	GPIO_InitTypeDef GPIO_Initure;
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOG时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();	

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;// 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	GPIO_Initure.Mode			= GPIO_MODE_OUTPUT_PP,  //推挽输出
	GPIO_Initure.Pull			= GPIO_PULLUP,          //无
	GPIO_Initure.Speed			= GPIO_SPEED_FREQ_HIGH,
	GPIO_Initure.Pin			= AD7124_CS_PIN;
	HAL_GPIO_Init(AD7124_CS_PORT,&GPIO_Initure);
	AD7124_CS_H;

//	SPI1_Init(); //初始化SPI
	bsp_InitSPIBus();	/* 配置SPI总线 */	
	AD7124_CS_L;
	bsp_DelayMS(10);
	AD7124_Reset();
	bsp_DelayMS(10);
	AD7124_CS_H;
	
	//////寄存器初始化,地址，长度（几个字节）
	AD7124REG.STATUS.adr=0X00;  AD7124REG.STATUS.len=1; 
	AD7124REG.ADC_CONTROL.adr=0X01;  AD7124REG.ADC_CONTROL.len=2; 
	AD7124REG.DATA.adr=0X02;  AD7124REG.DATA.len=3; 
	AD7124REG.IO_CONTROL_1.adr=0X03;  AD7124REG.IO_CONTROL_1.len=3; 
	AD7124REG.IO_CONTROL_2.adr=0X04;  AD7124REG.IO_CONTROL_2.len=2; 
	AD7124REG.ID.adr=0X05;  
// 	AD7124REG.ID.len=2; 
	AD7124REG.ID.len=1; 
	AD7124REG.ERR.adr=0X06;  AD7124REG.ERR.len=3; 
	AD7124REG.ERR_EN.adr=0X07;  AD7124REG.ERR_EN.len=3; 
	AD7124REG.MCLK_COUNT.adr=0X08;  AD7124REG.MCLK_COUNT.len=1; 
	for(i=0; i<17; i++)
	{
			AD7124REG.CHANNEL[i].adr=i+0x09;
			AD7124REG.CHANNEL[i].len=2;
	}
	for(i=0; i<8; i++)
	{
			AD7124REG.CONFIG[i].adr=i+0x19;
			AD7124REG.CONFIG[i].len=2;
	}	
	for(i=0; i<8; i++)
	{
			AD7124REG.FLITER[i].adr=i+0x21;
			AD7124REG.FLITER[i].len=3;
	}		
		for(i=0; i<8; i++)
	{
			AD7124REG.Offset[i].adr=i+0x29;
			AD7124REG.Offset[i].len=3;
	}		
		for(i=0; i<8; i++)
	{
			AD7124REG.GAIN[i].adr=i+0x31;
			AD7124REG.GAIN[i].len=3;
	}		
	///////////
//	delay_ms(100);
	bsp_DelayMS(100);
	AD7124REG.ID.value = AD7124ReadREG(AD7124REG.ID.adr, AD7124REG.ID.len);
	//ADC控制寄存器
	AD7124REG.ADC_CONTROL.value.bit.DATA_STATUS = 1;
	AD7124REG.ADC_CONTROL.value.bit.DOUT_RDY_DEL=0;
	AD7124REG.ADC_CONTROL.value.bit.CONT_READ=1;			//1：连续读取
	AD7124REG.ADC_CONTROL.value.bit.DATA_STATUS=0;
	AD7124REG.ADC_CONTROL.value.bit.CS_EN=0;//置1时， DOUT/RDY引脚在SCLK无效沿之后继续用作DOUT引脚。当CS变为高电平时，该引脚变为RDY引脚。
	AD7124REG.ADC_CONTROL.value.bit.REF_EN=1;//内部基准输出使能
	AD7124REG.ADC_CONTROL.value.bit.POWER_MODE=3;//0:低功耗，1：中功率，23：全功率
	AD7124REG.ADC_CONTROL.value.bit.Mode=0;//0:	连续转换；1：单次转换；2待机模式，3：关断模式，4：空闲模式，5：内部零电平校准，6：内部满偏校准，7：系统零电平校准，8：系统满偏校准
//	AD7124.InitERR += AD7124WriteREG(AD7124REG.ADC_CONTROL.adr,AD7124REG.ADC_CONTROL.value.all, AD7124REG.ADC_CONTROL.len);
 	//通道寄存器
	AD7124REG.CHANNEL[0].value.bit.Enable=1;
	AD7124REG.CHANNEL[0].value.bit.Setup=0;
	AD7124REG.CHANNEL[0].value.bit.AINP=0;
	AD7124REG.CHANNEL[0].value.bit.AINM=1;//0X11-AVSS
	AD7124.InitERR += AD7124WriteREG(AD7124REG.CHANNEL[0].adr,AD7124REG.CHANNEL[0].value.all, AD7124REG.CHANNEL[0].len);

	AD7124REG.CHANNEL[1].value.bit.Enable=1;
	AD7124REG.CHANNEL[1].value.bit.Setup=0;
	AD7124REG.CHANNEL[1].value.bit.AINP=2;
	AD7124REG.CHANNEL[1].value.bit.AINM=3;//0X11-AVSS
	AD7124.InitERR += AD7124WriteREG(AD7124REG.CHANNEL[1].adr,AD7124REG.CHANNEL[1].value.all, AD7124REG.CHANNEL[1].len);
	
	//配置寄存器
	AD7124REG.CONFIG[0].value.bit.Bipolar=1;//0:单极性
	AD7124REG.CONFIG[0].value.bit.Burnout=0;
	AD7124REG.CONFIG[0].value.bit.REF_BUFP=0;//1：基准缓冲打开
	AD7124REG.CONFIG[0].value.bit.REF_BUFM=0;//1:基准缓冲打开
	AD7124REG.CONFIG[0].value.bit.AIN_BUFP=1;
	AD7124REG.CONFIG[0].value.bit.AIN_BUFM=1;
	AD7124REG.CONFIG[0].value.bit.REF_SEL=0;//0:REFIN1+-; 2:内部基准
	AD7124REG.CONFIG[0].value.bit.PGA=0;
	AD7124.InitERR += AD7124WriteREG(AD7124REG.CONFIG[0].adr,AD7124REG.CONFIG[0].value.all, AD7124REG.CONFIG[0].len);
 
	//滤波器配置
	AD7124REG.FLITER[0].value.bit.Filter = 0;
	AD7124REG.FLITER[0].value.bit.POST_FILTER = 3;
	AD7124REG.FLITER[0].value.bit.FS = 1920;
	AD7124.InitERR += AD7124WriteREG(AD7124REG.FLITER[0].adr,AD7124REG.FLITER[0].value.all, AD7124REG.FLITER[0].len);	 

	//电流及偏压配置
	AD7124REG.IO_CONTROL_1.value.bit.IOUT0 = 1;
	AD7124REG.IO_CONTROL_1.value.bit.IOUT0_CH = 2;
	AD7124.InitERR += AD7124WriteREG(AD7124REG.IO_CONTROL_1.adr,AD7124REG.IO_CONTROL_1.value.all, AD7124REG.IO_CONTROL_1.len);
	
	AD7124REG.IO_CONTROL_2.value.bit.VBIAS3 = 1;
	AD7124.InitERR += AD7124WriteREG(AD7124REG.IO_CONTROL_2.adr,AD7124REG.IO_CONTROL_2.value.all, AD7124REG.IO_CONTROL_2.len);
}	

//uint16_t AD7124ReadID(void)
//{
//  uint16_t ID;
//  ID=0;
//   	AD7124_CS=0;      delay_us(3);  
//  SPI1_ReadWriteByte(0X45);delay_us(3);    
//  ID=  SPI1_ReadWriteByte(0xff); delay_us(3);  
//  ID<<=8;
//  ID|= SPI1_ReadWriteByte(0xff); delay_us(3);  
//   AD7124_CS=1;       delay_us(3);  
//  return ID;
//}



int32_t AD7124_Reset(void)
{
	int32_t i = 0;
	uint8_t rx_data1 =0x00;
	uint8_t wrBuf[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

 
		for(i=0;i<8;i++)
		{
//			 SPI1_ReadWriteByte(wrBuf[i]);
			HAL_SPI_TransmitReceive(&hspi, &wrBuf[i], &rx_data1, 1, 10);
		}
	return 0;
}

//读寄存器
u32 AD7124ReadREG(u8 adr,u8 len)
{
//  uint16_t ID;
//  ID=0;
//   	AD7124_CS=0;      delay_us(3);  
//  SPI1_ReadWriteByte(0X45);delay_us(3);    
//  ID=  SPI1_ReadWriteByte(0xff); delay_us(3);  
//  ID<<=8;
//  ID|= SPI1_ReadWriteByte(0xff); delay_us(3);  
//   AD7124_CS=1;       delay_us(3);  
//  return ID;
	
	u32 value;  
	u8 readdata,i,rx_data1;
	
	value=0; 
	readdata=0;
 
	readdata=0X04<<4;
	readdata|=adr;
	
//	AD7124_CS=0;  
	AD7124_CS_L;
	
//	delay_us(10);
	bsp_DelayUS(10);
	
//	SPI1_ReadWriteByte(readdata);
	HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);

	readdata = 0xff;
	for(i=0;i<len;i++)
	{
		if(i>0)	value<<=8;
//			value |=  SPI1_ReadWriteByte(0xff); 
		HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);
		value |=  rx_data1; 

	}
//   	AD7124_CS=1; 
	AD7124_CS_H;
//	delay_us(10);
	bsp_DelayUS(10);
  return value;
}

//写寄存器
unsigned char AD7124WriteREG(u8 adr,u32 data, u8 len)
{
	u8 i=0; u8 uctemp=0,rx_data1;
	u32 u32temp=0;
	volatile HAL_StatusTypeDef errorcode;
  	
//	AD7124_CS=0; 
	AD7124_CS_L;
//	delay_us(10);
	bsp_DelayUS(10);

	//--写
//	SPI1_ReadWriteByte(adr);
	errorcode = HAL_SPI_TransmitReceive(&hspi, &adr, &rx_data1, 1, 10);
	for(i=0;i<len;i++)
	{
		uctemp=data >> 8*(len-i-1);
		 
//		SPI1_ReadWriteByte(uctemp); 
		HAL_SPI_TransmitReceive(&hspi, &uctemp, &rx_data1, 1, 10);
	}
	//--读
	u32temp = AD7124ReadREG( adr, len);
	if(u32temp==data)
	{
 
//		AD7124_CS=1;  
		AD7124_CS_H;
		
//		delay_us(10);
		bsp_DelayUS(10);
		
		return 0;
	}
	else
	{
//		AD7124_CS=1;  
		AD7124_CS_H;
		
//		delay_us(10);
		bsp_DelayUS(10);
		return 1;
	}
 
}


//写寄存器
unsigned char AD7124WriteREG_NoCS(u8 adr,u32 data, u8 len)
{
	u8 i=0; u8 uctemp=0,rx_data1;
	u32 u32temp=0;
	volatile HAL_StatusTypeDef errorcode;
  	
	//--写
//	SPI1_ReadWriteByte(adr);
	errorcode = HAL_SPI_TransmitReceive(&hspi, &adr, &rx_data1, 1, 10);
	for(i=0;i<len;i++)
	{
		uctemp=data >> 8*(len-i-1);
		 
//		SPI1_ReadWriteByte(uctemp); 
		HAL_SPI_TransmitReceive(&hspi, &uctemp, &rx_data1, 1, 10);
	}
	//--读
//	u32temp = AD7124ReadREG( adr, len);
//	if(u32temp==data)
	if(1)
	{
 		
//		delay_us(10);
		bsp_DelayUS(10);
		
		return 0;
	}
	else
	{
		
//		delay_us(10);
		bsp_DelayUS(10);
		return 1;
	}
 
}


u32 AD7124_RDATA(void)
{
	volatile u32 value;  
//	volatile u8 readdata,rx_data1,i;
	u8 readdata,rx_data1,i;
	
	value=0; readdata=0;
 
//	AD7124_CS=0;
	AD7124_CS_L;
	while(1)
	{
//		if(PAin(6)==1)
		if((SPIx_MISO_GPIO->IDR & SPIx_MISO_PIN) != 0 )
		{
			break;
		}		
	}
//  SPI1_ReadWriteByte( 0X42); 
	readdata = 0x42;
	HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);

	readdata = 0xff;
	for(i=0;i<3;i++)
	{
		if(i>0)	value<<=8;
//		value |=  SPI1_ReadWriteByte( 0xff); 
		HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);
		value |=  rx_data1; 

	}
//  AD7124_CS=1; 
	AD7124_CS_H;
	
	return value;
}

u8 channel = 0;
u32 AD7124_RDATA_Single(void)
{
	volatile u32 value = 0;  
//	volatile u8 readdata,rx_data1,i;
	u8 readdata,rx_data1,i,j = 0;
	
	readdata=0;

	
//	AD7124_CS=0;
	AD7124_CS_L;
	bsp_DelayUS(10);

	AD7124REG.ADC_CONTROL.value.bit.DATA_STATUS = 1;
	AD7124REG.ADC_CONTROL.value.bit.CONT_READ=0;			//1：连续读取
	AD7124REG.ADC_CONTROL.value.bit.Mode=1;//0:	连续转换；1：单次转换；2待机模式，3：关断模式，4：空闲模式，5：内部零电平校准，6：内部满偏校准，7：系统零电平校准，8：系统满偏校准
	AD7124.InitERR += AD7124WriteREG_NoCS(AD7124REG.ADC_CONTROL.adr,AD7124REG.ADC_CONTROL.value.all, AD7124REG.ADC_CONTROL.len);
//	AD7124.InitERR += AD7124WriteREG_NoCS(AD7124REG.CHANNEL[0].adr,AD7124REG.CHANNEL[0].value.all, AD7124REG.CHANNEL[0].len);
//	AD7124.InitERR += AD7124WriteREG_NoCS(AD7124REG.CHANNEL[1].adr,AD7124REG.CHANNEL[1].value.all, AD7124REG.CHANNEL[1].len);
	
	for( j = 0; j < 2; j++ )
//	while(1)
	{
//		bsp_DelayUS(10);
		while(1)
		{
	//		if(PAin(6)==1)
			if((SPIx_MISO_GPIO->IDR & SPIx_MISO_PIN) == 0 )
			{
				break;
			}		
		}
	//  SPI1_ReadWriteByte( 0X42); 
		readdata = 0x42;
		HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);

		readdata = 0x00;
		for(i=0;i<3;i++)
		{
			if(i>0)	value<<=8;
	//		value |=  SPI1_ReadWriteByte( 0xff); 
			HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);
			value |=  rx_data1; 

		}
		HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);
		channel = rx_data1 & 0x01;
		sAD7124Signle[channel].CODE = value;
		value = 0;
//		sAD7124Signle[0].CODE = value[0];
//	sAD7124Signle[1].CODE = value[1];
//	sAD7124Signle[0].fvalue = AD7124_CodeValue(1,value[0],2.5,1000000);
//	sAD7124Signle[1].fvalue = AD7124_CodeValue(1,value[1],2.5,1000000);
	}

	//  AD7124_CS=1; 
	AD7124_CS_H;
//	sAD7124Signle[0].CODE = value[0];
//	sAD7124Signle[1].CODE = value[1];
	sAD7124Signle[0].fvalue = AD7124_CodeValue(1,sAD7124Signle[0].CODE,2.5,1000000);
	sAD7124Signle[1].fvalue = AD7124_CodeValue(1,sAD7124Signle[1].CODE,2.5,1000000);
	return 0;
}


u32 AD7124_RDATA_Multi(void)
{
	volatile u32 value = 0;  
//	volatile u8 readdata,rx_data1,i;
	u8 readdata,rx_data1,i,j = 0;
	
	readdata=0;

	
//	AD7124_CS=0;
	AD7124_CS_L;
	bsp_DelayUS(10);

	AD7124REG.ADC_CONTROL.value.bit.DATA_STATUS = 1;
	AD7124REG.ADC_CONTROL.value.bit.Mode=0;//0:	连续转换；1：单次转换；2待机模式，3：关断模式，4：空闲模式，5：内部零电平校准，6：内部满偏校准，7：系统零电平校准，8：系统满偏校准
	AD7124.InitERR += AD7124WriteREG_NoCS(AD7124REG.ADC_CONTROL.adr,AD7124REG.ADC_CONTROL.value.all, AD7124REG.ADC_CONTROL.len);
	AD7124.InitERR += AD7124WriteREG_NoCS(AD7124REG.CHANNEL[0].adr,AD7124REG.CHANNEL[0].value.all, AD7124REG.CHANNEL[0].len);
	AD7124.InitERR += AD7124WriteREG_NoCS(AD7124REG.CHANNEL[1].adr,AD7124REG.CHANNEL[1].value.all, AD7124REG.CHANNEL[1].len);
	
	for( j = 0; j < 2; j++ )
//	while(1)
	{
//		bsp_DelayUS(10);
		while(1)
		{
	//		if(PAin(6)==1)
			if((SPIx_MISO_GPIO->IDR & SPIx_MISO_PIN) == 0 )
			{
				break;
			}		
		}
//	//  SPI1_ReadWriteByte( 0X42); 
//		readdata = 0x42;
//		HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);

		readdata = 0x00;
		for(i=0;i<3;i++)
		{
			if(i>0)	value<<=8;
	//		value |=  SPI1_ReadWriteByte( 0xff); 
			HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);
			value |=  rx_data1; 

		}
		HAL_SPI_TransmitReceive(&hspi, &readdata, &rx_data1, 1, 10);
		channel = rx_data1 & 0x01;
		sAD7124Signle[channel].CODE = value;
		value = 0;
//		sAD7124Signle[0].CODE = value[0];
//	sAD7124Signle[1].CODE = value[1];
//	sAD7124Signle[0].fvalue = AD7124_CodeValue(1,value[0],2.5,1000000);
//	sAD7124Signle[1].fvalue = AD7124_CodeValue(1,value[1],2.5,1000000);
	}

	//  AD7124_CS=1; 
	AD7124_CS_H;
//	sAD7124Signle[0].CODE = value[0];
//	sAD7124Signle[1].CODE = value[1];
	sAD7124Signle[0].fvalue = AD7124_CodeValue(1,sAD7124Signle[0].CODE,2.5,1000000);
	sAD7124Signle[1].fvalue = AD7124_CodeValue(1,sAD7124Signle[1].CODE,2.5,1000000);
	return 0;
}


double AD7124_CodeValue(unsigned char pol, unsigned int code, float vref, float gain)
{
		double dftemp=0;
		//单极性
		if(pol==0)
		{
					dftemp=code*(vref/16777216);
		}
		//双极性
		else
		{
//				if(code&0x800000)
//				{
//								code|=0XFF000000;
//				}
//				dftemp=code*(vref/16777216);
				dftemp=(code/8388608.0 - 1)*2.500;			
		}
		dftemp=dftemp*gain;
		return dftemp;

}



