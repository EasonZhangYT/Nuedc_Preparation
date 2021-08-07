#ifndef __ADS1292R_H
#define __ADS1292R_H

#include "stm32h7xx_hal.h"
#include "arm_math.h"

//#include "arm_math.h"
//#include "sys.h"
////#include "tftlcd.h"
//#include <stdio.h>
//#include "arm_math.h"
//#include "math_helper.h"
//#include "arm_fir_example_f32.h"

//#define ADS1292R_CS_PORT                GPIOF
//#define ADS1292R_CS_PIN                 GPIO_PIN_6
//#define ADS1292R_START_PORT             GPIOB
//#define ADS1292R_START_PIN              GPIO_PIN_1
//#define ADS1292R_PWDN_PORT              GPIOB
//#define ADS1292R_PWDN_PIN               GPIO_PIN_0
//#define ADS1292R_ADC_RDY_PORT           GPIOB
//#define ADS1292R_ADC_RDY_PIN            GPIO_PIN_11
#define ADS1292R_CS_PORT                GPIOA
#define ADS1292R_CS_PIN                 GPIO_PIN_4
#define ADS1292R_START_PORT             GPIOF
#define ADS1292R_START_PIN              GPIO_PIN_10
#define ADS1292R_PWDN_PORT              GPIOF
#define ADS1292R_PWDN_PIN               GPIO_PIN_6
#define ADS1292R_ADC_RDY_PORT           GPIOF
#define ADS1292R_ADC_RDY_PIN            GPIO_PIN_8

#define ADS1292R_CS_H				HAL_GPIO_WritePin(ADS1292R_CS_PORT, ADS1292R_CS_PIN,GPIO_PIN_SET)
#define ADS1292R_CS_L				HAL_GPIO_WritePin(ADS1292R_CS_PORT, ADS1292R_CS_PIN,GPIO_PIN_RESET)
#define ADS1292R_PWDN_H			HAL_GPIO_WritePin(ADS1292R_PWDN_PORT, ADS1292R_PWDN_PIN,GPIO_PIN_SET)
#define ADS1292R_PWDN_L			HAL_GPIO_WritePin(ADS1292R_PWDN_PORT, ADS1292R_PWDN_PIN,GPIO_PIN_RESET)
#define ADS1292R_START_H		HAL_GPIO_WritePin(ADS1292R_START_PORT, ADS1292R_START_PIN,GPIO_PIN_SET)
#define ADS1292R_START_L		HAL_GPIO_WritePin(ADS1292R_START_PORT, ADS1292R_START_PIN,GPIO_PIN_RESET)

/*ADS1292R命令定义*/
/*系统命令*/
#define ADS1292R_WAKEUP	        	0X02	//从待机模式唤醒
#define ADS1292R_STANDBY	        0X04	//进入待机模式
#define ADS1292R_ADSRESET        	0X06	//复位ADS1292R
#define ADS1292R_START	        	0X08	//启动或转换
#define ADS1292R_STOP	        		0X0A	//停止转换
#define ADS1292R_OFFSETCAL				0X1A	//通道偏移校准
/*数据读取命令*/
#define ADS1292R_RDATAC	        	0X10	//启用连续的数据读取模式,默认使用此模式
#define ADS1292R_SDATAC	        	0X11	//停止连续的数据读取模式
#define ADS1292R_RDATA	        	0X12	//通过命令读取数据;支持多种读回。
/*寄存器读取命令*/
#define	ADS1292R_RREG	        		0X20	//读取001r rrrr 000n nnnn  这里定义的只有高八位，低8位在发送命令时设置
#define ADS1292R_WREG	        		0X40	//写入010r rrrr 000n nnnn
/*	r rrrr=要读、写的寄存器地址
		n nnnn=要读、写的数据		*/
