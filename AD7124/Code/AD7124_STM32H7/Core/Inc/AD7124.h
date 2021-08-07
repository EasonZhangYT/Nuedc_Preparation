#ifndef __AD7124_H
#define __AD7124_H
#include "stm32h7xx_hal.h"

//#define SPIx_SCK_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
//#define SPIx_SCK_GPIO				GPIOA
//#define SPIx_SCK_PIN				GPIO_PIN_12
//#define SPIx_SCK_AF					GPIO_AF5_SPI2
#define SPIx_SCK_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_SCK_GPIO				GPIOB
#define SPIx_SCK_PIN				GPIO_PIN_10
#define SPIx_SCK_AF					GPIO_AF5_SPI2

//#define SPIx_MISO_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
//#define SPIx_MISO_GPIO				GPIOC
//#define SPIx_MISO_PIN 				GPIO_PIN_2
//#define SPIx_MISO_AF				GPIO_AF5_SPI2
#define SPIx_MISO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MISO_GPIO				GPIOB
#define SPIx_MISO_PIN 				GPIO_PIN_14
#define SPIx_MISO_AF				GPIO_AF5_SPI2

//#define SPIx_MOSI_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
//#define SPIx_MOSI_GPIO				GPIOC
//#define SPIx_MOSI_PIN 				GPIO_PIN_1
//#define SPIx_MOSI_AF				GPIO_AF5_SPI2
#define SPIx_MOSI_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_GPIO				GPIOB
#define SPIx_MOSI_PIN 				GPIO_PIN_15
#define SPIx_MOSI_AF				GPIO_AF5_SPI2


#define AD7124_START_PORT             GPIOB
#define AD7124_START_PIN              GPIO_PIN_5
#define AD7124_PWDN_PORT              GPIOB
#define AD7124_PWDN_PIN               GPIO_PIN_6
#define AD7124_ADC_RDY_PORT           GPIOB
#define AD7124_ADC_RDY_PIN            GPIO_PIN_7
#define AD7124_CS_PORT                GPIOB
#define AD7124_CS_PIN                 GPIO_PIN_8

#define	AD7124_CS_H 		HAL_GPIO_WritePin(AD7124_CS_PORT, AD7124_CS_PIN,GPIO_PIN_SET) 	
#define	AD7124_CS_L 		HAL_GPIO_WritePin(AD7124_CS_PORT, AD7124_CS_PIN,GPIO_PIN_RESET) 

