/*
*********************************************************************************************************
*
*	ģ������ : SPI��������
*	�ļ����� : bsp_spi_bus.h
*	��    �� : V1.0
*	˵    �� : ͷ�ļ�
*
*	Copyright (C), 2014-2015, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __BSP_SPI_BUS_H
#define __BSP_SPI_BUS_H

//#define SPIx_SCK_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
//#define SPIx_SCK_GPIO				GPIOB
//#define SPIx_SCK_PIN				GPIO_PIN_3
//#define SPIx_SCK_AF					GPIO_AF5_SPI1
#define SPIx_SCK_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_SCK_GPIO				GPIOA
#define SPIx_SCK_PIN				GPIO_PIN_12
#define SPIx_SCK_AF					GPIO_AF5_SPI2

//#define SPIx_MISO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
//#define SPIx_MISO_GPIO				GPIOB
//#define SPIx_MISO_PIN 				GPIO_PIN_4
//#define SPIx_MISO_AF				GPIO_AF5_SPI1
#define SPIx_MISO_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_MISO_GPIO				GPIOC
#define SPIx_MISO_PIN 				GPIO_PIN_2
#define SPIx_MISO_AF				GPIO_AF5_SPI2

//#define SPIx_MOSI_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
//#define SPIx_MOSI_GPIO				GPIOB
//#define SPIx_MOSI_PIN 				GPIO_PIN_5
//#define SPIx_MOSI_AF				GPIO_AF5_SPI1
#define SPIx_MOSI_CLK_ENABLE()		__HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_MOSI_GPIO				GPIOC
#define SPIx_MOSI_PIN 				GPIO_PIN_1
#define SPIx_MOSI_AF				GPIO_AF5_SPI2

/* �ض�����SPI SCKʱ�ӣ�������ֲ */
#define SPI_BAUDRATEPRESCALER_100M      SPI_BAUDRATEPRESCALER_2			/* 100M */
#define SPI_BAUDRATEPRESCALER_50M       SPI_BAUDRATEPRESCALER_4			/* 50M */
#define SPI_BAUDRATEPRESCALER_12_5M     SPI_BAUDRATEPRESCALER_8			/* 12.5M */
#define SPI_BAUDRATEPRESCALER_6_25M     SPI_BAUDRATEPRESCALER_16		/* 6.25M */
#define SPI_BAUDRATEPRESCALER_3_125M    SPI_BAUDRATEPRESCALER_32		/* 3.125M */
#define SPI_BAUDRATEPRESCALER_1_5625M   SPI_BAUDRATEPRESCALER_64		/* 1.5625M */
#define SPI_BAUDRATEPRESCALER_781_25K   SPI_BAUDRATEPRESCALER_128		/* 781.25K */
#define SPI_BAUDRATEPRESCALER_390_625K  SPI_BAUDRATEPRESCALER_256		/* 390.625K */

void bsp_InitSPIBus(void);
void bsp_spiTransfer(void);
void bsp_InitSPIParam(uint32_t _BaudRatePrescaler, uint32_t _CLKPhase, uint32_t _CLKPolarity);

void bsp_SpiBusEnter(void);
void bsp_SpiBusExit(void);
uint8_t bsp_SpiBusBusy(void);

#define	SPI_BUFFER_SIZE		(4 * 1024)				/*  */

extern uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];
extern uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];
extern uint32_t g_spiLen;

extern uint8_t g_spi_busy;

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