/*ADS1292R内部寄存器地址定义	*/
#define ADS1292R_ID								0X00	//ID控制寄存器
#define ADS1292R_CONFIG1					0X01	//配置寄存器1
#define ADS1292R_CONFIG2					0X02	//配置寄存器2
#define ADS1292R_LOFF							0X03	//导联脱落控制寄存器
#define ADS1292R_CH1SET						0X04	//通道1设置寄存器
#define ADS1292R_CH2SET						0X05	//通道2设置寄存器
#define ADS1292R_RLD_SENS					0X06	//右腿驱动选择寄存器
#define ADS1292R_LOFF_SENS				0X07	//导联脱落检测选择寄存器
#define ADS1292R_LOFF_STAT				0X08	//导联脱落检测状态寄存器
#define	ADS1292R_RESP1						0X09	//呼吸检测控制寄存器1
#define	ADS1292R_RESP2						0X0A	//呼吸检测控制寄存器2
#define	ADS1292R_GPIO							0X0B	//GPIO控制寄存器

extern uint8_t ads1292r_data_buff[];
extern SPI_HandleTypeDef SPI5_Handler; 
extern uint8_t ads1292_recive_flag;	//数据读取完成标志
extern uint8_t device_id;

extern uint8_t ads1292_Cache[9] ; //数据缓冲区
extern uint8_t temp1292r[9];

extern uint8_t Flag_HALF_Full;
extern float32_t filter_result[1000];
extern float32_t Process_Data[2048];
extern float32_t filter_Highpass[1000];
extern float32_t filter_Lowpass[1000];
extern float32_t ban_data[1000];
extern float32_t Half_data[500];
extern float32_t Full_data[500];
extern uint8_t flag_filter_begin;
extern  uint8_t Flag_Store;

extern float32_t Store_Data_1[512];
extern float32_t Store_Data_2[512];
extern float32_t Get_Data[512];


void AD1292_Init(void); //初始化ADS1292引脚
void AD1292_PowerOnInit(void);//上电初始化
uint8_t ADS1292R_SPI_RW(uint8_t data);
void ADS1292R_CMD(uint8_t cmd);
void ADS1292R_Work(void);
void ADS1292R_Halt(void);
void ADS1292R_ReadData(void);
uint8_t ADS1292R_REG(uint8_t cmd, uint8_t data);	
uint32_t data_han1(void);
uint32_t data_han2();
int uhexTodec(uint32_t dataIn);
float32_t Data_Filter_DT(float32_t DT_data);
void Data_Filter_HD(void);
void Data_Filter_Medium(void);
void Data_Store(void);
void Heart_Rate_Cal(void);
void Data_Filter_HighPass(void);
#endif


//手册及论坛资料：
//关于CLK您是使用内部时钟还是使用外部时钟？如果使用内部时钟，可以将其接地。如果使用外部时钟，可以接有源晶振或者MCU的时钟输出引脚给ADS1292 提供时钟。
//使用内部晶振的话，寄存器CONFIG2的bit3 如果配置为1的话，那么CLK有输出，频率即为内部时钟产生的频率，如果配置为0的话，那么CLK输出disable
//SCLK 即为SPI的频率，它的大小datasheet已经给出，当2.7 V ≤ DVDD ≤ 3.6 V，周期tSCLK（min）=50ns。 当1.7 V ≤ DVDD ≤ 2 V时，tSCLK（min）=66.6ns

//1. 在连续读模式下，不能读写寄存器。在连续读模式下，首先要发命令停止 SDATAC 。然后才能发送其他命令。
//2. 手册里面这样描述，1292 接收多字节命令时，解析一个字节需要 7.2us。因此你发送多字节命令时，两个字节之间的间隔至少要到8us
//测试流程
//	设置 CLKSEL =1 	使用内部时钟，
//	设置 PWDN/RESET = 1  等待1秒 开机复位和等待起振
//	发送SDATAC命令  设置寄存器
//	发送WREG CONFIG2 A0h	使用内部参考电压，
//	设置START = 1		激活转换
//	发送RDATAC命令	将设备恢复到RDATAC模式
//	捕获数据并检查噪音
//	捕获数据并测试信号