typedef unsigned char u8; 
typedef unsigned short u16; 
typedef unsigned int u32; 

 typedef struct
 {
	 			//--0X00  STATUS
			struct
			{
						union 
						{
								struct
								{
										u8  CH_ACTIVE	    :4;
										u8 	PRO_FLAG      :1;
										u8 	         	    :1;
										u8  ERR_FLAG    :1;
										u8  	RDY				 :1;
								}bit;
								u8 all;
						}value;
						u8 adr;
						u8 len;
			}STATUS; 
			//--0X01  ADC_CONTROL¼Ä´æÆ÷
			struct
			{
						union 
						{
								struct
								{
										u16  CLK_SEL	  :2;
										u16 	Mode      :4;
										u16 	POWER_MODE :2;
										u16  REF_EN    :1;
										u16  CS_EN			 :1;
										u16  DATA_STATUS	 :1;
										u16  CONT_READ	 :1;
										u16  DOUT_RDY_DEL	 :1;
									  u16   	 :3;
								}bit;
								u16 all;
						}value;
						u8 adr;
						u8 len;
			}ADC_CONTROL; 	 
 			//--0X02  DATA Êý¾Ý¼Ä´æÆ÷
			struct
			{
					u32 value;
					u8 adr;
					u8 len;
			}DATA;
			//--0X03  IO_CONTROL_1 Êý¾Ý¼Ä´æÆ÷
			struct
			{
						union 
						{
								struct
								{
										u16  IOUT0_CH	:4;
										u16 	IOUT1_CH  :4;
										u16 	IOUT0 :3;
										u16  IOUT1    :3;
										u16   			 :1;
										u16  PDSW		 :1;
										u16  GPIO_CTRL1	 :1;
										u16  GPIO_CTRL2	 :1;
										u16  GPIO_CTRL3	 :1;
										u16  GPIO_CTRL4	 :1;
										u16  GPIO_DAT1	 :1;
										u16  GPIO_DAT2	 :1;
										u16  GPIO_DAT3	 :1;
										u16  GPIO_DAT4	 :1;									
								}bit;
								u16 all;
						}value;
						u8 adr;
						u8 len;
			}IO_CONTROL_1; 	
			//--0X04  IO_CONTROL_2 Êý¾Ý¼Ä´æÆ÷
			struct
			{
						union 
						{
								struct
								{
										u16  VBIAS0	:1;
										u16  VBIAS1	:1;
										u16  VBIAS2	:1;
										u16  VBIAS3	:1;
										u16  VBIAS4	:1;
										u16  VBIAS5	:1;
										u16  VBIAS6	:1;
										u16  VBIAS7	:1;
										u16  VBIAS8	:1;
										u16  VBIAS9	:1;
										u16  VBIAS10	:1;
										u16  VBIAS11	:1;
										u16  VBIAS12	:1;
										u16  VBIAS13	:1;
										u16  VBIAS14	:1;
										u16  VBIAS15	:1;
								}bit;
								u16 all;
						}value;
						u8 adr;
						u8 len;
			}IO_CONTROL_2; 
 			//--0X05  ID
			struct
			{
					u8 value;
					u8 adr;
					u8 len;
			}ID;
			//--0X06  ERR ´íÎó¼Ä´æÆ÷
			struct
			{
						union 
						{
								struct
								{
										u32   	:1;
										u32  MM_CRC_ERR	:1;
										u32  SPI_CRC_ERR	:1;
										u32  SPI_WRITE_ERR	:1;
										u32  SPI_READ_ERR	:1;
										u32  SPI_SCLK_CNT_ERR	:1;
										u32  SPI_IGNORE_ERR	:1;
										u32  ALDO_PSM_ERR 	:1;
										u32   	:1;
										u32  DLDO_PSM_ERR	:1;
										u32   	:1;
										u32  REF_DET_ERR	:1;
										u32  AINM_UV_ERR 	:1;
										u32  AINM_OV_ERR	:1;
										u32  AINP_UV_ERR 	:1;
										u32  AINP_OV_ERR	:1;
										u32  ADC_SAT_ERR	:1;
										u32  ADC_CONV_ERR 	:1;
										u32  ADC_CAL_ERR 	:1;
										u32  LDO_CAP_ERR 	:1;
										u32   	:4;
								}bit;
								u32 all;
						}value;
						u8 adr;
						u8 len;
			}ERR;  
			//--0X07  ERROR_EN ´íÎó¼Ä´æÆ÷
			struct
			{
						union 
						{
								struct
								{
										u32   	:1;
										u32  MM_CRC_ERR_EN	:1;
										u32  SPI_CRC_ERR_EN	:1;
										u32  SPI_WRITE_ERR_EN	:1;
										u32  SPI_READ_ERR_EN	:1;
										u32  SPI_SCLK_CNT_ERR_EN	:1;
										u32  SPI_IGNORE_ERR_EN	:1;
										u32  ALDO_PSM_ERR_EN 	:1;
										u32  ALDO_PSM_TRIP_TEST_EN 	:1;
										u32  DLDO_PSM_ERR_EN	:1;
										u32  DLDO_PSM_TRIP_TEST_EN 	:1;
										u32  REF_DET_ERR_EN	:1;
										u32  AINM_UV_ERR_EN 	:1;
										u32  AINM_OV_ERR_EN	:1;
										u32  AINP_UV_ERR_EN 	:1;
										u32  AINP_OV_ERR_EN	:1;
										u32  ADC_SAT_ERR_EN	:1;
										u32  ADC_CONV_ERR_EN 	:1;
										u32  ADC_CAL_ERR_EN 	:1;
										u32  LDO_CAP_CHK 	:2;
										u32  LDO_CAP_CHK_TEST_EN 	:1;
										u32  MCLK_CNT_EN 	:1;
										u32    	:1;
								}bit;
								u32 all;
						}value;
						u8 adr;
						u8 len;
			}ERR_EN;  
			//--0X08  MCLK_COUNT¼Ä´æÆ÷
			struct
			{
					u8 value;
					u8 adr;
					u8 len;
			}MCLK_COUNT;
			//--0X09~0X18 CHANNEL Í¨µÀ¼Ä´æÆ÷
			struct
			{
						union 
						{
								struct
								{
										u16  AINM 	:5;
										u16  AINP 	:5;
										u16   	:2;
										u16  Setup  	:3;
										u16  Enable 	:1;
								}bit;
								u16 all;
						}value;
						u8 adr;
						u8 len;
			}CHANNEL[15];
			//--0X19~0X20 CONFIG Í¨µÀ¼Ä´æÆ÷
			struct
			{
						union 
						{
								struct
								{
										u16  PGA 	:3;
										u16  REF_SEL 	:2;
										u16  AIN_BUFM 	:1;
										u16  AIN_BUFP 	:1;
										u16  REF_BUFM 	:1;
										u16  REF_BUFP 	:1;
										u16  Burnout  	:2;
										u16  Bipolar  	:1;
										u16     	:4;
								}bit;
								u16 all;
						}value;
						u8 adr;
						u8 len;
			}CONFIG[8];
			//--0X21~0X28 FLITER Í¨µÀ¼Ä´æÆ÷
			struct
			{
						union 
						{
								struct
								{
										u32  FS 	:11;
										u32    	:5;
										u32  SINGLE_CYCLE 	:1;
										u32  POST_FILTER 	:3;
										u32  REJ60 	:1;
										u32  Filter 	:3;
								}bit;
								u32 all;
						}value;
						u8 adr;
						u8 len;
			}FLITER[8];
			//--0X29~0X30 OFFSET Í¨µÀ¼Ä´æÆ÷
			struct
			{
					u32 value;
					u8 adr;
					u8 len;
			}Offset[8];
			struct
			{
					u32 value;
					u8 adr;
					u8 len;
			}GAIN[8];
			
 }AD7124REGSTRUCT;
extern   AD7124REGSTRUCT   AD7124REG;
 
typedef struct 
{
		unsigned  int InitERR;
		unsigned  int CODE;
		double   fvalue;
}AD7124Struct;
extern  volatile AD7124Struct AD7124;
extern  volatile AD7124Struct sAD7124Signle[2];



extern SPI_HandleTypeDef hspi;

extern void Error_Handler(void);

void AD7124Init(void);
uint16_t AD7124ReadID(void);
int32_t AD7124_Reset(void);
u32 AD7124ReadREG(u8 adr,u8 len);
unsigned char AD7124WriteREG(u8 adr,u32 data, u8 len);
double AD7124_CodeValue(unsigned char pol, unsigned int code, float vref, float gain);
u32 AD7124_RDATA(void);
u32 AD7124_RDATA_Single(void);
u32 AD7124_RDATA_Multi(void);
#endif
